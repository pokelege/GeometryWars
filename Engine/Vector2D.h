#ifndef Vector2D
#define Vector2D
#include "ExportHeader.h"
#include <iostream>
#include "Logger.h"

namespace Engine
{
	class ENGINE_SHARED Vector2
	{
		float x;
		float y;
	public:
		explicit Vector2(const float& x1 = 0, const float& y1 = 0)
		{
			x = x1;
			y = y1;
		}

		friend Vector2 operator+(const Vector2& vector1, const Vector2& vector2);
		friend Vector2 operator-(const Vector2& vector1, const Vector2& vector2);
		friend Vector2 operator*(const float& multiply, const Vector2& vector);
		friend Vector2 operator*(const Vector2& vector, const float& multiply);
		friend Vector2 operator/(const Vector2& vector, const float& divide);
		friend std::ostream& operator<<(std::ostream& stream, const Vector2& vector);
		friend Vector2 LERP(const Vector2& vector1, const Vector2& vector2, const float& percent);
		friend float Length(const Vector2& vector);
		friend float LengthSquared(const Vector2& vector);
		friend Vector2 PerpCW(const Vector2& vector);
		friend Vector2 PerpCCW(const Vector2& vector);
		friend float Dot(const Vector2& vector1, const Vector2& vector2);
		friend float Cross(const Vector2& vector);

		inline operator const float *() const
		{
			return &x;
		}

		inline operator float *()
		{
			return &x;
		}

		inline float getX() const
		{
			return x;
		}

		inline float getY() const
		{
			return y;
		}

		inline float Dot(const Vector2& vector) const
		{
			return (x * vector.x) + (y * vector.y);
		}

		inline float Cross(const Vector2& vector) const
		{
			return (Length(*this) * Length(vector)) / 2;
		}
	};

	inline Vector2 operator+(const Vector2& vector1, const Vector2& vector2)
	{
		return Vector2(vector1.x + vector2.x, vector1.y + vector2.y);
	}

	inline Vector2 operator-(const Vector2& vector1, const Vector2& vector2)
	{
		return Vector2(vector1.x - vector2.x, vector1.y - vector2.y);
	}

	inline Vector2 operator*(const float& multiply, const Vector2& vector)
	{
		return Vector2(multiply * vector.x, multiply * vector.y);
	}

	inline Vector2 operator*(const Vector2& vector, const float& multiply)
	{
		return Vector2(multiply * vector.x, multiply * vector.y);
	}

	inline Vector2 operator/(const Vector2& vector, const float& divide)
	{
		ASSERT((divide != 0), "Divided by 0...")
		return Vector2(vector.x / divide, vector.y / divide);
	}

	inline std::ostream& operator<<(std::ostream& stream, const Vector2& vector)
	{
		return stream << "{ " << vector.x << ", " << vector.y << " }";
	}

	inline Vector2 LERP(const Vector2& vector1, const Vector2& vector2, const float& percent)
	{

		return ((1 - percent) * vector1) + (percent * vector2);
	}

	inline float Length(const Vector2& vector)
	{
		return sqrtf((vector.x * vector.x) + (vector.y * vector.y));
	}

	inline float LengthSquared(const Vector2& vector)
	{
		return (vector.x * vector.x) + (vector.y * vector.y);
	}

	inline Vector2 Normalized(const Vector2& vector)
	{
		ASSERT(Length(vector) != 0, "Length is 0 therefore divide by 0...")
		return vector / Length(vector);
	}

	inline Vector2 PerpCW(const Vector2& vector)
	{
		return Vector2(vector.y, -vector.x);
	}

	inline Vector2 PerpCCW(const Vector2& vector)
	{
		return Vector2(-vector.y, vector.x);
	}

	inline float Dot(const Vector2& vector1, const Vector2& vector2)
	{
		return (vector1.x * vector2.x) + (vector1.y * vector2.y);
	}

	inline float Cross(const Vector2& vector1, Vector2& vector2)
	{
		return (Length(vector1) * Length(vector2)) / 2;
	}
}
#endif