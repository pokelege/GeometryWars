#include "Boundary.h"
#include "Collision.h"

Boundary::Boundary()
{
	totalBoundaries++;
}

Boundary::Boundary(const Engine::Vector2& point1, const Engine::Vector2& point2)
{
	this->point1 = point1;
	this->point2 = point2;
	totalBoundaries++;
}
Boundary::~Boundary()
{
	totalBoundaries--;
}

Boundary::operator const float *() const
{
	return (const float *)point1;
}

Boundary::operator float *()
{
	return (float *)point1;
}

bool Boundary::boundaryIsCollidedCCW(const Engine::Vector2& point, const Engine::Vector2& velocity) const
{
	return Engine::isCollidedCCW(point, velocity, point1, point2);
}

bool Boundary::boundaryIsCollidedCW(const Engine::Vector2& point, const Engine::Vector2& velocity) const
{
	return Engine::isCollidedCW(point, velocity, point1, point2);
}

Engine::Vector2 Boundary::boundaryCollisionVelocity(const Engine::Vector2& point, const Engine::Vector2& velocity) const
{
	return Engine::collisionVelocity(point, velocity, point1, point2);
}

void Boundary::DrawBound(Core::Graphics& graphics)
{
	graphics.SetColor(WHITE);
	graphics.DrawLines(1, point1);
}