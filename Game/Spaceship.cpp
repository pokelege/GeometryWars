#include "Spaceship.h"
#include "Keys.h"

Spaceship::Spaceship(){}

Spaceship::Spaceship(const float& size,
	const Engine::Vector2& initialPosition,
	const float& acceleration,
	const float& life,
	const int& RESWIDTH,
	const int& RESHEIGHT) :
	resetPosition(initialPosition),
	shipPosition(initialPosition),
	acceleration(acceleration),
	life(life),
	shipRotation(0),
	RESWIDTH(RESWIDTH),
	RESHEIGHT(RESHEIGHT)
{
	frame = ShipFrame(size);
	originalLife = life;
}

Vector2& Spaceship::getPosition()
{
	return shipPosition;
}

void Spaceship::outofBoundsCheck(ParticleSystem& system, bool& warp)
{
	if (warp)
	{
		if (shipPosition.getX() > RESWIDTH)
		{
			system.AddParticle(new WARPPARTICLE);
			shipPosition = shipPosition - Vector2(float(RESWIDTH), 0);
			system.AddParticle(new WARPPARTICLE);
		}

		if (shipPosition.getX() < 0)
		{
			system.AddParticle(new WARPPARTICLE);
			shipPosition = shipPosition + Vector2(float(RESWIDTH), 0);
			system.AddParticle(new WARPPARTICLE);
		}

		if (shipPosition.getY() > RESHEIGHT)
		{
			system.AddParticle(new WARPPARTICLE);
			shipPosition = shipPosition - Vector2(0, float(RESHEIGHT));
			system.AddParticle(new WARPPARTICLE);
		}

		if (shipPosition.getY() < 0)
		{
			system.AddParticle(new WARPPARTICLE);
			shipPosition = shipPosition + Vector2(0, float(RESHEIGHT));
			system.AddParticle(new WARPPARTICLE);
		}
	}

	else
	{
		if (shipPosition.getX() > RESWIDTH)
		{
			if (velocity.getX() > 0)
			{
				system.AddParticle(new COLLISIONPARTICLE);
				velocity = Vector2(velocity.getX() * -1, velocity.getY());
			}
		}
		if (shipPosition.getX() < 0)
		{
			if (velocity.getX() < 0)
			{
				system.AddParticle(new COLLISIONPARTICLE);
				velocity = Vector2(velocity.getX() * -1, velocity.getY());
			}
		}
		if (shipPosition.getY() > RESHEIGHT)
		{
			if (velocity.getY() > 0)
			{
				system.AddParticle(new COLLISIONPARTICLE);
				velocity = Vector2(velocity.getX(), velocity.getY() * -1);
			}
		}
		if (shipPosition.getY() < 0)
		{
			if (velocity.getY() < 0)
			{
				system.AddParticle(new COLLISIONPARTICLE);
				velocity = Vector2(velocity.getX(), velocity.getY() * -1);
			}
		}
	}
}

bool Spaceship::isShot(Bullet& bullet, ParticleSystem& system)
{
	if (frame.isShot(Matrix3::Translation(shipPosition) * Matrix3::rotation(shipRotation), bullet))
	{
		life -= 0.1f;
		if (!(life > 0))
		{
			system.AddParticle(new EXPLODEPARTICLE);
		}
		return true;
	}
	return false;
}

bool& Spaceship::isaPlayer()
{
	return isPlayer;
}