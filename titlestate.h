#ifndef RZ_TITLESTATE_H
#define RZ_TITLESTATE_H

#include "gamestate.h"

class TitleState : public GameState
{
	public:
		void init();
		void cleanup();

		void pause();
		void resume();

		void handleEvents();
		void update();
		void render();

		static TitleState* instance()
		{
			return &m_TitleState;
		}

	protected:
		TitleState() {}

	private:
		static TitleState m_TitleState;
};

#endif

