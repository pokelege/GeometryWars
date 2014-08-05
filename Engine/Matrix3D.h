#ifndef MATRIX3D
#define MATRIX3D

#include "Vector2D.h"

#include "Vector3D.h"

#include "Logger.h"

namespace Engine
{
	class Matrix3
	{
		float matrix3[3][3];

	public:
		explicit Matrix3
			(
			const float& r0c0 = 1, const float& r0c1 = 0, const float& r0c2 = 0,
			const float& r1c0 = 0, const float& r1c1 = 1, const float& r1c2 = 0,
			const float& r2c0 = 0, const float& r2c1 = 0, const float& r2c2 = 1)
		{
			matrix3[0][0] = r0c0;
			matrix3[0][1] = r0c1;
			matrix3[0][2] = r0c2;
			matrix3[1][0] = r1c0;
			matrix3[1][1] = r1c1;
			matrix3[1][2] = r1c2;
			matrix3[2][0] = r2c0;
			matrix3[2][1] = r2c1;
			matrix3[2][2] = r2c2;
		}

		explicit Matrix3(const Vector2& c0, const Engine::Vector2& c1)
		{
			matrix3[0][0] = c0.getX();
			matrix3[0][1] = c1.getX();
			matrix3[0][2] = 0;
			matrix3[1][0] = c0.getY();
			matrix3[1][1] = c1.getY();
			matrix3[1][2] = 0;
			matrix3[2][0] = 0;
			matrix3[2][1] = 0;
			matrix3[2][2] = 1;
		}

		explicit Matrix3(const Vector2& c0, const Engine::Vector2& c1, const Engine::Vector2& c2)
		{
			matrix3[0][0] = c0.getX();
			matrix3[0][1] = c1.getX();
			matrix3[0][2] = c2.getX();
			matrix3[1][0] = c0.getY();
			matrix3[1][1] = c1.getY();
			matrix3[1][2] = c2.getY();
			matrix3[2][0] = 0;
			matrix3[2][1] = 0;
			matrix3[2][2] = 1;
		}

		inline operator const float*() const
		{
			return *matrix3;
		}

		inline operator float*()
		{
			return *matrix3;
		}

		inline float getCell(const unsigned short& row, const unsigned short& column) const
		{
			ASSERT((row < 3 || column < 3), "Out of bounds");
			return matrix3[row][column];
		}

		inline Vector2 getTranslation()
		{
			return Vector2(matrix3[0][2], matrix3[1][2]);
		}

		inline static Matrix3 rotation(const float& angle)
		{
			return Matrix3(cosf(angle), -sinf(angle), 0, sinf(angle), cos(angle), 0);
		}

		inline static Matrix3 scale(const float& scale)
		{
			return Matrix3(scale, 0, 0, 0, scale);
		}

		inline static Matrix3 scaleX(const float& scale)
		{
			return Matrix3(scale);
		}

		inline static Matrix3 scaleY(const float& scale)
		{
			return Matrix3(1, 0, 0, 0, scale);
		}

		inline static Matrix3 Translation(const float& x, const float& y)
		{
			return Matrix3(1, 0, x, 0, 1, y);
		}

		inline static Matrix3 Translation(const Vector2& t)
		{
			return Matrix3(1, 0, *t, 0, 1, *((const float*)t + 1));
		}
	};

	inline Matrix3 operator*(const Matrix3& matrix1, const Matrix3& matrix2)
	{	
		Vector3 r0(matrix1.getCell(0, 0), matrix1.getCell(0, 1), matrix1.getCell(0, 2));
		Vector3 r1(matrix1.getCell(1, 0), matrix1.getCell(1, 1), matrix1.getCell(1, 2));
		Vector3 r2(matrix1.getCell(2, 0), matrix1.getCell(2, 1), matrix1.getCell(2, 2));

		Vector3 c0(matrix2.getCell(0, 0), matrix2.getCell(1, 0), matrix2.getCell(2, 0));
		Vector3 c1(matrix2.getCell(0, 1), matrix2.getCell(1, 1), matrix2.getCell(2, 1));
		Vector3 c2(matrix2.getCell(0, 2), matrix2.getCell(1, 2), matrix2.getCell(2, 2));

		return Matrix3(Dot(r0, c0), Dot(r0, c1), Dot(r0, c2), Dot(r1, c0), Dot(r1, c1), Dot(r1, c2), Dot(r2, c0), Dot(r2, c1), Dot(r2, c2));
	}

	inline Vector3 operator*(const Matrix3& matrix, const Vector2& vector)
	{
		Vector3 r0(matrix.getCell(0, 0), matrix.getCell(0, 1), matrix.getCell(0, 2));
		Vector3 r1(matrix.getCell(1, 0), matrix.getCell(1, 1), matrix.getCell(1, 2));
		Vector3 r2(matrix.getCell(2, 0), matrix.getCell(2, 1), matrix.getCell(2, 2));

		Vector3 c0(vector.getX(), vector.getY(), 1);

		return Vector3(Dot(r0, c0), Dot(r1, c0), Dot(r2, c0));
	}

	inline Vector3 operator*(const Matrix3& matrix, const Vector3& vector)
	{
		Vector3 c0(vector.getX(), vector.getY(), vector.getZ());

		return Vector3(Dot(Vector3(matrix.getCell(0, 0), matrix.getCell(0, 1), matrix.getCell(0, 2)), c0),
			Dot(Vector3(matrix.getCell(1, 0), matrix.getCell(1, 1), matrix.getCell(1, 2)), c0),
			Dot(Vector3(matrix.getCell(2, 0), matrix.getCell(2, 1), matrix.getCell(2, 2)), c0));
	}
}
#endif