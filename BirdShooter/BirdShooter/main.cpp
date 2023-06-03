#ifndef _DEBUG
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include "src/Engine.h"

int main(int argc, char* argv[])
{
	mEngine::Engine* game = mEngine::Engine::GetInstance();
	
	game->Init("test", false);
	game->RunEngine();
	game->Clean();
	return 0;
}


