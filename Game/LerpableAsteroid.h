#ifndef LERPABLEASTEROID
#define LERPABLEASTEROID
#include "Asteroid.h"

#define MAXWAYPOINTS 4

class LerpableAsteroid : public Asteroid
{
	Engine::Vector2 waypoints[MAXWAYPOINTS];

	unsigned int point;

public:
	LerpableAsteroid(const float& diameter, const int& RESWIDTH, const int& RESHEIGHT);

	void move(const float& velocity);
	void extraMove(const float& extralength);
};


#endif