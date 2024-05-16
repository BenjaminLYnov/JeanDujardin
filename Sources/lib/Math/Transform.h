#ifndef TRANSFORM_H
#define TRANSFORM_H

template<typename T>
struct Transform 
{
	Transform(const Vec3<T>& position_, const Vec3<T>& rotation_, const Vec3<T>& scale_)
		: position(position_)
		, rotation(Quaternion<T>(rotation_))
		, scale(scale_)
	{}

	Transform(const Vec3<T>& position_, const Quaternion<T>& rotation_, const Vec3<T>& scale_)
		: position(position_)
		, rotation(rotation_)
		, scale(scale_)
	{}

	Vec3<T> position;
	Vec3<T> scale;
	Quaternion<T> rotation;
};

using TransformF = Transform<float>;
using TransformD = Transform<double>;

#endif // TRANSFORM_H