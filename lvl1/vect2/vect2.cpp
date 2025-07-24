#include "vect2.hpp"

vect2::vect2() : x(0), y(0) {}

vect2::vect2(int x_, int y_) : x(x_), y(y_) {}

vect2::vect2(const vect2 &other) : x(other.x), y(other.y) {}

vect2 &vect2::operator=(const vect2 &other) {
	if (this != &other) {
		x = other.x;
		y = other.y;
	}
	return *this;
}

int &vect2::operator[](int index) {
	return (index == 0 ? x : y);
}

const int &vect2::operator[](int index) const {
	return (index == 0 ? x : y);
}

vect2 &vect2::operator+=(const vect2 &other) {
	x += other.x;
	y += other.y;
	return *this;
}

vect2 &vect2::operator-=(const vect2 &other) {
	x -= other.x;
	y -= other.y;
	return *this;
}

vect2 vect2::operator+(const vect2 &other) const {
	return vect2(x + other.x, y + other.y);
}

vect2 vect2::operator-(const vect2 &other) const {
	return vect2(x - other.x, y - other.y);
}

vect2 &vect2::operator++() {
	++x;
	++y;
	return *this;
}

vect2 vect2::operator++(int) {
	vect2 tmp(*this);
	++(*this);
	return tmp;
}

vect2 &vect2::operator--() {
	--x;
	--y;
	return *this;
}

vect2 vect2::operator--(int) {
	vect2 tmp(*this);
	--(*this);
	return tmp;
}

bool vect2::operator==(const vect2 &other) const {
	return x == other.x && y == other.y;
}

bool vect2::operator!=(const vect2 &other) const {
	return !(*this == other);
}

vect2 operator*(int scalar, const vect2 &v) {
	return vect2(scalar * v.x, scalar * v.y);
}

std::ostream &operator<<(std::ostream &os, const vect2 &v) {
	os << "{" << v[0] << ", " << v[1] << "}";
	return os;
}
