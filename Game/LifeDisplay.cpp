#include "LifeDisplay.h"

void drawLife(Core::Graphics& graphics, unsigned int& life, float x, float y)
{
	for (unsigned int i = 0; i < life; i++)
	{
		graphics.SetColor(BLOODRED);
		Vector2 lifedraw[12] =
		{
			Matrix3::Translation(x, y) * Vector2(0, 0),
			Matrix3::Translation(x, y) * Vector2(-10, -10),

			Matrix3::Translation(x, y) * Vector2(-10, -10),
			Matrix3::Translation(x, y) * Vector2(-10, 10),

			Matrix3::Translation(x, y) * Vector2(-10, 10),
			Matrix3::Translation(x, y) * Vector2(0, 15),

			Matrix3::Translation(x, y) * Vector2(0, 15),
			Matrix3::Translation(x, y) * Vector2(10, 10),

			Matrix3::Translation(x, y) * Vector2(10, 10),
			Matrix3::Translation(x, y) * Vector2(10, -10),

			Matrix3::Translation(x, y) * Vector2(10, -10),
			Matrix3::Translation(x, y) * Vector2(0, 0)
		};

		int size = sizeof(lifedraw) / (sizeof(Vector2)* 2);

		graphics.DrawLines(size, *lifedraw);
		x += 30;
	}
}