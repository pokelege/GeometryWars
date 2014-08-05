#include "EnemyShip.h"

EnemyShip::EnemyShip(){}

EnemyShip::EnemyShip(const float& size,
	const Engine::Vector2& initialPosition,
	const float& acceleration,
	//const float& turnRate,
	const float& life,
	const int& RESWIDTH,
	const int& RESHEIGHT,
	const EnemyTurret& turret,
	Spaceship* target)
{
	frame = ShipFrame(size);
	this->life = life;
	this->resetPosition = initialPosition;
	this->shipPosition = initialPosition;
	this->acceleration = acceleration;
	shipRotation = 0;
	this->RESWIDTH = RESWIDTH;
	this->RESHEIGHT = RESHEIGHT;
	this->turret = turret;
	this->target = target;
	originalLife = life;

	isPlayer = false;
}

void EnemyShip::changeTarget(Spaceship* target)
{
	this->target = target;
}

void EnemyShip::changeVelocity(const float& dt, Engine::ParticleSystem& system)
{
	if (target != nullptr)
	{
		Vector2 toTarget = target->getPosition() - shipPosition;
		
		if (LengthSquared(toTarget) != 0)
		{
			Vector2 normalizedtoTarget = PerpCCW(Normalized(toTarget));

			shipRotation = atan2f(normalizedtoTarget.getY(), normalizedtoTarget.getX());

			if (LengthSquared(toTarget) >= 0)
			{
				velocity = velocity + (Engine::Matrix2::rotation(shipRotation) * Engine::Vector2(0, -(acceleration * dt) * dt));
				system.AddParticle(new THRUSTPARTICLEUP);
			}
			else
			{
				velocity = velocity + (Engine::Matrix2::rotation(shipRotation) * Engine::Vector2(0, (acceleration * dt) * dt));
				system.AddParticle(new THRUSTPARTICLEDOWN);
			}
		}
	}
}

bool EnemyShip::Update(const float& dt, bool& warp, ParticleSystem& Psystem, BulletSystem& Bsystem, Spaceship* target)
{
	changeTarget(target);
	turret.update(dt, shipPosition, Bsystem, (rand.RandomFloat() > 0.8));
	outofBoundsCheck(Psystem, warp);
	changeVelocity(dt, Psystem);
	shipPosition = shipPosition + velocity;
	return (life > 0);
}

bool EnemyShip::Update(const float& dt, bool& warp, ParticleSystem& Psystem, BulletSystem& Bsystem, Spaceship* target, Walls& walls)
{
	changeTarget(target);
	turret.update(dt, shipPosition, Bsystem, (rand.RandomFloat() < 0.1));
	outofBoundsCheck(Psystem, warp);
	changeVelocity(dt, Psystem);

	Vector2 collision = walls.getCollisionVelocity(shipPosition, velocity);

	if (Engine::LengthSquared(collision) != 0)
	{
		Psystem.AddParticle(new COLLISIONPARTICLE);
	}

	velocity = velocity + collision;
	shipPosition = shipPosition + velocity;
	return (life > 0);
}

void EnemyShip::Draw(Core::Graphics& graphics)
{
	RGB from = ALIEN;
	RGB to = BLACK;
	float percent = 1 - (life / originalLife);
	graphics.SetColor(RGB(((GetRValue(to) - GetRValue(from)) * percent) + GetRValue(from),
		((GetGValue(to) - GetGValue(from)) * percent) + GetGValue(from),
		((GetBValue(to) - GetBValue(from)) * percent) + GetBValue(from)));

	//graphics.SetColor(ALIEN);

	Engine::Matrix3 transformations = Engine::Matrix3::Translation(shipPosition) * Engine::Matrix3::rotation(shipRotation);

	frame.draw(graphics, transformations);

	turret.draw(graphics, shipPosition);
}