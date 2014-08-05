#include "EnemyTurret.h"

EnemyTurret::EnemyTurret(){}

EnemyTurret::EnemyTurret(const float& turretSize,
	const float& bulletLength,
	const float& coolDown,
	const float& bulletVelocity,
	const float& accuracy)
{
	this->turretSize = turretSize;
	this->bulletLength = bulletLength;
	this->coolDown = coolDown;
	cool = 0;
	this->bulletVelocity = bulletVelocity;
	this->accuracy = (float)(accuracy * (M_PI / 2));
}

void EnemyTurret::rotateTurret()
{
	rotationNormal = rand.RandomUnitVector();
}

void EnemyTurret::update(const float& dt, const Vector2& parentPosition, BulletSystem& system, const bool& didFire)
{
	if (cool > 0)
	{
		cool -= dt;
	}

	rotateTurret();

	if (didFire && cool <= 0)
	{
		fire(dt, system, parentPosition);
	}
}