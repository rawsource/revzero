
#include "starfield.h"

int StarField::index;
StarField StarField::instances[MAX_INSTANCES];

StarField::StarField()
{
}

void StarField::init()
{
	for (int i = 0; i < MAX_INSTANCES; i++)
	{
		StarField s = StarField();
		s.x = 0 + (rand() % (int)(WIDTH - 0 + 1));
		s.y = 0 + (rand() % (int)(HEIGHT - 0 + 1));
		s.a = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		instances[i] = s;
	}
}

void StarField::render(float gx, float gy)
{
	float tx = x + gx;
	float ty = y + gy;

	if (tx < 0) {
		tx = WIDTH + fmod(tx, WIDTH);
	}
	if (tx > WIDTH) {
		tx = fmod(tx, WIDTH);
	}
	if (ty < 0) {
		ty = HEIGHT + fmod(ty, HEIGHT);
	}
	if (ty > HEIGHT) {
		ty = fmod(ty, HEIGHT);
	}

	glColor4f (1, 1, 1, a);
	glVertex3f(x + (gx * a), y + (gy * a), 90);
}

void StarField::renderAll(float gx, float gy)
{
	glBegin(GL_POINTS);
	for (int i = 0; i < MAX_INSTANCES; i++)
	{
		instances[i].render(gx, gy);
	}
	glEnd();
}
