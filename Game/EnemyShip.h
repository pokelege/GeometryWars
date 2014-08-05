#ifndef ENEMYSHIP
#define ENEMYSHIP
#include "Spaceship.h"
#include "EnemyTurret.h"
#define _USE_MATH_DEFINES
#include <math.h>

class EnemyShip : public Spaceship
{
	EnemyTurret turret;
	RandomItemsGenerator rand;
	Spaceship* target;
public:
	EnemyShip();

	EnemyShip(const float& size,
		const Vector2& initialPosition,
		const float& acceleration,
		const float& life,
		const int& RESWIDTH,
		const int& RESHEIGHT,
		const EnemyTurret& turret,
		Spaceship* target);

	void changeTarget(Spaceship* target);

	void changeVelocity(const float& dt, ParticleSystem& system);

	bool Update(const float& dt, bool& warp, ParticleSystem& Psystem, BulletSystem& Bsystem, Spaceship* target);

	bool Update(const float& dt, bool& warp, ParticleSystem& Psystem, BulletSystem& Bsystem, Spaceship* target, Walls& walls);

	void Draw(Core::Graphics& graphics);
};

#endif