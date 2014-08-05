#include "ParticleEffect.h"

namespace Engine
{
	ParticleEffect::ParticleEffect() {}

	ParticleEffect::ParticleEffect(const Engine::Vector2& initialPosition,
		const Vector2& initialVelocity,
		const Core::RGB& color,
		const float& lifeTimeinSecs,
		const unsigned int& numParticles)
	{
		particleList = new Particle*[numParticles];
		numberofParticles = numParticles;
		for (unsigned int i = 0; i < numberofParticles; i++)
		{
			particleList[i] = new Particle(initialPosition, initialVelocity, color, lifeTimeinSecs);
		}
	}

	ParticleEffect::~ParticleEffect()
	{
		for (unsigned int i = 0; i < numberofParticles; i++)
		{
			delete particleList[i];
		}

		delete[] particleList;
	}

	bool ParticleEffect::Update(const float& dt)
	{
		bool isChanged = false;

		for (unsigned int i = 0; i < numberofParticles; i++)
		{
			particleList[i]->setPosition(particleList[i]->getPosition() + (particleList[i]->getVelocity() * dt));

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

	void ParticleEffect::Draw(Core::Graphics& graphics)
	{
		graphics.SetColor(WHITE);
		for (unsigned int i = 0; i < numberofParticles; i++)
		{
			Engine::Vector2 draws[] = 
			{
				Engine::Vector2(1, 0) + particleList[i]->getPosition(),
				Engine::Vector2(0, 1) + particleList[i]->getPosition()
			};
			graphics.SetColor(particleList[i]->getColor());
			graphics.DrawLines(1, *draws);
		}
	}
}