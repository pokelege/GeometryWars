#ifndef Vector3D
#define Vector3D

#include <iostream>

namespace Engine
{
	class Vector3
	{
		float x;
		float y;
		float z;
	public:
		explicit Vector3(const float x = 0, const float y = 0, const float z = 0)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}
		
		friend std::ostream& operator<<(std::ostream& stream, const Vector3& vector);
		friend float Dot(const Vector3& vector1, const Vector3& vector2);

		inline operator const float *() const
		{
			return &x;
		}

		inline operator float *()
		{
			return &x;
		}

		inline operator Vector2()
		{
			return Vector2(x, y);
		}

		inline float getX() const
		{
			return x;
		}

		inline float getY() const
		{
			return y;
		}

		inline float getZ() const
		{
			return z;
		}

		inline float Dot(const Vector3& vector) const
		{
			return (x * vector.x) + (y * vector.y) + (z * vector.z);
		}
	};

	inline float Dot(const Vector3& vector1, const Vector3& vector2)
	{
		return (vector1.x * vector2.x) + (vector1.y * vector2.y) + (vector1.z * vector2.z);
	}
}
#endif