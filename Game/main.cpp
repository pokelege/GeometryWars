#include "Engine.h"
#include "Game.h"
#include "Logger.h"
using namespace Engine;

int main()
{
#ifdef _DEBUG
	//CHANGE BUILD TYPE FROM DEBUG TO WITH LOGGING TO TURN ON LOGGING 

	//bool troll = false;
	//ASSERT(troll, "wwwwwwwwwww")

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);
	//Memory leak sim
	//int* memleak = new int;
	//delete memleak;

	//Memory corruption sim
	//int* memcorr = new int[1];
	//memcorr[-1] = 1;

#endif
	Core::Init("Geo Wars", Game::RESWIDTH, Game::RESHEIGHT);
	Game game;
	Core::GameLoop();
	Core::Shutdown();
	LOG(Info, "Exited gracefully.")
	END_LOG
}