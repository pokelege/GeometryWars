#include "Explosion.h"

namespace Engine
{
	Explosion::Explosion(const Engine::Vector2& initialPosition = Engine::Vector2(),
		const float& minVelo = 1,
		const float& maxVelo = 2,
		const Core::RGB& color = WHITE,
		const Core::RGB& endColor = BLACK,
		const float& lifeTimeinSecs = 10,
		const float& timeToStartFade = 1,
		const unsigned int& numParticles = 1)
	{
		size = 1;
		startColor = color;
		this->endColor = endColor;
		startFade = timeToStartFade;
		particleList = new Particle*[numParticles];
		numberofParticles = numParticles;
		for (unsigned int i = 0; i < numberofParticles; i++)
		{
			particleList[i] = new Particle(initialPosition, rand.RandomRangedFloat(minVelo, maxVelo) * rand.RandomUnitVector(), color, lifeTimeinSecs);
		}
	}

	Explosion::Explosion(const Engine::Vector2& initialPosition,
		const float& minVelo,
		const float& maxVelo,
		const Core::RGB& color,
		const Core::RGB& endColor,
		const float& lifeTimeinSecs,
		const float& timeToStartFade,
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
		startColor = color;
		this->endColor = endColor;
		startFade = timeToStartFade;
		particleList = new Particle*[numParticles];
		numberofParticles = numParticles;
		for (unsigned int i = 0; i < numberofParticles; i++)
		{
			particleList[i] = new Particle(initialPosition, rand.RandomRangedFloat(minVelo, maxVelo) * rand.RandomUnitVector(), color, lifeTimeinSecs);
		}
	}

	bool Explosion::Update(const float& dt)
	{
		bool isChanged = false;

		for (unsigned int i = 0; i < numberofParticles; i++)
		{
			particleList[i]->setPosition(particleList[i]->getPosition() + (particleList[i]->getVelocity() * dt));

			if (!Fade(*(particleList[i]), dt))
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

	void Explosion::Draw(Core::Graphics& graphics)
	{
		graphics.SetColor(WHITE);
		for (unsigned int i = 0; i < numberofParticles; i++)
		{
			if (Length(particleList[i]->getVelocity()) != 0)
			{

				Engine::Vector2 draws[] =
				{
					particleList[i]->getPosition(),
					particleList[i]->getPosition() + (size * Normalized(particleList[i]->getVelocity()))
				};
				graphics.SetColor(particleList[i]->getColor());
				graphics.DrawLines(1, *draws);
			}
		}
	}

	bool Explosion::Fade(Particle& particle, const float& dt)
	{
		if (particle.decreaseLife(dt))
		{
			if (particle.getLife() < startFade)
			{
				float percent = 1 - (particle.getLife() / startFade);
				particle.setColor(RGB(((GetRValue(endColor) - GetRValue(startColor)) * percent) + GetRValue(startColor),
					((GetGValue(endColor) - GetGValue(startColor)) * percent) + GetGValue(startColor),
					((GetBValue(endColor) - GetBValue(startColor)) * percent) + GetBValue(startColor)));
			}
			return true;
		}
		else
		{
			return false;
		}
	}
}