#include "ChainableAsteroid.h"

ChainableAsteroid::ChainableAsteroid() {}

ChainableAsteroid::ChainableAsteroid(const float& diameter, const Engine::Vector2& initialTranslation)
{
	asteroidDiameter = diameter;
	chainTranslation = initialTranslation;
	angle = 0;
}

ChainableAsteroid::ChainableAsteroid(const float& diameter, const Engine::Vector2& initialTranslation, Asteroid* initialParent)
{
	asteroidDiameter = diameter;
	chainTranslation = initialTranslation;
	parent = initialParent;
	asteroidPosition = Engine::Matrix3::Translation(chainTranslation) * initialParent->getPosition();
	angle = 0;
}

void ChainableAsteroid::updateFromParentPosition()
{
	asteroidPosition = (Engine::Matrix3::rotation(angle) * chainTranslation) + parent->getPosition();
}

void ChainableAsteroid::translateFromParentPosition(const Engine::Vector2& translation)
{
	chainTranslation = Engine::Matrix3::Translation(translation) * chainTranslation;
}

void ChainableAsteroid::rotateFromParentPosition(const float& angle)
{
	this->angle += angle;
}

void ChainableAsteroid::scaleFromParentPosition(const float& scale)
{
	asteroidDiameter += (Engine::Matrix3::scale(scale) * Engine::Vector2(asteroidDiameter, 0)).getX();
}

void ChainableAsteroid::changeParent(Asteroid* newparent)
{
	parent = newparent;
}