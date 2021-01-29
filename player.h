#ifndef RZ_PLAYER_H
#define RZ_PLAYER_H

#include <SDL2/SDL.h>

#include "mesh.h"
#include "vec2.h"
#include "actor.h"

#include "shotemitter.h"

class Player : public Actor
{
	public:
		// initializes the variables
		Player();
		~Player();

		static constexpr float SPEED = 6.f;

		// takes key presses and adjusts the player's velocity
		void handleEvent( SDL_Event& );

		// moves the player
		void update();

		// shows the player on the screen
		void render();

		// shooting
		ShotEmitter* emitter;

	private:
		// aim distance
		static constexpr float AIM_DISTANCE = 60.f;

		// aim fields
		float aim_x, aim_y;
		vec2f warp;
		float aim_angle;
		bool aim_activated = false, aim_active = false;

		// shot fields
		bool shot_activated = false, shot_active = false;

		// the x and y offsets of the player
		float x, y;

		// player speed and angle
		float speed, angle;

		// directional
		bool left = false, right = false, up = false, down = false;

		// pointers to data
		Mesh *gfx;
		Mesh *aim;
		Mesh *burst;
};

#endif

