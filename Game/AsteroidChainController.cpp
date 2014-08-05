#include "AsteroidChainController.h"

AsteroidChainController::AsteroidChainController() {}

void AsteroidChainController::setAsteroid(const unsigned int& index, const ChainableAsteroid& asteroid)
{
	ASSERT((index < ASTEROIDCHAINSIZE), "Out of bounds")
	asteroidChain[index] = asteroid;

	if (index > 0)
	{
		asteroidChain[index].changeParent(&(asteroidChain[index - 1]));
	}
}

void AsteroidChainController::setTranslateAsteroid(const unsigned int& index, const Engine::Vector2& translation)
{
	asteroidChain[index].translateFromParentPosition(translation);
}

void AsteroidChainController::setRotateAsteroid(const unsigned int& index, const float& angle)
{
	asteroidChain[index].rotateFromParentPosition(angle);
}

void AsteroidChainController::setScaleAsteroid(const unsigned int& index, const float& scale)
{
	asteroidChain[index].scaleFromParentPosition(scale);
}

void AsteroidChainController::setFirstParentAsteroid(Asteroid* parent)
{
	asteroidChain[0].changeParent(parent);
}

void AsteroidChainController::update()
{
	for (int i = 0; i < ASTEROIDCHAINSIZE; i++)
	{
		asteroidChain[i].updateFromParentPosition();
	}
}

void AsteroidChainController::draw(Core::Graphics& graphics)
{
	graphics.SetColor(WHITE);
	for (int i = 0; i < ASTEROIDCHAINSIZE; i++)
	{
		asteroidChain[i].Draw(graphics);
	}
}