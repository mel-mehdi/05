#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

char get_cell(char *b, int w, int h, int x, int y)
{
	if (x < 0 || y < 0 || x >= w || y >= h) return 0;
	return b[y * w + x];
}

int live_neighbors(char *b, int w, int h, int x, int y)
{
	int n = 0;
	for (int dy = -1; dy <= 1; dy++)
		for (int dx = -1; dx <= 1; dx++)
			if (dx || dy) n += get_cell(b, w, h, x + dx, y + dy);
	return n;
}

void update(char *b, char *next, int w, int h) 
{
	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++)
		{
			int n = live_neighbors(b, w, h, x, y);
			int c = get_cell(b, w, h, x, y);
			next[y * w + x] = (c && (n == 2 || n == 3)) || (!c && n == 3);
		}
}

void draw(char *b, int w, int h)
{
	for (int y = 0; y < h; y++)\
	{
		for (int x = 0; x < w; x++)
			putchar(b[y * w + x] ? '0' : ' ');
		putchar('\n');
	}
}

int main(int ac, char **av)
{
	if (ac != 4) return 1;
	int w = atoi(av[1]), h = atoi(av[2]), it = atoi(av[3]);
	char *board = calloc(w * h, 1);
	char *next = calloc(w * h, 1);
	int x = 0, y = 0, pen = 0;
	char c;
	while (read(0, &c, 1) > 0)
	{
		if (c == 'x') pen = !pen;
		else if (c == 'w' && y > 0) y--;
		else if (c == 's' && y + 1 < h) y++;
		else if (c == 'a' && x > 0) x--;
		else if (c == 'd' && x + 1 < w) x++;
		if (pen) board[y * w + x] = 1;
	}
	while (it--) {
		update(board, next, w, h);
		char *tmp = board; board = next; next = tmp;
	}
	draw(board, w, h);
	free(board);
	free(next);
	return 0;
}
