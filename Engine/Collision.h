#ifndef COLLISION
#define COLLISION
#include "Vector2D.h"

namespace Engine
{
	inline bool isCollidedCCW(const Engine::Vector2& point, const Engine::Vector2& velocity, const Engine::Vector2& point1, const Engine::Vector2& point2)
	{
		if (Engine::Dot((point1 - point), (point2 - point)) <= 0)
		{
			Engine::Vector2 normal = Engine::PerpCCW(Engine::Normalized(point2 - point1));

			return(Engine::Dot(point - point1, normal) >= 0 && Engine::Dot(((point + velocity) - point1), normal) <= 0);
		}
		else
		{
			return false;
		}
	}

	inline bool isCollidedCW(const Engine::Vector2& point, const Engine::Vector2& velocity, const Engine::Vector2& point1, const Engine::Vector2& point2)
	{
		if (Engine::Dot((point1 - point), (point2 - point)) <= 0)
		{
			Engine::Vector2 normal = Engine::PerpCW(Engine::Normalized(point2 - point1));

			return(Engine::Dot(point - point1, normal) > 0 && Engine::Dot(((point + velocity) - point1), normal) < 0);
		}
		else
		{
			return false;
		}
	}

	inline bool isCollidedPoint(const Engine::Vector2& point, const Engine::Vector2& velocity, const Engine::Vector2& pointblock)
	{
		Engine::Vector2 test = point - pointblock;
		if (Engine::Length(test) != 0)
		{
			Engine::Vector2 normal = Engine::Normalized(test);

			return(Engine::Dot(point - pointblock, normal) > 0 && Engine::Dot(((point + velocity) - pointblock), normal) < 0);
		}
		else
		{
			return true;
		}
	}

	inline Engine::Vector2 collisionVelocity(const Engine::Vector2& point, const Engine::Vector2& velocity, const Engine::Vector2& point1, const Engine::Vector2& point2)
	{
		Engine::Vector2 p = point2 - point1;

		if (isCollidedCCW(point, velocity, point1, point2))
		{
			Engine::Vector2 n = Engine::PerpCCW(Engine::Normalized(p));

			return -2 * (Engine::Dot(velocity, n) * n);
		}
		else if (isCollidedCW(point, velocity, point1, point2))
		{
			Engine::Vector2 n = Engine::PerpCW(Engine::Normalized(p));
			return -2 * (Engine::Dot(velocity, n) * n);
		}
		else
		{
			return Engine::Vector2();
		}
	}
}
#endif