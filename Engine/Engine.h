#ifndef _ENGINE_H_
#define _ENGINE_H_

#include "ExportHeader.h"

#include "Explosion.h"
#include "MagicAbsorb.h"
#include "ParticleSystem.h"

#include "Keys.h"

namespace Engine
{
	// your stuff goes here...
	// use ENGINE_SHARED to indicate a function or class that you want to export
	ENGINE_SHARED void Init();

	ENGINE_SHARED bool sampleFunctionThatReturnsTrue();
}

#endif // _ENGINE_H_