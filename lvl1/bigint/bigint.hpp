#pragma once
#include <iostream>
#include <string>
#include <algorithm>

class bigint {
	std::string value;

public:
	bigint(unsigned long long n = 0) : value(std::to_string(n)) {}
	bigint(const std::string &s) : value(s) { trim(); }
	friend std::ostream &operator<<(std::ostream &os, const bigint &b) {return os << b.value;}
	bigint &operator+=(const bigint &other);
	friend bigint operator+(bigint a, const bigint &b) { return a += b; }
	bigint &operator++() { return *this += 1; }
	bigint operator++(int) { bigint tmp = *this; ++(*this); return tmp; }
	bool operator<(const bigint &b) const;
	bool operator>(const bigint &b) const { return b < *this; }
	bool operator<=(const bigint &b) const { return !(b < *this); }
	bool operator>=(const bigint &b) const { return !(*this < b); }
	bool operator==(const bigint &b) const { return value == b.value; }
	bool operator!=(const bigint &b) const { return !(*this == b); }
	bigint operator<<(int n) const;
	bigint &operator<<=(int n);
	bigint &operator<<=(const bigint &n);
	bigint operator>>(int n) const;
	bigint &operator>>=(int n);
	bigint &operator>>=(const bigint &n);
private:
	void trim() {
		value.erase(0, value.find_first_not_of('0'));
		if (value.empty()) value = "0";
	}
};
