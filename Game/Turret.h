#ifndef TURRET
#define TURRET
#include "graphics.h"
#include "BulletSystem.h"
#include "Matrix3D.h"
#include "Matrix2D.h"
#define _USE_MATH_DEFINES
#include <math.h>

using namespace Engine;
using namespace Core;

class Turret
{
protected:
	Vector2 rotationNormal;
	float turretSize, bulletLength, coolDown, cool, bulletVelocity, accuracy;
	RandomItemsGenerator rand;
public:
	Turret();

	Turret(const float& turretSize,
		const float& bulletLength,
		const float& coolDown,
		const float& bulletVelocity,
		const float& accuracy);

	virtual void rotateTurret() = 0;

	void fire(const float& dt, BulletSystem& Bsystem, const Vector2& parentPosition);

	virtual void update(const float& dt, const Vector2& parentPosition, BulletSystem& Bsystem, const bool& didFire) = 0;

	void draw(Graphics& graphics, const Vector2& parentPosition);
};

#endif