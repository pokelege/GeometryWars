#include "ParticleSystem.h"

namespace Engine
{
	ParticleSystem::ParticleSystem()
	{
		particleEffectList = new ParticleEffect*[0];
		LOG(Info, "Started particle system.")
	}

	ParticleSystem::~ParticleSystem()
	{
		for (unsigned int i = 0; i < numberofParticleEffects; i++)
		{
			delete particleEffectList[i];
		}

		delete[] particleEffectList;
	}

	void ParticleSystem::AddParticle(ParticleEffect* effect)
	{
		if (numberofParticleEffects < MAXIMUMAMOUNTOFEFFECTS)
		{
			ParticleEffect** newList = new ParticleEffect*[numberofParticleEffects + 1];

			for (unsigned int i = 0; i < numberofParticleEffects; i++)
			{
				newList[i] = particleEffectList[i];
			}

			newList[numberofParticleEffects] = effect;
			numberofParticleEffects++;
			delete[] particleEffectList;
			particleEffectList = newList;
		}
		else
		{
			delete effect;
			LOG(Warning, "Particle system full, deleting particle...");
		}
	}

	void ParticleSystem::Update(const float& dt)
	{
		bool isChanged = false;
		for (unsigned int i = 0; i < numberofParticleEffects; i++)
		{
			if (!particleEffectList[i]->Update(dt))
			{
				delete particleEffectList[i];
				for (unsigned int j = i; j < numberofParticleEffects - 1; j++)
				{
					particleEffectList[j] = particleEffectList[j + 1];
				}
				numberofParticleEffects--;
				isChanged = true;
			}
		}

		if (isChanged)
		{
			ParticleEffect** newList = new ParticleEffect*[numberofParticleEffects];

			for (unsigned int i = 0; i < numberofParticleEffects; i++)
			{
				newList[i] = particleEffectList[i];
			}

			delete[] particleEffectList;
			particleEffectList = newList;
		}
	}

	void ParticleSystem::Draw(Core::Graphics& graphics)
	{
		for (unsigned int i = 0; i < numberofParticleEffects; i++)
		{
			particleEffectList[i]->Draw(graphics);
		}
	}

	void ParticleSystem::Refresh()
	{
		ParticleEffect** newList = new ParticleEffect*[0];

		for (unsigned int i = 0; i < numberofParticleEffects; i++)
		{
			delete particleEffectList[i];
		}
		numberofParticleEffects = 0;
		delete[] particleEffectList;
		particleEffectList = newList;
	}
}