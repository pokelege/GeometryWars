#ifndef EXPLOSION
#define EXPLOSION
#include "ExportHeader.h"
#include "ParticleEffect.h"
#include "Colors.h"
namespace Engine
{
	class ENGINE_SHARED Explosion : public ParticleEffect
	{
		Core::RGB startColor;
		Core::RGB endColor;
		float size;
		float startFade;
		RandomItemsGenerator rand;
	public:
		Explosion(const Engine::Vector2& initialPosition,
			const float& minVelo,
			const float& maxVelo,
			const Core::RGB& color,
			const Core::RGB& endColor,
			const float& lifeTimeinSecs,
			const float& timeToStartFade,
			const unsigned int& numParticles);

		Explosion(const Engine::Vector2& initialPosition,
			const float& minVelo,
			const float& maxVelo,
			const Core::RGB& color,
			const Core::RGB& endColor,
			const float& lifeTimeinSecs,
			const float& timeToStartFade,
			const unsigned int& numParticles,
			const float& size);

		bool Update(const float& dt);

		void Draw(Core::Graphics& graphics);

		bool Fade(Particle& particle, const float& dt);
	};
}
#endif