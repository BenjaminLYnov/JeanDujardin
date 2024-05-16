#ifndef QUATERNION_H
#define QUATERNION_H

#include "KMath.h"
#include "MathVector.h"

#include <cmath>

template<typename T>
struct Quaternion 
{
	Quaternion(const T& angle, const Vec3<T>& axis)
		: x(std::sin(angle / 2)* axis.x)
		, y(std::sin(angle / 2)* axis.y)
		, z(std::sin(angle / 2)* axis.z)
		, w(std::cos(angle / 2))
	{
		_normalize();
	}

	/* euler angles in rad */
	Quaternion(const Vec3<T>& euler)
	{
		T roll = euler.x;
		T pitch = euler.y;
		T yaw = euler.z;

		T cr = cos(roll * 0.5);
		T sr = sin(roll * 0.5);
		T cp = cos(pitch * 0.5);
		T sp = sin(pitch * 0.5);
		T cy = cos(yaw * 0.5);
		T sy = sin(yaw * 0.5);

		x = sr * cp * cy - cr * sp * sy;
		y = cr * sp * cy + sr * cp * sy;
		z = cr * cp * sy - sr * sp * cy;
		w = cr * cp * cy + sr * sp * sy;

		_normalize();
	}

	Vec3<T> ToEuler() 
	{
		return Vec3<T>(
			atan2( 2 * x * w  + 2 * y * z , 1 - 2 * x * x - 2 * y * y)
			, F_PI * -0.5f + 2 * atan2(sqrt(1 + 2 * y * w - 2 * x * z), sqrt(1 - 2 * y * w + 2 * x * z))
			, atan2(2 * z * w + 2 * x * y, 1 - 2 * y * y - 2 * z * z)
		);
	}

private:

	void _normalize()
	{
		T n = sqrt(x * x + y * y + z * z + w * w);
		x /= n;
		y /= n;
		z /= n;
		w /= n;
	}

public:
	T x;
	T y;
	T z;
	T w;
};

using QuatF = Quaternion<float>;

#endif // QUATERNION_H