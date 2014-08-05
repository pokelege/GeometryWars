#ifndef ENEMYTURRET
#define ENEMYTURRET
#include "Turret.h"

class EnemyTurret : public Turret
{
public:
	EnemyTurret();
	EnemyTurret(const float& turretSize,
		const float& bulletLength,
		const float& coolDown,
		const float& bulletVelocity,
		const float& accuracy);

	void rotateTurret();
	void update(const float& dt, const Vector2& parentPosition, BulletSystem& system, const bool& didFire);
};
#endif