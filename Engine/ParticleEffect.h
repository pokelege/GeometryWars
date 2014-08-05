#ifndef PARTICLEEFFECT
#define PARTICLEEFFECT
#include "ExportHeader.h"
#include "DebugMemory.h"
#include "Colors.h"
#include "Particle.h"
#include "Vector2D.h"
#include "graphics.h"
#include "RandomItemsGenerator.h"

namespace Engine
{
	class ENGINE_SHARED ParticleEffect
	{
	protected:
		unsigned int numberofParticles;
		Particle** particleList;
	public:
		ParticleEffect();
		ParticleEffect(const Vector2& initialPosition,
			const Vector2& initialVelocity,
			const Core::RGB& color,
			const float& lifeTimeinSecs,
			const unsigned int& numParticles);
		~ParticleEffect();

		virtual bool Update(const float& dt);

		virtual void Draw(Core::Graphics& graphics);
	};
}
#endif