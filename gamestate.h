#ifndef RZ_GAMESTATE_H
#define RZ_GAMESTATE_H

class GameState
{
	public:
		virtual void init() = 0;
		virtual void cleanup() = 0;

		virtual void pause() = 0;
		virtual void resume() = 0;

		virtual void handleEvents() = 0;
		virtual void update() = 0;
		virtual void render() = 0;

	protected:
		GameState() {};
};

#endif

