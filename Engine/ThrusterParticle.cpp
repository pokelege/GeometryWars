#include "ThrusterParticle.h"

namespace Engine
{
	ThrusterParticle::ThrusterParticle(const Vector2& initialPosition,
		const Vector2& direction,
		const float& minSpeed,
		const float& maxSpeed,
		const Core::RGB& color,
		const Core::RGB& endColor,
		const float& lifeTimeinSecs,
		const float& timeToStartFade,
		const unsigned int& numParticles)
	{
		size = 1;
		startColor = color;
		this->endColor = endColor;
		startFade = timeToStartFade;
		particleList = new Particle*[numParticles];
		numberofParticles = numParticles;
		for (unsigned int i = 0; i < numberofParticles; i++)
		{
			particleList[i] = new Particle(initialPosition, Engine::Matrix2::rotation(rand.RandomRangedFloat(-3.14f /2 , 3.14f / 2)) * (rand.RandomRangedFloat(minSpeed, maxSpeed) * direction), color, lifeTimeinSecs);
		}
	}

	ThrusterParticle::ThrusterParticle(const Vector2& initialPosition,
		const Vector2& direction,
		const float& minSpeed,
		const float& maxSpeed,
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
			particleList[i] = new Particle(initialPosition, Engine::Matrix2::rotation(rand.RandomRangedFloat(-3.14f /2 , 3.14f/2)) * (rand.RandomRangedFloat(minSpeed, maxSpeed) * direction), color, lifeTimeinSecs);
		}
	}

	bool ThrusterParticle::Update(const float& dt)
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

	void ThrusterParticle::Draw(Core::Graphics& graphics)
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

	bool ThrusterParticle::Fade(Particle& particle, const float& dt)
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