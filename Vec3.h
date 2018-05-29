#pragma once

class Vec3 {
public:
	double x, y, z;
	// constructors
	Vec3() : x(0), y(0), z(0) {};
	Vec3(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {};
	Vec3(const Vec3 &other) : x(other.x), y(other.y), z(other.z) {};
	Vec3(double i) : x(i), y(0), z(0) {};
	~Vec3() {};
	// operators
	Vec3 operator+(const Vec3 &) const;
	Vec3 operator-(const Vec3 &) const;
	Vec3 operator*(const double) const;
	double operator*(const Vec3 &) const;
	Vec3 operator^(const Vec3 &) const;
	double length() const;
	// assignment operators
	Vec3 operator=(const Vec3 &);
	Vec3 operator=(const double);
	Vec3 operator+=(const Vec3 &);
	Vec3 operator-=(const Vec3 &);
	Vec3 operator*=(const double);
	Vec3 operator^=(const Vec3 &);
};