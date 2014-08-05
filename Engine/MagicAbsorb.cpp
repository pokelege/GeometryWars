#include "MagicAbsorb.h"

namespace Engine
{
	MagicAbsorb::MagicAbsorb(const Engine::Vector2& initialPosition = Engine::Vector2(),
		const float& minDistance = 0,
		const float& maxDistance = 0,
		const float& lifeTimeinSecs = 10,
		const unsigned int& numParticles = 1)
	{
		size = 1;
		position = initialPosition;
		particleList = new Particle*[numParticles];
		numberofParticles = numParticles;
		for (unsigned int i = 0; i < numberofParticles; i++)
		{
			Vector2 particlePosition = initialPosition + Vector2(rand.RandomRangedFloat(minDistance, maxDistance), rand.RandomRangedFloat(minDistance, maxDistance));
			particleList[i] = new Particle(particlePosition,
				rand.RandomFloat() * (position - particlePosition),
				rand.RandomColor(),
				lifeTimeinSecs);
		}
	}

	MagicAbsorb::MagicAbsorb(const Engine::Vector2& initialPosition,
		const float& minDistance,
		const float& maxDistance,
		const float& lifeTimeinSecs,
		const unsigned int& numParticles,
		const float& size)
	{
		if (size <= 0)
		{
			this->size = 1;
		}
		else
		{
			this->size = size;
		}
		position = initialPosition;
		particleList = new Particle*[numParticles];
		numberofParticles = numParticles;
		for (unsigned int i = 0; i < numberofParticles; i++)
		{
			Vector2 particlePosition = initialPosition + Vector2(rand.RandomRangedFloat(minDistance, maxDistance), rand.RandomRangedFloat(minDistance, maxDistance));
			particleList[i] = new Particle(particlePosition,
				rand.RandomFloat() * (position - particlePosition),
				rand.RandomColor(),
				lifeTimeinSecs);
		}
	}

	bool MagicAbsorb::Update(const float& dt)
	{
		bool isChanged = false;

		for (unsigned int i = 0; i < numberofParticles; i++)
		{
			if (isCollidedPoint(particleList[i]->getPosition(), (particleList[i]->getVelocity() * dt), position))
			{
				particleList[i]->setLife(0);
			}
			else
			{
				particleList[i]->setPosition(particleList[i]->getPosition() + (particleList[i]->getVelocity() * dt));
				particleList[i]->setColor(rand.RandomColor());
			}
			if (!particleList[i]->decreaseLife(dt))
			{
				delete particleList[i];
				for (unsigned int j = i; j < numberofParticles - 1; j++)
				{
					particleList[j] = particleList[j + 1];
				}
				numberofParticles--;
				isChanged = true;
			}
		}

		if (isChanged)
		{
			Particle** newList = new Particle*[numberofParticles];

			for (unsigned int i = 0; i < numberofParticles; i++)
			{
				newList[i] = particleList[i];
			}

			delete[] particleList;
			particleList = newList;
		}

		return (numberofParticles > 0);
	}

	void MagicAbsorb::Draw(Core::Graphics& graphics)
	{
		graphics.SetColor(WHITE);
		for (unsigned int i = 0; i < numberofParticles; i++)
		{
			Engine::Vector2 vect = size * rand.RandomUnitVector();
			Engine::Vector2 draws[] =
			{
				particleList[i]->getPosition(),
				particleList[i]->getPosition() + vect,

				particleList[i]->getPosition(),
				particleList[i]->getPosition() - vect
			};
			graphics.SetColor(particleList[i]->getColor());
			graphics.DrawLines(2, *draws);
		}
	}
}