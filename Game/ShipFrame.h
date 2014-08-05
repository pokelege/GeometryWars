#ifndef SHIPFRAME
#define SHIPFRAME
#include "Vector2D.h"
#include "graphics.h"
#include "Matrix3D.h"
#include "Bullet.h"
#include "Collision.h"
using namespace Engine;
using namespace Core;

struct ShipFrame
{
	Engine::Vector2 frames[10];

	ShipFrame();

	ShipFrame(const float& size);

	bool isShot(const Matrix3& transformations, Bullet& bullet);

	void draw(Graphics& graphics, const Matrix3& transformations);
};

#endif