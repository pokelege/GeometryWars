#ifndef ASTEROIDCHAINCONTROLLER
#define ASTEROIDCHAINCONTROLLER
#include "ChainableAsteroid.h"
#include "Colors.h"

#define ASTEROIDCHAINSIZE 5

class AsteroidChainController
{
	ChainableAsteroid asteroidChain[ASTEROIDCHAINSIZE];

public:
	AsteroidChainController();

	void setAsteroid(const unsigned int& index, const ChainableAsteroid& asteroid);

	void setTranslateAsteroid(const unsigned int& index, const Engine::Vector2& translation);

	void setRotateAsteroid(const unsigned int& index, const float& angle);

	void setScaleAsteroid(const unsigned int& index, const float& scale);

	void setFirstParentAsteroid(Asteroid* parent);

	void update();

	void draw(Core::Graphics& graphics);
};


#endif