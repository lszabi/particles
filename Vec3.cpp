#include "Vec3.h"
#include <cmath>

Vec3 Vec3::operator=(const Vec3 &other) {
	x = other.x;
	y = other.y;
	z = other.z;
	return *this;
}

Vec3 Vec3::operator=(const double i) {
	x = i;
	y = 0;
	z = 0;
	return *this;
}

Vec3 Vec3::operator+(const Vec3 &other) const {
	return Vec3(x + other.x, y + other.y, z + other.z);
}

Vec3 Vec3::operator-(const Vec3 &other) const {
	return Vec3(x - other.x, y - other.y, z - other.z);
}

Vec3 Vec3::operator*(const double n) const {
	return Vec3(x * n, y * n, z * n);
}

double Vec3::operator*(const Vec3 &other) const {
	return x * other.x + y * other.y + z * other.z;
}

Vec3 Vec3::operator^(const Vec3 &other) const {
	// y1*z2 - z1*y2	;	-x1*z2 + z1*x2	;	x1*y2 - y1*x2
	return Vec3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
}

double Vec3::length() const {
	return sqrt(x * x + y * y + z * z);
}

Vec3 Vec3::operator+=(const Vec3 &other) {
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

Vec3 Vec3::operator-=(const Vec3 &other) {
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

Vec3 Vec3::operator*=(const double n) {
	x *= n;
	y *= n;
	z *= n;
	return *this;
}

Vec3 Vec3::operator^=(const Vec3 &other) {
	*this = *this ^ other;
	return *this;
}

