#pragma once

#include "MathVector.h"

template<typename T>
struct Point2d
{
    Point2d(const T& x_ = 0, const T& y_ = 0) : x(x_), y(y_) {};
    Point2d(const Point2d& pt) : x(pt.x), y(pt.y) {};

    T x;
    T y;
};

template<typename T>
struct Point3d
{
    Point3d(const T& x_ = 0, const T& y_ = 0, const T& z_ = 0) : x(x_), y(y_), z(z_) {};
    Point3d(const Point3d& pt) : x(pt.x), y(pt.y), z(pt.z) {};

    T x;
    T y;
    T z;
};

template<typename T>
struct Color3
{
    Color3(const T& r_ = 0, const T& g_ = 0, const T& b_ = 0) : r(r_), g(g_), b(b_) {};
    Color3(const Color3& col) : r(col.r), g(col.g), b(col.b) {};

    T r;
    T g;
    T b;
};

template<typename T>
struct Color4
{
    Color4(const T& r_ = 0, const T& g_ = 0, const T& b_ = 0, const T& a_ = 0) : r(r_), g(g_), b(b_), a(a_) {};
    Color4(const Color4& col) : r(col.r), g(col.g), b(col.b), a(col.a) {};

    T r;
    T g;
    T b;
    T a;
};

template<typename T>
struct Vertex
{
    Point3d<T> position;
    Point3d<T> normal;
    Color4<T> color;
};
using VertexF = Vertex<float>;