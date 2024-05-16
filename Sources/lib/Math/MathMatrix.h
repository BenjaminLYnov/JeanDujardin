#ifndef MATH_MATRIX_H
#define MATH_MATRIX_H

#include "Quaternion.h"
#include "Transform.h"

#include <array>

const int MAT_4_SIZE = 4;

template<typename T>
class Mat4 
{
public:
	Mat4() 
	{
		for (int row = 0; row < MAT_4_SIZE; ++row)
		{
			for (int col = 0; col < MAT_4_SIZE; ++col)
			{
				m_coefs[row + col * MAT_4_SIZE] = 0;
			}
		}
	}

	Mat4(const Transform<T>& transform) 
	{
		Mat4 translate = MakeTranslate(Vec4<T>(transform.position));
		Mat4 rotate = MakeRotate(transform.rotation);
		Mat4 scale = MakeScale(Vec4<T>(transform.scale));

		Mat4 temp = translate * rotate * scale;

		m_coefs = temp.m_coefs;
	}

	static Mat4<T> Identity() 
	{
		Mat4<T> result;

		for (int row = 0; row < MAT_4_SIZE; ++row)
		{
			result(row, row) = 1;
		}
		return result;
	}

	//static Mat4<T>

	static Mat4<T> MakeProjection(const T& aspect, const T& fov, const T& nearDistance, const T& farDistance)
	{
		Mat4<T> result;
		
		result(0, 0) = 1.f / (aspect * std::tan(fov / 2.f));
		result(1, 1) = 1.f / (std::tan(fov / 2.f));
		result(2, 2) = -(farDistance + nearDistance) / (farDistance - nearDistance);
		result(2, 3) = -(2.f * farDistance * nearDistance) / (farDistance - nearDistance);
		result(3, 2) = -1.f;

		return result;
	}

	// TRANSLATION MATRICES

	static Mat4<T> MakeTranslate(const Vec4<T>& vec, const Mat4<T>& mat) 
	{
		Mat4<T> result = mat;
		result.Translate(vec);
		return result;
	}

	static Mat4<T> MakeTranslate(const Vec4<T>& vec)
	{
		Mat4<T> result = Identity();
		result.Translate(vec);
		return result;
	}

	void Translate(const Vec4<T>& vec) 
	{
		operator()(0, 3) += vec.x;
		operator()(1, 3) += vec.y;
		operator()(2, 3) += vec.z;
	}

	// SCALE MATRICES

	static Mat4<T> MakeScale(const Vec4<T>& vec, const Mat4<T>& mat) 
	{
		Mat4<T> result = mat;
		result.Scale(vec);
		return result;
	}

	static Mat4<T> MakeScale(const Vec4<T>& vec)
	{
		Mat4<T> result = Identity();
		result.Scale(vec);
		return result;
	}

	void Scale(const Vec4<T>& vec) 
	{
		operator()(0, 0) *= vec.x;
		operator()(1, 1) *= vec.y;
		operator()(2, 2) *= vec.z;
		operator()(3, 3) *= vec.w;
	}

	// ROTATE MATRICES

	static Mat4<T> MakeRotate(const T& angle, const Vec3<T>& axis)
	{
		Quaternion<T> q(angle, axis);
		return MakeRotate(q);
	}

	/* euler is a vec3 of rotation along each axis in radians */
	static Mat4<T> MakeRotate(const Vec3<T>& euler)
	{
		Quaternion<T> q(euler);
		return MakeRotate(q);
	}

	static Mat4<T> MakeRotate(const Quaternion<T>& quat)
	{
		Mat4<T> result = Identity();

		result(0, 0) = 1 - 2 * quat.y * quat.y - 2 * quat.z * quat.z;
		result(0, 1) = 2 * quat.x * quat.y - 2 * quat.z * quat.w;
		result(0, 2) = 2 * quat.x * quat.z + 2 * quat.y * quat.w;

		result(1, 0) = 2 * quat.x * quat.y + 2 * quat.z * quat.w;
		result(1, 1) = 1 - 2 * quat.x * quat.x - 2 * quat.z * quat.z;
		result(1, 2) = 2 * quat.y * quat.z - 2 * quat.x * quat.w;

		result(2, 0) = 2 * quat.x * quat.z - 2 * quat.y * quat.w;
		result(2, 1) = 2 * quat.y * quat.z + 2 * quat.x * quat.w;
		result(2, 2) = 1 - 2 * quat.x * quat.x - 2 * quat.y * quat.y;

		return result;
	}

	T& operator()(int row, int col) { return m_coefs[row + col * MAT_4_SIZE]; }
	const T& operator()(int row, int col) const { return m_coefs[row + col * MAT_4_SIZE]; }

	const T* data() const { return m_coefs.data(); }

private:
	std::array<T, MAT_4_SIZE * MAT_4_SIZE> m_coefs;
};

using Mat4F = Mat4<float>;

template<typename T>
Mat4<T> operator*(const Mat4<T>& op1, const Mat4<T>& op2)
{
	Mat4<T> result;
	for (int row = 0; row < MAT_4_SIZE; ++row)
	{
		for (int col = 0; col < MAT_4_SIZE; ++col)
		{
			T temp = 0;
			for (int k = 0; k < MAT_4_SIZE; ++k)
			{
				temp += ( op1(row, k) * op2(k, col) );
			}
			result(row, col) = temp;
		}
	}

	return result;
}

template<typename T>
Mat4<T> operator*(const Mat4<T>& op1, const T& op2)
{
	Mat4<T> result;
	for (int row = 0; row < MAT_4_SIZE; ++row)
	{
		for (int col = 0; col < MAT_4_SIZE; ++col)
		{
			result(row, col) = op1(row, col) * op2;
		}
	}

	return result;
}

template<typename T>
Mat4<T> operator*(const T& op1, const Mat4<T>& op2)
{
	return op2 * op1;
}

template<typename T>
Mat4<T> operator*(const Mat4<T>& mat, const Vec4<T>& vec)
{
	return Vec4<T>(
		mat(0, 0) * vec.x + mat(0, 1) * vec.y + mat(0, 2) * vec.z + mat(0, 3) * vec.w
		, mat(1, 0) * vec.x + mat(1, 1) * vec.y + mat(1, 2) * vec.z + mat(1, 3) * vec.w
		, mat(2, 0) * vec.x + mat(2, 1) * vec.y + mat(2, 2) * vec.z + mat(2, 3) * vec.w
		, mat(3, 0) * vec.x + mat(3, 1) * vec.y + mat(3, 2) * vec.z + mat(3, 3) * vec.w
	);
}

#endif // MATH_MATRIX_H