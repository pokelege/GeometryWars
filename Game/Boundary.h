#ifndef BOUNDARY
#define BOUNDARY
#include "Colors.h"
#include "Core.h"
#include "Vector2D.h"

class Boundary
{
	Engine::Vector2 point1;
	Engine::Vector2 point2;

public:
	static unsigned int totalBoundaries;

	explicit Boundary();
	
	explicit Boundary(const Engine::Vector2& point1, const Engine::Vector2& point2);
	
	~Boundary();

	operator const float *() const;

	operator float *();

	bool boundaryIsCollidedCCW(const Engine::Vector2& point, const Engine::Vector2& velocity) const;

	bool boundaryIsCollidedCW(const Engine::Vector2& point, const Engine::Vector2& velocity) const;

	Engine::Vector2 boundaryCollisionVelocity(const Engine::Vector2& point, const Engine::Vector2& velocity) const;

	void DrawBound(Core::Graphics& graphics);
};
#endif