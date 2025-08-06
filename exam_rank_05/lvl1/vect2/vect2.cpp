#include "vect2.hpp"

vect2::vect2(): x(0), y(0) {}

vect2::vect2(int x, int y) : x(x), y(y) {}

vect2::vect2(const vect2& other) : x(other.x), y(other.y){}
vect2& vect2::operator=(const vect2& other)throw()
{
    if (this != &other){
        x = other.x;
        y = other.y;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const vect2& v)
{
	os << "{" << v.x << ", " << v.y << "}";
	return os;
}

vect2 vect2::operator+(const vect2& other) const
{
	return vect2(x + other.x, y + other.y);
}

vect2& vect2::operator+=(const vect2& other)
{
	x += other.x;
	y += other.y;
	return *this;
}

vect2 vect2::operator-(const vect2& other) const
{
	return vect2(x - other.x, y - other.y);
}

vect2& vect2::operator-=(const vect2& other)
{
	x -= other.x;
	y -= other.y;
	return *this;
}

bool vect2::operator==(const vect2& other) const
{
	return x == other.x && y == other.y;
}

bool vect2::operator!=(const vect2& other) const
{
	return !(*this == other);
}

vect2& vect2::operator++()
{
	++x;
	++y;
	return *this;
}

vect2 vect2::operator++(int)
{
	vect2 temp(*this);
	++(*this);
	return temp;
}

vect2& vect2::operator--()
{
	--x;
	--y;
	return *this;
}

vect2 vect2::operator--(int)
{
	vect2 temp(*this);
	--(*this);
	return temp;
}

vect2 operator*(int scalar, const vect2& v)
{
	return vect2(v.getX() * scalar, v.getY() * scalar);
}

int vect2::getX() const throw()
{
	return x;
}

int vect2::getY() const throw()
{
	return y;
}

void vect2::setX(int newX) throw()
{
	x = newX;
}

void vect2::setY(int newY) throw()
{
	y = newY;
}

vect2 vect2::operator*(int scalar) const
{
	return vect2(x * scalar, y * scalar);
}

vect2& vect2::operator*=(int scalar)
{
	x *= scalar;
	y *= scalar;
	return *this;
}

int& vect2::operator[](int index)
{
	if (index == 0)
		return x;
	else
		return y;
}

const int& vect2::operator[](int index) const
{
	if (index == 0)
		return x;
	else
		return y;
}

vect2 vect2::operator-() const
{
	return vect2(-x, -y);
}