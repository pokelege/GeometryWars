#ifndef WALLS
#define WALLS
#include "Boundary.h"
#include "Vector2D.h"
#include "RandomItemsGenerator.h"
using namespace Engine;

class Walls
{
	Boundary boundary1;
	Boundary boundary2;
	Boundary boundary3;
	Boundary boundary4;
	RandomItemsGenerator rand;

public:
	explicit Walls(const float& RESWIDTH, const float& RESHEIGHT);
	
	explicit Walls(const int& RESWIDTH, const int& RESHEIGHT);

	Engine::Vector2 getCollisionVelocity(const Engine::Vector2& point, const Engine::Vector2& velocity) const;

	void DrawAllBounds(Core::Graphics& graphics);
};

#endif