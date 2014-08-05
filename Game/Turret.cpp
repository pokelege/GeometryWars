#include "Turret.h"

Turret::Turret(){}

Turret::Turret(const float& turretSize,
	const float& bulletLength,
	const float& coolDown,
	const float& bulletVelocity,
	const float& accuracy) :
	turretSize(turretSize),
	bulletLength(bulletLength),
	coolDown(coolDown),
	cool(0),
	bulletVelocity(bulletVelocity)
{
	this->accuracy = (float)(accuracy * (M_PI / 2));
}

void Turret::fire(const float& dt, BulletSystem& Bsystem, const Vector2& parentPosition)
{

	Bsystem.addBullet(
		new Bullet(parentPosition,
		Matrix2::rotation(rand.RandomRangedFloat(-accuracy, accuracy)) * (rotationNormal * (bulletVelocity * dt)),
		BULLETCOLOR,
		0.5,
		3));
	cool = coolDown;
}

void Turret::draw(Graphics& graphics, const Vector2& parentPosition)
{
	graphics.SetColor(WHITE);

	Engine::Matrix3 turretRotation(rotationNormal, Engine::PerpCW(rotationNormal), parentPosition);

	Engine::Vector2 drawTurretArray[] =
	{
		turretRotation * (Engine::Vector2(0, -turretSize)),
		turretRotation * (Engine::Vector2(0, turretSize)),

		turretRotation * (Engine::Vector2(0, turretSize)),
		turretRotation * (Engine::Vector2(turretSize, 0)),

		turretRotation * (Engine::Vector2(turretSize, 0)),
		turretRotation * (Engine::Vector2(0, -turretSize))
	};

	unsigned int drawTurretArraySize = sizeof(drawTurretArray) / (sizeof(*drawTurretArray) * 2);

	graphics.SetColor(RED);
	graphics.DrawLines(drawTurretArraySize, *drawTurretArray);
}