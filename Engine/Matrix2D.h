#ifndef MATRIX2D
#define MATRIX2D

#include "Vector2D.h"
#include "Matrix3D.h"
#include "Logger.h"
namespace Engine
{
	class Matrix2
	{
		float matrix2[2][2];

	public:
		explicit Matrix2(const float& r0c0 = 1, const float& r0c1 = 0,
			const float& r1c0 = 0, const float& r1c1 = 1)
		{
			matrix2[0][0] = r0c0;
			matrix2[0][1] = r0c1;
			matrix2[1][0] = r1c0;
			matrix2[1][1] = r1c1;
		}

		explicit Matrix2(const Vector2& c0, const Vector2& c1)
		{
			matrix2[0][0] = c0.getX();
			matrix2[0][1] = c1.getX();
			matrix2[1][0] = c0.getY();
			matrix2[1][1] = c1.getY();
		}

		inline operator const float*() const
		{
			return *matrix2;
		}

		inline operator float*()
		{
			return *matrix2;
		}

		inline float getCell(const unsigned short& row, const unsigned short& column) const
		{
			ASSERT((row < 2 || column < 2), "Problem with get cell.")
			return matrix2[row][column];
		}

		inline operator Matrix3() const
		{
			return Matrix3(matrix2[0][0], matrix2[0][1], 0, matrix2[1][0], matrix2[1][1]);
		}

		inline static Matrix2 rotation(const float& angle)
		{
			return Matrix2(cosf(angle), -sinf(angle), sinf(angle), cosf(angle));
		}

		//inline static float rotationAngle(const Matrix2& rotation)
		//{
		//	
		//}

		inline static Matrix2 scale(const float& scale)
		{
			return Matrix2(scale, 0, 0, scale);
		}

		inline static Matrix2 scaleX(const float& scale)
		{
			return Matrix2(scale);
		}

		inline static Matrix2 scaleY(const float& scale)
		{
			return Matrix2(1, 0, 0, scale);
		}
	};

	inline Matrix2 operator*(const Matrix2& matrix1, const Matrix2& matrix2)
	{
		Vector2 r0(matrix1.getCell(0, 0), matrix1.getCell(0, 1));
		Vector2 r1(matrix1.getCell(1, 0), matrix1.getCell(1, 1));

		Vector2 c0(matrix2.getCell(0, 0), matrix2.getCell(1, 0));
		Vector2 c1(matrix2.getCell(0, 1), matrix2.getCell(1, 1));

		return Matrix2(Dot(r0, c0), Dot(r0, c1), Dot(r1, c0), Dot(r1, c1));
	}

	inline Vector2 operator*(const Matrix2& matrix, const Vector2& vector)
	{
		return Vector2(Dot(Vector2(matrix.getCell(0, 0), matrix.getCell(0, 1)), vector),
			Dot(Vector2(matrix.getCell(1, 0), matrix.getCell(1, 1)), vector));
	}
}
#endif