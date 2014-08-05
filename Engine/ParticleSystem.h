#ifndef PARTICLESYSTEM
#define PARTICLESYSTEM
#include "ExportHeader.h"
#include "ParticleEffect.h"

namespace Engine
{
#define MAXIMUMAMOUNTOFEFFECTS ((UINT_MAX / sizeof(ParticleEffect)) / 10)

	class ENGINE_SHARED ParticleSystem
	{
		unsigned int numberofParticleEffects;
		ParticleEffect** particleEffectList;
	public:
		ParticleSystem();
		~ParticleSystem();
		void AddParticle(ParticleEffect* effect);
		void Update(const float& dt);
		void Draw(Core::Graphics& graphics);
		void Refresh();
	};
}

#endif