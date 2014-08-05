#ifndef THRUSTERPARTICLE
#define THRUSTERPARTICLE
#include "ExportHeader.h"
#include "ParticleEffect.h"
#include "Matrix2D.h"
#include "Colors.h"

namespace Engine
{
	class ENGINE_SHARED ThrusterParticle : public ParticleEffect
	{
		Core::RGB startColor;
		Core::RGB endColor;
		float size;
		float startFade;
		RandomItemsGenerator rand;
	public:
		ThrusterParticle(const Vector2& initialPosition,
			const Vector2& direction,
			const float& minSpeed,
			const float& maxSpeed,
			const Core::RGB& color,
			const Core::RGB& endColor,
			const float& lifeTimeinSecs,
			const float& timeToStartFade,
			const unsigned int& numParticles);

		ThrusterParticle(const Vector2& initialPosition,
			const Vector2& direction,
			const float& minSpeed,
			const float& maxSpeed,
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