#include "bigint.hpp"

bigint &bigint::operator+=(const bigint &other) {
	std::string a = value, b = other.value, res;
	int carry = 0;

	std::reverse(a.begin(), a.end());
	std::reverse(b.begin(), b.end());
	size_t len = std::max(a.size(), b.size());
	a.resize(len, '0');
	b.resize(len, '0');

	for (size_t i = 0; i < len; ++i) {
		int sum = (a[i] - '0') + (b[i] - '0') + carry;
		res += (sum % 10 + '0');
		carry = sum / 10;
	}
	if (carry) res += (carry + '0');
	std::reverse(res.begin(), res.end());
	value = res;
	return *this;
}

bool bigint::operator<(const bigint &b) const {
	if (value.size() != b.value.size())
		return value.size() < b.value.size();
	return value < b.value;
}

bigint bigint::operator<<(int n) const {
	if (*this == 0) return 0;
	return bigint(value + std::string(n, '0'));
}

bigint &bigint::operator<<=(int n) {
	if (*this != 0)
		value += std::string(n, '0');
	return *this;
}

bigint &bigint::operator<<=(const bigint &n) {
	return *this <<= std::stoi(n.value);
}

bigint bigint::operator>>(int n) const {
	if ((int)value.size() <= n) return 0;
	return bigint(value.substr(0, value.size() - n));
}

bigint &bigint::operator>>=(int n) {
	if ((int)value.size() <= n)
		value = "0";
	else
		value = value.substr(0, value.size() - n);
	return *this;
}

bigint &bigint::operator>>=(const bigint &n) {
	return *this >>= std::stoi(n.value);
}
