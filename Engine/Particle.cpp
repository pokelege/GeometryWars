#include "Particle.h"

namespace Engine
{
	Particle::Particle()
	{
		position = Vector2();
		velocity = Vector2();
		color = RGB(255, 255, 255);
		this->lifetime = 0;
	}

	Particle::Particle(const Vector2& initialPosition, const Vector2& initialVelocity,
		const Core::RGB& initialColor, const float& lifetime)
	{
		position = initialPosition;
		velocity = initialVelocity;
		color = initialColor;
		this->lifetime = lifetime;
	}

	void Particle::setPosition(const Vector2& position)
	{
		this->position = position;
	}

	Vector2& Particle::getPosition()
	{
		return position;
	}

	void Particle::setVelocity(const Vector2& velocity)
	{
		this->velocity = velocity;
	}

	Vector2& Particle::getVelocity()
	{
		return velocity;
	}

	void Particle::setColor(const Core::RGB& color)
	{
		this->color = color;
	}

	Core::RGB& Particle::getColor()
	{
		return color;
	}

	void Particle::setLife(const float& life)
	{
		lifetime = life;
	}

	float& Particle::getLife()
	{
		return lifetime;
	}

	bool Particle::decreaseLife(const float& dt)
	{
		lifetime -= dt;
		return(lifetime >= 0);
	}
}
