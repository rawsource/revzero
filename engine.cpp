#include "engine.h"

#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "constants.h"
#include "gamestate.h"
#include "soundmanager.h"

void Engine::init()
{
	isrunning = true;
	ispaused = false;

	// initialize random seed
	srand(time(NULL));

	mProgramID = 0;

	initSDL();
	initGL();
	SoundManager::init();
}

void Engine::initSDL()
{
	// initialize sdl
	SDL_Init( SDL_INIT_VIDEO );

	// use opengl 2.1
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 2 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );

	//SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
	//SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
	//SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

	// create window
	gWindow = SDL_CreateWindow( "Rev.ZER0 v0.1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );

	// create context
	gContext = SDL_GL_CreateContext( gWindow );

	// use vsync
	SDL_GL_SetSwapInterval( 1 );
}

void Engine::initGL()
{

	glewExperimental = GL_TRUE;
	glewInit();

	//GLuint vao;
	//glGenVertexArrays( 1, &vao );
	//glBindVertexArray( vao );

	// --------------------------------------------------------------

	// success flag
	GLint programSuccess = GL_TRUE;

	// generate program
	mProgramID = glCreateProgram();

	// create vertex shader
	GLuint vertexShader = glCreateShader( GL_VERTEX_SHADER );

	// get vertex source
	const GLchar* vertexShaderSource[] =
	{
		"void main() { gl_Position = gl_Vertex; }"
	};

	// set vertex source
	glShaderSource( vertexShader, 1, vertexShaderSource, NULL );

	// compile vertex source
	glCompileShader( vertexShader );

	// check vertex shader for errors
	GLint vShaderCompiled = GL_FALSE;
	glGetShaderiv( vertexShader, GL_COMPILE_STATUS, &vShaderCompiled );
	if( vShaderCompiled != GL_TRUE )
	{
		std::cout << "problem 1" << std::endl;
	}

	// attach vertex shader to program
	glAttachShader( mProgramID, vertexShader );

	// create fragment shader
	GLuint fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );

	// get fragment source
	const GLchar* fragmentShaderSource[] =
	{
		"void main() { gl_FragColor = vec4( 0.5, 0.0, 0.5, 1.0 ); }"
	};

	// set fragment source
	glShaderSource( fragmentShader, 1, fragmentShaderSource, NULL );

	// compile fragment source
	glCompileShader( fragmentShader );

	// check fragment shader for errors
	GLint fShaderCompiled = GL_FALSE;
	glGetShaderiv( fragmentShader, GL_COMPILE_STATUS, &fShaderCompiled );
	if( fShaderCompiled != GL_TRUE )
	{
		std::cout << "problem 2" << std::endl;
	}

	// attach fragment shader to program
	glAttachShader( mProgramID, fragmentShader );

	// link program
	glLinkProgram( mProgramID );

	// check for errors
	glGetProgramiv( mProgramID, GL_LINK_STATUS, &programSuccess );
	if( programSuccess != GL_TRUE )
	{
		std::cout << "problem 3" << std::endl;
	}

	// --------------------------------------------------------------

	// initialize projection matrix
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho( 0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, 100.0, -100.0 );

	// initialize modelview matrix
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	// enable blending
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA ) ;
	glEnable( GL_BLEND );

	glEnable(GL_DEPTH_TEST);

	// initialize clear color
	glClearColor( 0.f, 0.f, 0.f, 1.f );
}

void Engine::cleanup()
{
	SoundManager::deinit();

	// cleanup the all states
	while ( !states.empty() )
	{
		states.back()->cleanup();
		states.pop_back();
	}

	// destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	// quit sdl subsystems
	SDL_Quit();
}

void Engine::changeState(GameState* state)
{
	// cleanup the current state
	if ( !states.empty() )
	{
		states.back()->cleanup();
		states.pop_back();
	}

	// store and init the new state
	states.push_back(state);
	states.back()->init();
}

void Engine::pushState(GameState* state)
{
	// pause current state
	if ( !states.empty() )
	{
		states.back()->pause();
	}

	// store and init the new state
	states.push_back(state);
	states.back()->init();
}

void Engine::popState()
{
	// cleanup the current state
	if ( !states.empty() )
	{
		states.back()->cleanup();
		states.pop_back();
	}

	// resume previous state
	if ( !states.empty() ) {
		states.back()->resume();
	}
}

void Engine::handleEvents()
{
	// let the state handle events
	states.back()->handleEvents();
}

void Engine::update()
{
	if (ispaused) return;

	// let the state update the game
	states.back()->update();
}

void Engine::render()
{
	if (ispaused) return;

	// clear color buffer
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// bind program
	//glUseProgram( mProgramID );

	// reset modelview matrix
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	// set polygon mode
	glPolygonMode( GL_FRONT, GL_FILL );

	// enable vertex arrays
	glEnableClientState( GL_VERTEX_ARRAY );
	glEnableClientState( GL_COLOR_ARRAY );

	// let the state draw the screen
	states.back()->render();

	// disable vertex arrays
	glDisableClientState( GL_VERTEX_ARRAY );
	glDisableClientState( GL_COLOR_ARRAY );

	// update screen
	SDL_GL_SwapWindow( gWindow );

	//glUseProgram( 0 );
}

