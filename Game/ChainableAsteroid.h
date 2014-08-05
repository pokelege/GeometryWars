#ifndef CHAINABLEASTEROID
#define CHAINABLEASTEROID
#include "Asteroid.h"

class ChainableAsteroid : public Asteroid
{
	Engine::Vector2 chainTranslation;
	float angle;
	Asteroid* parent;  

public:
	explicit ChainableAsteroid();

	explicit ChainableAsteroid(const float& diameter, const Engine::Vector2& initialTranslation);

	explicit ChainableAsteroid(const float& diameter, const Engine::Vector2& initialTranslation, Asteroid* initialParent);

	void updateFromParentPosition();

	void translateFromParentPosition(const Engine::Vector2& translation);

	void rotateFromParentPosition(const float& angle);

	void scaleFromParentPosition(const float& scale);

	void changeParent(Asteroid* newparent);
};

#endif