#ifndef RZ_PLAYSTATE_H
#define RZ_PLAYSTATE_H

#include "gamestate.h"
#include "player.h"

class PlayState : public GameState
{
	public:
		void init();
		void cleanup();

		void pause();
		void resume();

		void handleEvents();
		void update();
		void render();

		// begin temp
		int timer;
		// end temp

		Player* player;

		static PlayState* instance()
		{
			return &m_PlayState;
		}

	protected:
		PlayState() { }

	private:
		static PlayState m_PlayState;
};

#endif

