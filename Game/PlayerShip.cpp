#include "PlayerShip.h"

PlayerShip::PlayerShip(){}

PlayerShip::PlayerShip(const float& size,
	const Engine::Vector2& initialPosition,
	const float& acceleration,
	const float& turnRate,
	const float& life,
	const int& RESWIDTH,
	const int& RESHEIGHT,
	const PlayerTurret& turret,
	const int keyConfig[5])
{
	frame = ShipFrame(size);
	this->life = life;
	this->resetPosition = initialPosition;
	this->shipPosition = initialPosition;
	this->acceleration = acceleration;
	this->turnRate = turnRate;
	shipRotation = 0;
	this->RESWIDTH = RESWIDTH;
	this->RESHEIGHT = RESHEIGHT;
	this->turret = turret;
	originalLife = life;
	isPlayer = true;

	keyUp = keyConfig[0];
	keyDown = keyConfig[1];
	keyLeft = keyConfig[2];
	keyRight = keyConfig[3];
	keyShoot = keyConfig[4];
}

void PlayerShip::changeVelocity(const float& dt, Engine::ParticleSystem& system)
{
	if (Input::IsPressed(keyUp))
	{
		velocity = velocity + (Engine::Matrix2::rotation(shipRotation) * Engine::Vector2(0, -(acceleration * dt) * dt));
		system.AddParticle(new THRUSTPARTICLEUP);
	}
	if (Input::IsPressed(keyDown))
	{
		velocity = velocity + (Engine::Matrix2::rotation(shipRotation) * Engine::Vector2(0, (acceleration * dt) * dt));
		system.AddParticle(new THRUSTPARTICLEDOWN);
	}

	if (Input::IsPressed(keyLeft))
	{
		shipRotation -= turnRate * dt;
	}

	if (Input::IsPressed(keyRight))
	{
		shipRotation += turnRate * dt;
	}
}

bool PlayerShip::Update(const float& dt, bool& warp, ParticleSystem& Psystem, BulletSystem& Bsystem, Spaceship* target)
{
	//hack to bypass, will fix soon
	target;

	turret.update(dt, shipPosition, Bsystem, Input::IsPressed(keyShoot));
	outofBoundsCheck(Psystem, warp);
	changeVelocity(dt, Psystem);
	shipPosition = shipPosition + velocity;
	return (life > 0);
}

bool PlayerShip::Update(const float& dt, bool& warp, ParticleSystem& Psystem, BulletSystem& Bsystem, Spaceship* target, Walls& walls)
{
	//hack to bypass, will fix soon
	target;

	turret.update(dt, shipPosition, Bsystem, Input::IsPressed(keyShoot));
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

void PlayerShip::Draw(Core::Graphics& graphics)
{
	RGB from = BESTCYAN;
	RGB to = BLOODRED;
	float percent = 1 - (life / originalLife);
	graphics.SetColor(RGB(((GetRValue(to) - GetRValue(from)) * percent) + GetRValue(from),
		((GetGValue(to) - GetGValue(from)) * percent) + GetGValue(from),
		((GetBValue(to) - GetBValue(from)) * percent) + GetBValue(from)));

	//graphics.SetColor(BESTCYAN);

	Engine::Matrix3 transformations = Engine::Matrix3::Translation(shipPosition) * Engine::Matrix3::rotation(shipRotation);

	frame.draw(graphics, transformations);

	turret.draw(graphics, shipPosition);
}