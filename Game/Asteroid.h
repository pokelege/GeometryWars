#ifndef ASTEROID
#define ASTEROID
#include "Core.h"
#include "Colors.h"
#include "Vector2D.h"
#include "Matrix3D.h"
#include "RandomItemsGenerator.h"

class Asteroid
{
protected:
	Engine::Vector2 asteroidPosition;

	float asteroidDiameter;

public:
	Asteroid();

	Asteroid(const float& diameter);

	Engine::Vector2 getPosition() const;

	virtual void Draw(Core::Graphics& graphics);
};

#endif