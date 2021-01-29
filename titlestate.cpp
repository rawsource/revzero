#include "titlestate.h"

#include <SDL2/SDL.h>

#include "globals.h"
#include "constants.h"
#include "playstate.h"

TitleState TitleState::m_TitleState;

void TitleState::init()
{
}

void TitleState::cleanup()
{
}

void TitleState::pause()
{
}

void TitleState::resume()
{
}

void TitleState::handleEvents()
{
	SDL_Event event;

	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				game->exit();
				break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						game->exit();
						break;
					case SDLK_RETURN:
						game->changeState(PlayState::instance());
						break;
				}
				break;
		}
	}
}

void TitleState::update()
{
}

void TitleState::render()
{
	rm->data["title"].render(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0, 1);
}

