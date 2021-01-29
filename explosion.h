#ifndef RZ_EXPLOSION_H
#define RZ_EXPLOSION_H

#include "mesh.h"

class Explosion
{
	public:
		// initialize
		Explosion();

		static const int MAX_INSTANCES = 64;

		// active
		bool active;

		// position
		float x, y;

		int type;
		float scale;

		// update and render
		void render();
		void destroy();
		static void renderAll();

		// create
		static void create(float x, float y, int type);

		// init instances
		static void init();

		// index
		static int index;

		// instances
		static Explosion instances[MAX_INSTANCES];

	private:
		// pointers to data
		static Mesh *gfx;
		static Mesh *gfx2;
};

#endif
