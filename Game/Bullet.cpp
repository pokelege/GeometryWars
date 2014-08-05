#include "Bullet.h"

Bullet::Bullet(){}

Bullet::Bullet(const Vector2& initialPosition, const Vector2& initialVelocity,
	const RGB& initialColor, const float& lifetime, const float& size)
{
	position = initialPosition;
	velocity = initialVelocity;
	color = initialColor;
	this->size = size;
	if (LengthSquared(velocity) == 0)
	{
		this->lifetime = 0;
	}
	else
	{
		this->lifetime = lifetime;
	}
}

bool Bullet::update(const float& dt)
{
	position = position + velocity;
	lifetime -= dt;
	return (lifetime > 0);
}

void Bullet::draw(Graphics& graphics)
{
	graphics.SetColor(WHITE);
	Vector2 bulletDraw[] =
	{
		position + (size * Normalized(velocity)),
		position - (size * Normalized(velocity))
	};

	int arraysize = sizeof(bulletDraw) / (sizeof(*bulletDraw) * 2);

	graphics.SetColor(color);
	graphics.DrawLines(arraysize, *bulletDraw);
}

