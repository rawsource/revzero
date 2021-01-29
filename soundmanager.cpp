#include "soundmanager.h"

#include <stdlib.h>
#include <dlfcn.h>

#define SUNVOX_MAIN
#include "sunvox.h"

void SoundManager::init()
{
	sv_load_dll();
	sv_init( 0, 44100, 2, 0 );
	sv_open_slot( 0 );
	sv_load( 0, "data/snd/stage-1.sunvox" );
}


void SoundManager::deinit()
{
	sv_close_slot( 0 );
	sv_deinit();
	sv_unload_dll();
}

void SoundManager::playMusic()
{
	sv_play_from_beginning( 0 );
}

void SoundManager::stopMusic()
{
	sv_stop( 0 );
}

void SoundManager::play(int s)
{
	int note = 64 + (rand() % (int)(96 - 64 + 1));
	sv_send_event( 0, 8, note, 255, s, 0, 0 );
}

void SoundManager::play(int s, int n)
{
	sv_send_event( 0, 8, n, 64, s, 0, 0 );
}

void SoundManager::play(int s, int n, int v)
{
	sv_send_event( 0, 8, n, v, s, 0, 0 );
}

