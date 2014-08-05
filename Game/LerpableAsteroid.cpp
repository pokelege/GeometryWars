#include "LerpableAsteroid.h"

LerpableAsteroid::LerpableAsteroid(const float& diameter = 1, const int& RESWIDTH = 0, const int& RESHEIGHT = 0)
{
	asteroidDiameter = diameter;
	waypoints[0] = Engine::Vector2((float)RESWIDTH / 4, (float)RESHEIGHT / 4);
	waypoints[1] = Engine::Vector2((float)RESWIDTH - (float)RESWIDTH / 4, (float)RESHEIGHT / 4);
	waypoints[2] = Engine::Vector2((float)RESWIDTH / 4, (float)RESHEIGHT - ((float)RESHEIGHT / 4));
	waypoints[3] = Engine::Vector2((float)RESWIDTH - ((float)RESWIDTH / 4), (float)RESHEIGHT - ((float)RESHEIGHT / 4));
	asteroidPosition = waypoints[0];
	point = 0;
}

void LerpableAsteroid::move(const float& velocity)
{
	Engine::Vector2 a;
	Engine::Vector2 b;

	if (point == MAXWAYPOINTS)
	{
		point = 0;
	}

	if (point == MAXWAYPOINTS - 1)
	{
		a = waypoints[point];
		b = waypoints[0];
	}

	else
	{
		a = waypoints[point];
		b = waypoints[point + 1];
	}

	float length = Engine::Length(a - b);

	float length1 = Engine::Length(asteroidPosition - waypoints[point]);

	float length2 = Engine::Length(Engine::Normalized(a - b) * velocity) + length1;

	if (length2 / length > 1)
	{
		point++;
		extraMove(length2 - length);
	}
	else
	{
		asteroidPosition = Engine::LERP(a, b, length2 / length);
	}
}

void LerpableAsteroid::extraMove(const float& extralength)
{
	Engine::Vector2 a;
	Engine::Vector2 b;

	if (point == MAXWAYPOINTS)
	{
		point = 0;
	}

	if (point == MAXWAYPOINTS - 1)
	{
		a = waypoints[point];
		b = waypoints[0];
	}
	else
	{
		a = waypoints[point];
		b = waypoints[point + 1];
	}

	float length = Engine::Length(a - b);

	if (extralength / length > 1)
	{
		point++;
		extraMove(extralength - length);
	}
	else
	{
		asteroidPosition = Engine::LERP(a, b, extralength / length);
	}
}