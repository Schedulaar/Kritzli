
#pragma once
class Vector3D {
public:
	double x;
	double y;
	double z;
	Vector3D();
	Vector3D(double x, double y, double z);
	Vector3D& operator=(Vector3D x);
	Vector3D& operator+=(const Vector3D& y);
	Vector3D& operator-=(const Vector3D& y);
	double getLength() const;
};

inline bool operator==(const Vector3D& x, const Vector3D& y);

inline bool operator!=(const Vector3D& x, Vector3D& y);

static inline Vector3D operator+(const Vector3D x, const Vector3D& y) {
 return Vector3D(x.x + y.x, x.y + y.y, x.z + y.z);
}

static inline Vector3D operator*(const double x, const Vector3D& y) {
 return Vector3D(x * y.x, x * y.y, x* y.z);
}

inline Vector3D operator-(Vector3D x, const Vector3D& y) {
	return x -= y;
}
