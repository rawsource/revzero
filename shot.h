#ifndef RZ_SHOT_H
#define RZ_SHOT_H

#include "mesh.h"

class Shot
{
	public:
		// initialize
		Shot();

		static const int MAX_INSTANCES = 32;

		// active
		bool active;

		// position
		float x, y;

		// speed and angle
		float speed, angle;

		// update and render
		void render();
		void destroy();
		static void renderAll();

		// create
		static void create(float x, float y, float angle);

		// init instances
		static void init();

		// index
		static int index;

		// instances
		static Shot instances[MAX_INSTANCES];

	private:
		// pointers to data
		static Mesh *gfx;
};

#endif

