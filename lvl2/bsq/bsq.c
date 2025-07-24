#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
    int rows;
    char empty;
    char obstacle;
    char full;
    char **map;
    int cols;
} Map;

typedef struct {
    int x, y, size;
} Square;

int min(int a, int b, int c) {
    int m = a < b ? a : b;
    return m < c ? m : c;
}

int parse_header(char *line, Map *map) {
    int i = 0, len = strlen(line);
    char *num_str = malloc(len);
    int j = 0;
    
    // Extract number
    while (i < len && line[i] >= '0' && line[i] <= '9') {
        num_str[j++] = line[i++];
    }
    num_str[j] = '\0';
    
    if (j == 0 || i >= len - 2) {
        free(num_str);
        return 0;
    }
    
    map->rows = atoi(num_str);
    map->empty = line[i];
    map->obstacle = line[i + 1];
    map->full = line[i + 2];
    
    free(num_str);
    
    // Check for duplicate characters
    if (map->empty == map->obstacle || map->empty == map->full || map->obstacle == map->full) {
        return 0;
    }
    
    return map->rows > 0;
}

int validate_map(Map *map) {
    if (map->rows <= 0 || map->cols <= 0) return 0;
    
    for (int i = 0; i < map->rows; i++) {
        if (strlen(map->map[i]) != map->cols) return 0;
        for (int j = 0; j < map->cols; j++) {
            if (map->map[i][j] != map->empty && map->map[i][j] != map->obstacle) {
                return 0;
            }
        }
    }
    return 1;
}

Square find_biggest_square(Map *map) {
    Square best = {0, 0, 0};
    int **dp = malloc(map->rows * sizeof(int*));
    
    for (int i = 0; i < map->rows; i++) {
        dp[i] = malloc(map->cols * sizeof(int));
        for (int j = 0; j < map->cols; j++) {
            dp[i][j] = 0;
        }
    }
    
    // Fill DP table
    for (int i = 0; i < map->rows; i++) {
        for (int j = 0; j < map->cols; j++) {
            if (map->map[i][j] == map->empty) {
                if (i == 0 || j == 0) {
                    dp[i][j] = 1;
                } else {
                    dp[i][j] = min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1]) + 1;
                }
                
                if (dp[i][j] > best.size) {
                    best.size = dp[i][j];
                    best.x = j - dp[i][j] + 1;
                    best.y = i - dp[i][j] + 1;
                }
            }
        }
    }
    
    for (int i = 0; i < map->rows; i++) {
        free(dp[i]);
    }
    free(dp);
    
    return best;
}

void fill_square(Map *map, Square sq) {
    for (int i = sq.y; i < sq.y + sq.size; i++) {
        for (int j = sq.x; j < sq.x + sq.size; j++) {
            map->map[i][j] = map->full;
        }
    }
}

void print_map(Map *map) {
    for (int i = 0; i < map->rows; i++) {
        printf("%s\n", map->map[i]);
    }
}

void free_map(Map *map) {
    if (map->map) {
        for (int i = 0; i < map->rows; i++) {
            free(map->map[i]);
        }
        free(map->map);
    }
}

int process_file(FILE *file) {
    char *line = NULL;
    size_t len = 0;
    Map map = {0};
    
    // Read header
    if (getline(&line, &len, file) <= 0) {
        free(line);
        return 0;
    }
    
    // Remove newline
    int line_len = strlen(line);
    if (line_len > 0 && line[line_len - 1] == '\n') {
        line[line_len - 1] = '\0';
    }
    
    if (!parse_header(line, &map)) {
        fprintf(stderr, "map error\n");
        free(line);
        return 1;
    }
    
    // Allocate map
    map.map = malloc(map.rows * sizeof(char*));
    
    // Read map lines
    for (int i = 0; i < map.rows; i++) {
        if (getline(&line, &len, file) <= 0) {
            fprintf(stderr, "map error\n");
            free_map(&map);
            free(line);
            return 1;
        }
        
        // Remove newline
        line_len = strlen(line);
        if (line_len > 0 && line[line_len - 1] == '\n') {
            line[line_len - 1] = '\0';
        }
        
        if (i == 0) {
            map.cols = strlen(line);
        }
        
        map.map[i] = malloc(strlen(line) + 1);
        strcpy(map.map[i], line);
    }
    
    if (!validate_map(&map)) {
        fprintf(stderr, "map error\n");
        free_map(&map);
        free(line);
        return 1;
    }
    
    Square sq = find_biggest_square(&map);
    if (sq.size > 0) {
        fill_square(&map, sq);
    }
    
    print_map(&map);
    
    free_map(&map);
    free(line);
    return 1;
}

int main(int argc, char **argv) {
    if (argc == 1) {
        // Read from stdin
        process_file(stdin);
    } else {
        // Process each file
        for (int i = 1; i < argc; i++) {
            FILE *file = fopen(argv[i], "r");
            if (!file) {
                fprintf(stderr, "map error\n");
                continue;
            }
            
            process_file(file);
            fclose(file);
            
            if (i < argc - 1) {
                printf("\n");
            }
        }
    }
    
    return 0;
}