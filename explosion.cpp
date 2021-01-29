#include "explosion.h"

#include "globals.h"
#include "constants.h"

// instance index
int Explosion::index;

// mesh
Mesh* Explosion::gfx;
Mesh* Explosion::gfx2;

// instances
Explosion Explosion::instances[MAX_INSTANCES];

Explosion::Explosion()
{
	active = false;
	gfx = &rm->data["explosion-0"];
	gfx2 = &rm->data["explosion-1"];
}

void Explosion::init()
{
	for (int i = 0; i < MAX_INSTANCES; i++)
	{
		instances[i] = Explosion();
		instances[i].scale = 0.1f;
	}
}

void Explosion::renderAll()
{
	for (int i = 0; i < MAX_INSTANCES; i++)
	{
		if (instances[i].active)
		{
			instances[i].render();
		}
	}
}


void Explosion::render()
{
	// render
	

	if (type == 0) {
		gfx2->render(x, y, 0, scale);
		scale += 0.2f;
		if (scale > 2.f) {
			destroy();
		}
	}
	if (type == 1) {
		gfx->render(x, y, 0, scale);
		scale += 0.1f;
		if (scale > 0.75f) {
			destroy();
		}
	}
}

void Explosion::create(float x, float y, int type)
{
	instances[index].active = true;
	instances[index].x = x;
	instances[index].y = y;
	instances[index].type = type;
	index++;
	if (index == MAX_INSTANCES)
	{
		index = 0;
	}
}

void Explosion::destroy()
{
	active = false;
	scale = 0.1f;
}
