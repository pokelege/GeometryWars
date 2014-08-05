#include "Asteroid.h"

Asteroid::Asteroid()
{
	asteroidDiameter = 1;
}

Asteroid::Asteroid(const float& diameter)
{
	asteroidDiameter = diameter;
}

Engine::Vector2 Asteroid::getPosition() const
{
	return asteroidPosition;
}

void Asteroid::Draw(Core::Graphics& graphics)
{
	graphics.SetColor(DARKGREY);
	Engine::Vector2 draw[] =
	{
		Engine::Vector2(asteroidDiameter, 0) + asteroidPosition,
		Engine::Vector2(-(asteroidDiameter), 0) + asteroidPosition,

		Engine::Vector2(-(asteroidDiameter), 0) + asteroidPosition,
		Engine::Vector2(0, asteroidDiameter) + asteroidPosition,

		Engine::Vector2(0, asteroidDiameter) + asteroidPosition,
		Engine::Vector2(0, -(asteroidDiameter)) + asteroidPosition,

		Engine::Vector2(0, -(asteroidDiameter)) + asteroidPosition,
		Engine::Vector2(asteroidDiameter, 0) + asteroidPosition
	};

	unsigned int drawsize = sizeof(draw) / (sizeof(*draw) * 2);

	graphics.DrawLines(drawsize, *draw);
}