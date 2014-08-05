#include "Walls.h"

Walls::Walls(const float& RESWIDTH, const float& RESHEIGHT)
{
	srand((unsigned int)time(NULL));
	boundary1 = Boundary(Engine::Vector2(rand.RandomRangedFloat(0, (float)RESWIDTH), rand.RandomRangedFloat(0, (float)RESHEIGHT)), Engine::Vector2(rand.RandomRangedFloat(0, (float)RESWIDTH), rand.RandomRangedFloat(0, (float)RESHEIGHT)));
	boundary2 = Boundary(Engine::Vector2(rand.RandomRangedFloat(0, (float)RESWIDTH), rand.RandomRangedFloat(0, (float)RESHEIGHT)), Engine::Vector2(rand.RandomRangedFloat(0, (float)RESWIDTH), rand.RandomRangedFloat(0, (float)RESHEIGHT)));
	boundary3 = Boundary(Engine::Vector2(rand.RandomRangedFloat(0, (float)RESWIDTH), rand.RandomRangedFloat(0, (float)RESHEIGHT)), Engine::Vector2(rand.RandomRangedFloat(0, (float)RESWIDTH), rand.RandomRangedFloat(0, (float)RESHEIGHT)));
	boundary4 = Boundary(Engine::Vector2(rand.RandomRangedFloat(0, (float)RESWIDTH), rand.RandomRangedFloat(0, (float)RESHEIGHT)), Engine::Vector2(rand.RandomRangedFloat(0, (float)RESWIDTH), rand.RandomRangedFloat(0, (float)RESHEIGHT)));
}

Walls::Walls(const int& RESWIDTH, const int& RESHEIGHT)
{
	srand((unsigned int)time(NULL));
	boundary1 = Boundary(Engine::Vector2(rand.RandomRangedFloat(0, (float)RESWIDTH), rand.RandomRangedFloat(0, (float)RESHEIGHT)), Engine::Vector2(rand.RandomRangedFloat(0, (float)RESWIDTH), rand.RandomRangedFloat(0, (float)RESHEIGHT)));
	boundary2 = Boundary(Engine::Vector2(rand.RandomRangedFloat(0, (float)RESWIDTH), rand.RandomRangedFloat(0, (float)RESHEIGHT)), Engine::Vector2(rand.RandomRangedFloat(0, (float)RESWIDTH), rand.RandomRangedFloat(0, (float)RESHEIGHT)));
	boundary3 = Boundary(Engine::Vector2(rand.RandomRangedFloat(0, (float)RESWIDTH), rand.RandomRangedFloat(0, (float)RESHEIGHT)), Engine::Vector2(rand.RandomRangedFloat(0, (float)RESWIDTH), rand.RandomRangedFloat(0, (float)RESHEIGHT)));
	boundary4 = Boundary(Engine::Vector2(rand.RandomRangedFloat(0, (float)RESWIDTH), rand.RandomRangedFloat(0, (float)RESHEIGHT)), Engine::Vector2(rand.RandomRangedFloat(0, (float)RESWIDTH), rand.RandomRangedFloat(0, (float)RESHEIGHT)));
}

Engine::Vector2 Walls::getCollisionVelocity(const Engine::Vector2& point, const Engine::Vector2& velocity) const
{
	for (int i = Boundary::totalBoundaries - 1; i >= 0; i--)
	{
		if ((&boundary1 + i)->boundaryIsCollidedCCW(point, velocity) || (&boundary1 + i)->boundaryIsCollidedCW(point, velocity))
		{
			return (&boundary1 + i)->boundaryCollisionVelocity(point, velocity);
		}
	}

	return Engine::Vector2();
}

void Walls::DrawAllBounds(Core::Graphics& graphics)
{
	graphics.SetColor(WHITE);
	for (int i = Boundary::totalBoundaries - 1; i >= 0; i--)
	{
		(&boundary1 + i)->DrawBound(graphics);
	}
}