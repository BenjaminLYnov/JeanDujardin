#ifndef MATH_VECTOR_H
#define MATH_VECTOR_H

#include "lib/Logger/logger.h"

template<typename T>
struct Point3d;

template<typename T>
struct Vec2
{
    Vec2(const T& x_ = 0, const T& y_ = 0) : x(x_), y(y_) {};
    Vec2(const Vec2& v) : x(v.x), y(v.y) {};

    T x;
    T y;
};

template<typename T>
struct Vec3
{
    Vec3(const T& x_ = 0, const T& y_ = 0, const T& z_ = 0) : x(x_), y(y_), z(z_) {};
    Vec3(const Vec3& v) : x(v.x), y(v.y), z(v.z) {};

    T x;
    T y;
    T z;
};

template<typename T>
struct Vec4
{
    Vec4(const T& x_ = 0, const T& y_ = 0, const T& z_ = 0, const T& w_ = 0) : x(x_), y(y_), z(z_), w(w_) {}
    Vec4(const Vec4& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}
    explicit Vec4(const Vec3<T>& v, const T& w_ = 1.f) : x(v.x), y(v.y), z(v.z), w(w_) {}
    explicit Vec4(const Point3d<T>& v, const T& w_ = 1.f) : x(v.x), y(v.y), z(v.z), w(w_) {}

    T x;
    T y;
    T z;
    T w;
};

using Vec4F = Vec4<float>;

#endif // MATH_VECTOR_H