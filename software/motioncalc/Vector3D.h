
#pragma once
class Vector3D {
public:
	long double x;
	long double y;
	long double z;
	Vector3D();
	Vector3D(long double x, long double y, long double z);
	Vector3D& operator=(Vector3D x);
	Vector3D& operator+=(const Vector3D& y);
	Vector3D& operator-=(const Vector3D& y);
	long double getLength() const;
};

inline bool operator==(const Vector3D& x, const Vector3D& y);

inline bool operator!=(const Vector3D& x, Vector3D& y);

static inline Vector3D operator+(const Vector3D x, const Vector3D& y) {
	return Vector3D(x.x + y.x, x.y + y.y, x.z + y.z);
}

inline Vector3D operator-(Vector3D x, const Vector3D& y) {
	return x -= y;
}