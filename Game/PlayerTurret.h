#ifndef PLAYERTURRET
#define PLAYERTURRET
#include "Turret.h"

class PlayerTurret : public Turret
{
	Vector2 parentPosition;
public:
	PlayerTurret();
	PlayerTurret(const float& turretSize,
	const float& bulletLength,
	const float& coolDown,
	const float& bulletVelocity,
	const float& accuracy);

	void rotateTurret();
	void update(const float& dt, const Vector2& parentPosition, BulletSystem& Bsystem, const bool& didFire);
};

#endif