#ifndef SPACESHIP
#define SPACESHIP
#include "Core.h"
#include "Vector2D.h"
#include "Matrix2D.h"
#include "Matrix3D.h"
#include "ParticleSystem.h"
#include "Explosion.h"
#include "MagicAbsorb.h"
#include "ThrusterParticle.h"
#include "RandomItemsGenerator.h"
#include "Walls.h"
#include "BulletSystem.h"
#include "Turret.h"
#include "ShipFrame.h"


using namespace Engine;
using namespace Core;

#define WARPPARTICLE Engine::MagicAbsorb(shipPosition, -50, 50, 1, 100, 5)
//to fix
#define EXPLODEPARTICLE Engine::Explosion(shipPosition, 0, 100, SAFETY_ORANGE, RED, 2, 1 , 300, 5)
#define COLLISIONPARTICLE Engine::Explosion(shipPosition, 0, (Engine::LengthSquared(velocity)) + 1 / 2, SAFETY_ORANGE, RED, 2, 1 , 300, 5)
#define THRUSTPARTICLEUP Engine::ThrusterParticle(shipPosition, Normalized(Engine::Matrix2::rotation(shipRotation) * Engine::Vector2(0, (acceleration * dt))), 1, 100, YELLOW, RED, 0.5, 0.25, 10)
#define THRUSTPARTICLEDOWN Engine::ThrusterParticle(shipPosition, Normalized(Engine::Matrix2::rotation(shipRotation) * Engine::Vector2(0, -(acceleration * dt))), 1, 100, YELLOW, RED, 0.5, 0.25, 10)

class Spaceship
{
protected:
	ShipFrame frame;

	Engine::Vector2 shipPosition;

	Engine::Vector2 velocity;
	Engine::Vector2 resetPosition;

	float shipRotation;

	float acceleration;

	float life, originalLife;

	int RESWIDTH;

	int RESHEIGHT;

	bool isPlayer;

public:

	Spaceship();
	
	Spaceship(const float& size,
		const Vector2& initialPosition,
		const float& acceleration,
		const float& life,
		const int& RESWIDTH,
		const int& RESHEIGHT);

	Vector2& getPosition();

	bool& isaPlayer();

	bool isShot(Bullet& bullet, ParticleSystem& particle);

	void outofBoundsCheck(ParticleSystem& system, bool& warp);

	virtual void changeVelocity(const float& dt, ParticleSystem& system) = 0;

	virtual bool Update(const float& dt, bool& warp, ParticleSystem& Psystem, BulletSystem& Bsystem, Spaceship* target) = 0;

	virtual bool Update(const float& dt, bool& warp, ParticleSystem& Psystem, BulletSystem& Bsystem, Spaceship* target, Walls& walls) = 0;

	virtual void Draw(Core::Graphics& graphics) = 0;
};
#endif