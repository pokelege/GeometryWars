#include "ShipFrame.h"

ShipFrame::ShipFrame(){}

ShipFrame::ShipFrame(const float& size)
{
	frames[0] = size * Engine::Vector2(0, -1);
	frames[1] = size * Engine::Vector2(1, -1 / 2);
			    
	frames[2] = size * Engine::Vector2(1, -1 / 2);
	frames[3] = size * Engine::Vector2(1, 1);
	
	frames[4] = size * Engine::Vector2(1, 1);
	frames[5] = size * Engine::Vector2(-1, 1);
			
	frames[6] = size * Engine::Vector2(-1, 1);
	frames[7] = size * Engine::Vector2(-1, -1 / 2);
			  
	frames[8] = size * Engine::Vector2(-1, -1 / 2);
	frames[9] = size * Engine::Vector2(0, -1);
}

bool ShipFrame::isShot(const Matrix3& transformations, Bullet& bullet)
{
	for (int i = 0; i < sizeof(frames) / (sizeof(*frames)); i+=2)
	{
		if (isCollidedCW(bullet.getPosition(), bullet.getVelocity(), transformations * frames[i], transformations * frames[i + 1]))
		{
			return true;
		}
	}
	return false;
}

void ShipFrame::draw(Graphics& graphics, const Matrix3& transformations)
{

	for (int i = 0; i < sizeof(frames) / (sizeof(*frames)); i += 2)
	{
		Engine::Vector2 a[] = 
		{
			transformations * frames[i],
			transformations * frames[i + 1]
		};
		graphics.DrawLines(1, *a);
	}
}