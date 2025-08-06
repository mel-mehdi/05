#ifndef VECT2_HPP
#define VECT2_HPP

#include <iostream>

class vect2
{
    private:
		int x;
		int y;

    public:
    vect2();
    vect2(int x, int y);
    vect2(const vect2& other);
    vect2& operator=(const vect2& other) throw();
	vect2 operator+(const vect2& other) const;
	vect2& operator+=(const vect2& other);

	vect2 operator-(const vect2& other) const;
	vect2& operator-=(const vect2& other);

	vect2 operator*(int scalar) const;
	vect2& operator*=(int scalar);
	vect2 operator-() const;
	bool operator==(const vect2& other) const;
	bool operator!=(const vect2& other) const;
	int& operator[](int index);
	const int& operator[](int index) const;
	vect2& operator++();
	vect2 operator++(int);
	vect2& operator--();
	vect2 operator--(int);
	friend std::ostream& operator<<(std::ostream& os, const vect2& v);
    int getX() const throw();
    int getY() const throw();
    void setX(int newX) throw();
    void setY(int newY) throw();

	friend vect2 operator*(int scalar, const vect2& v);

};

#endif