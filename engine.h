
#ifndef RZ_ENGINE_H
#define RZ_ENGINE_H

#include <vector>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

class GameState;

class Engine
{
	public:
		bool isrunning;
		bool ispaused;

		void init();
		void cleanup();

		void changeState(GameState* state);
		void pushState(GameState* state);
		void popState();

		void handleEvents();
		void update();
		void render();
		void exit() { isrunning = false; };

		// starts up sdl, creates window and initializes opengl
		void initSDL();

		// initializes matrices and clear color
		void initGL();

	private:
		std::vector<GameState*> states;

		// the window we'll be rendering to
		SDL_Window* gWindow = NULL;

		// opengl context
		SDL_GLContext gContext;

	protected:
		GLuint mProgramID;
};

#endif

