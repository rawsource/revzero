#ifndef RZ_STARFIELD_H
#define RZ_STARFIELD_H

#include <cstdlib>
#include <cmath>
#include <SDL2/SDL_opengl.h>

class StarField
{
	public:
		StarField();

		static const int MAX_INSTANCES = 512;
		static constexpr float WIDTH = 1280;
		static constexpr float HEIGHT = 720;

		float x, y, a;

		// instances
		static int index;
		static void init();
		static void renderAll(float gx, float gy);
		static StarField instances[MAX_INSTANCES];

	private:
		void render(float gx, float gy);
};

#endif

