#ifndef PLAYERSHIP
#define PLAYERSHIP
#include "Spaceship.h"
#include "PlayerTurret.h"
using namespace Engine;
using namespace Core;

class PlayerShip : public Spaceship
{
	PlayerTurret turret;
	//button configs
	int keyUp, keyDown, keyLeft, keyRight, keyShoot;
	float turnRate;
public:
	PlayerShip();
	PlayerShip(const float& size,
		const Vector2& initialPosition,
		const float& acceleration,
		const float& turnRate,
		const float& life,
		const int& RESWIDTH,
		const int& RESHEIGHT,
		const PlayerTurret& turret,
		const int keyConfig[5]);

	void changeVelocity(const float& dt, ParticleSystem& system);

	bool Update(const float& dt, bool& warp, ParticleSystem& Psystem, BulletSystem& Bsystem, Spaceship* target);

	bool Update(const float& dt, bool& warp, ParticleSystem& Psystem, BulletSystem& Bsystem, Spaceship* target, Walls& walls);

	void Draw(Graphics& graphics);
};

#endif