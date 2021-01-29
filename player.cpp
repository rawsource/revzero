#include "player.h"

#include "globals.h"
#include "constants.h"
#include "explosion.h"
#include "soundmanager.h"

// QWERTY
// ZXC

// QWERTZ
// YXC

// AZERTY
// WXC

Player::Player()
{
	// initialize the offsets
	x = SCREEN_WIDTH / 2;
	y = SCREEN_HEIGHT / 2;

	angle = 0;
	speed = 0;
	aim_x = 0;
	aim_y = 0;
	aim_angle = 0;

	// assign data
	gfx = &rm->data["player"];
	aim = &rm->data["aim"];
	burst = &rm->data["burst-1"];

	// emitter
	emitter = new ShotEmitter();
}

Player::~Player()
{
	delete emitter;
	emitter = nullptr;
}

void Player::handleEvent( SDL_Event& e )
{
	// movement
	if ( e.type == SDL_KEYDOWN )
	{
		switch ( e.key.keysym.sym )
		{
			case SDLK_UP:
				up = true;
				break;
			case SDLK_DOWN:
				down = true;
				break;
			case SDLK_LEFT:
				left = true;
				break;
			case SDLK_RIGHT:
				right = true;
				break;
			case SDLK_c:
				if (e.key.repeat == 0) {
					if (! aim_active) {
						SoundManager::play(6, 33, 128);
						x = warp.x;
						y = warp.y;
						aim_angle = aim_angle - 180;
						Explosion::create(x, y, 0);
					}
				}
				break;
			case SDLK_x:
				aim_active = true;
				if (e.key.repeat == 0) {
					aim_activated = true;
				}
				break;
			case SDLK_z:
			case SDLK_y:
			case SDLK_w:
				shot_active = true;
				if (e.key.repeat == 0) {
					shot_activated = true;
				}
				break;
		}
	}
	if ( e.type == SDL_KEYUP)
	{
		switch ( e.key.keysym.sym )
		{
			case SDLK_UP:
				up = false;
				break;
			case SDLK_DOWN:
				down = false;
				break;
			case SDLK_LEFT:
				left = false;
				break;
			case SDLK_RIGHT:
				right = false;
				break;
			case SDLK_x:
				aim_active = false;
				break;
			case SDLK_z:
			case SDLK_y:
			case SDLK_w:
				shot_active = false;
				break;
		}
	}
}

void Player::update()
{
	// angle
	if (left) angle = -90;
	if (right) angle = 90;
	if (up) angle = 180;
	if (down) angle = 0;
	if (left && down) angle = -45;
	if (right && down) angle = 45;
	if (left && up) angle = -135;
	if (right && up) angle = 135;

	// speed
	if (left || right || up || down) {
		speed = SPEED;
	} else {
		speed = 0;
	}

	// aim
	if (aim_activated)
	{
		aim_activated = false;
		aim_x = x + AIM_DISTANCE * sin(aim_angle * DEGRAD);
		aim_y = y + AIM_DISTANCE * cos(aim_angle * DEGRAD);
		warp.x = aim_x;
		warp.y = aim_y;
	}
	if (aim_active)
	{
		aim_angle = atan2(aim_x - x, aim_y - y) * RADDEG;
	}

	// shooting
	if (shot_active)
	{
		bool done = emitter->update(x, y, aim_angle);
		if (done && shot_activated)
		{
			emitter->reset();
			shot_activated = false;
		}
	}

	// movement
	x += sin(angle * DEGRAD) * speed;
	y += cos(angle * DEGRAD) * speed;

	// screen collisions
	if (x < 0) {
		x = 0;
	}
	if (x > SCREEN_WIDTH) {
		x = SCREEN_WIDTH;
	}
	if (y < 0) {
		y = 0;
	}
	if (y > SCREEN_HEIGHT) {
		y = SCREEN_HEIGHT;
	}

	// set position
	position.x = x;
	position.y = y;

	// compute velocity
	float dispx = position.x - prevposition.x;
	float dispy = position.y - prevposition.y;
	float distance = sqrt(dispx * dispx + dispy * dispy);
	velocity.x = dispx * speed / distance;
	velocity.y = dispy * speed / distance;

	if (isnan(velocity.x)) velocity.x = 0;
	if (isnan(velocity.y)) velocity.y = 0;

	// remember previous position
	prevposition.x = x;
	prevposition.y = y;
}

void Player::render()
{
	// aim
	if (aim_active)
	{
		aim->render(aim_x, aim_y, aim_angle, 1);
	}

	// gfx
	gfx->render(x, y, aim_angle, 1);

	// burst
	if (shot_active)
	{
		//burst->render(x, y, aim_angle, 1);
	}
}

