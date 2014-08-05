#include "RandomItemsGenerator.h"

namespace Engine
{
	const float RandomItemsGenerator::PI2 = 3.1415926f * 2;

	RandomItemsGenerator::RandomItemsGenerator()
	{}

	float RandomItemsGenerator::RandomFloat()
	{
		return (float)rand() / RAND_MAX;
	}

	float RandomItemsGenerator::RandomRangedFloat(const float& min, const float& max)
	{
		if (max < min)
		{
			return (RandomFloat() * (min - max)) + max;
		}
		else
		{
			return (RandomFloat() * (max - min)) + min;
		}
	}

	Vector2 RandomItemsGenerator::RandomUnitVector()
	{
		float angle = PI2 * RandomFloat();
		return Vector2(cosf(angle), sinf(angle));
	}

	Core::RGB RandomItemsGenerator::RandomColor()
	{
		return RGB(RandomRangedFloat(0, 255), RandomRangedFloat(0, 255), RandomRangedFloat(0, 255));
	}
}