#ifndef MAGICABSORB
#define MAGICABSORB
#include "ExportHeader.h"
#include "ParticleEffect.h"
#include "Collision.h"
#include "Colors.h"

namespace Engine
{
	class ENGINE_SHARED MagicAbsorb : public ParticleEffect
	{
		Vector2 position;
		float size;
		RandomItemsGenerator rand;
	public:
		MagicAbsorb (const Vector2& initialPosition,
			const float& minDistance,
			const float& maxDistance,
			const float& lifeTimeinSecs,
			const unsigned int& numParticles);

		MagicAbsorb(const Vector2& initialPosition,
			const float& minDistance,
			const float& maxDistance,
			const float& lifeTimeinSecs,
			const unsigned int& numParticles,
			const float& size);

		bool Update(const float& dt);

		void Draw(Core::Graphics& graphics);
	};
}

#endif