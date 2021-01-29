#include "shot.h"

#include "globals.h"
#include "constants.h"

// shot instance index
int Shot::index;

// mesh
Mesh *Shot::gfx;

// instances
Shot Shot::instances[MAX_INSTANCES];

Shot::Shot()
{
	active = false;
	speed = 20;
	gfx = &rm->data["shot-0"];
}

void Shot::init()
{
	// fill array with shots
	for (int i = 0; i < MAX_INSTANCES; i++)
	{
		instances[i] = Shot();
	}
}

void Shot::renderAll()
{
	// render all active shots
	for (int i = 0; i < MAX_INSTANCES; i++)
	{
		if (instances[i].active)
		{
			instances[i].render();
		}
	}
}

void Shot::render()
{
	// update
	x += sin(angle * DEGRAD) * speed;
	y += cos(angle * DEGRAD) * speed;

	// render
	gfx->render(x, y, angle, 1);

	// screen collisions
	if (x < 0) {
		active = false;
	}
	if (x > SCREEN_WIDTH) {
		active = false;
	}
	if (y < 0) {
		active = false;
	}
	if (y > SCREEN_HEIGHT) {
		active = false;
	}
}

void Shot::create(float x, float y, float angle)
{
	instances[index].active = true;
	instances[index].angle = angle;
	instances[index].x = x;
	instances[index].y = y;
	index++;
	if (index == MAX_INSTANCES)
	{
		index = 0;
	}
}

void Shot::destroy()
{
	active = false;
}
