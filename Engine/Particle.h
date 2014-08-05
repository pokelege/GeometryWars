#ifndef PARTICLE
#define PARTICLE
#include "ExportHeader.h"
#include "graphics.h"
#include "Vector2D.h"

namespace Engine
{
	using namespace Core;

	class ENGINE_SHARED Particle
	{
	protected:
		Vector2 position;
		Vector2 velocity;
		RGB color;
		float lifetime;
	public:
		explicit Particle();
		explicit Particle(const Vector2& initialPosition, const Vector2& initialVelocity,
			const Core::RGB& initialColor, const float& lifetime);

		void setPosition(const Vector2& position);
		Vector2& getPosition();

		void setVelocity(const Vector2& velocity);
		Vector2& getVelocity();

		void setColor(const Core::RGB& color);
		RGB& getColor();

		void setLife(const float& life);
		float& getLife();

		bool decreaseLife(const float& dt);
	};
}
#endif