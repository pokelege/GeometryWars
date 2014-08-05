#include "PlayerTurret.h"

PlayerTurret::PlayerTurret() {}

PlayerTurret::PlayerTurret(const float& turretSize,
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

void PlayerTurret::rotateTurret()
{
	Vector2 mousetoposition = Vector2((float)Input::GetMouseX(), (float)Input::GetMouseY()) - parentPosition;

	if (LengthSquared(mousetoposition) != 0)
	{
		rotationNormal = Engine::Normalized(mousetoposition);
	}
}

void PlayerTurret::update(const float& dt, const Vector2& parentPosition, BulletSystem& system, const bool& didFire)
{
	this->parentPosition = parentPosition;
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