#ifndef BULLET
#define BULLET
#include "Vector2D.h"
#include "graphics.h"
#include "Particle.h"
#include "Colors.h"
using namespace Engine;
using namespace Core;

class Bullet : public Particle
{
	float size;
public:
	explicit Bullet();
	explicit Bullet(const Vector2& initialPosition, const Vector2& initialVelocity,
		const RGB& initialColor, const float& lifetime, const float& size);

	bool update(const float& dt);

	void draw(Graphics& graphics);
};

#endif