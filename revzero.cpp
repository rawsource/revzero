
/*
	- ttf font rendering
	- steering behavior state machine
	- input manager
*/

#include "globals.h"
#include "titlestate.h"

Engine* game = new Engine();
ResourceManager* rm = ResourceManager::getInstance();

int main( int argc, char* args[] )
{
	// initialize the engine
	game->init();

	// load the intro
	game->changeState( TitleState::instance() );

	// main loop
	while ( game->isrunning )
	{
		if ( game->ispaused  )
		{
			SDL_Delay(15);
		}
		game->handleEvents();
		game->update();
		game->render();
	}

	// free resources and close sdl
	game->cleanup();

	delete game;
	game = nullptr;

	ResourceManager::deleteInstance();
	rm = nullptr;

	return 0;
}
