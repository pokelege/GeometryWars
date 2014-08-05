#ifndef RANDOMITEMSGENERATOR
#define RANDOMITEMSGENERATOR
#include "ExportHeader.h"
#include <stdlib.h>
#include <ctime>
#include "Logger.h"
#include "Vector2D.h"
#include "graphics.h"

namespace Engine
{
	struct ENGINE_SHARED RandomItemsGenerator
	{
		static const float PI2;

		RandomItemsGenerator();

		float RandomFloat();

		float RandomRangedFloat(const float& min, const float& max);

		Vector2 RandomUnitVector();

		Core::RGB RandomColor();
	};	
}

#endif