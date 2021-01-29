#include "playstate.h"

#include <iostream>
#include <fstream>

#include <SDL2/SDL.h>

#include "globals.h"
#include "constants.h"
#include "titlestate.h"
#include "starfield.h"
#include "shot.h"
#include "boid.h"
#include "explosion.h"
#include "soundmanager.h"

#include "json.hpp"

// for convenience
using json = nlohmann::json;

PlayState PlayState::m_PlayState;

void PlayState::init()
{
	player = new Player();

	Shot::init();
	Boid::init();
	Explosion::init();
	StarField::init();

	SoundManager::playMusic();

	// load some boids
	json j;
	std::ifstream ifs("data/flock.json");
	ifs >> j;

	for (auto& element : j) {
		float x = element["x"];
		float y = element["y"];
		Boid::create(1, x, y, 0);
	}
}

void PlayState::cleanup()
{
	SoundManager::stopMusic();

	delete player;
	player = nullptr;
}

void PlayState::pause()
{
}

void PlayState::resume()
{
}

void PlayState::handleEvents()
{
	SDL_Event event;

	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				game->exit();
				break;

			case SDL_WINDOWEVENT:
				if (event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED)
				{
					if (game->ispaused)
						game->ispaused = false;
				}
				else if (event.window.event == SDL_WINDOWEVENT_FOCUS_LOST)
				{
					if (! game->ispaused)
						game->ispaused = true;
				}

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						//json j;
						//for (int i = 0; i < Boid::MAX_INSTANCES; i++)
						//{
						//	Boid b = Boid::instances[i];
						//	if (! b.active) continue;
						//	json o;
						//	o["x"] = b.position.x; // - (1280.f * 0.5f);
						//	o["y"] = b.position.y;
						//	j.push_back(o);
						//}
						//std::string s = j.dump();
						//std::cout << j.dump(4) << std::endl;
						// write to file
						/*
						std::ofstream myfile;
						myfile.open("data/flock.json");
						myfile << s;
						myfile.close();
						*/
						//
						game->changeState(TitleState::instance());
						//game->exit();
						break;
				}
				break;
		}
		player->handleEvent(event);
	}
}

void PlayState::update()
{
	player->update();

	// begin temp
	if (timer == 60*5)
	{
		//SoundManager::play(8, 64, 128);
		int note = 16 + (rand() % (int)(32 - 16 + 1));
		SoundManager::play(8, note, 255);

		// load some boids
		json j;
		std::ifstream ifs("data/flock.json");
		ifs >> j;

		int i = 0;
		int output1 = 0 + (rand() % (int)(3 - 0 + 1));
		for (auto& element : j) {
			float x = element["x"];
			float y = element["y"];
			Boid::create(1, x, y, output1);
			i++;
			if (i == 8) break;
		}
		i = 0;
		int output2 = 0 + (rand() % (int)(3 - 0 + 1));
		if (output1 == output2) {
			output2++;
			if (output2 == 4) {
				output2 = 0;
			}
		}
		for (auto& element : j) {
			float x = element["x"];
			float y = element["y"];
			Boid::create(1, x, y, output2);
			i++;
			if (i == 8) break;
		}
		timer = 0;
	}
	timer++;
	// end temp

	// collisions
	for (int i = 0; i < Shot::MAX_INSTANCES; i++)
	{
		if (! Shot::instances[i].active) continue;

		for (int j = 0; j < Boid::MAX_INSTANCES; j++)
		{
			if (! Boid::instances[j].active) continue;

			float radius = 32.f;
			float x1 = Shot::instances[i].x;
			float y1 = Shot::instances[i].y;
			float x2 = Boid::instances[j].position.x;
			float y2 = Boid::instances[j].position.y;

			float dx = x2 - x1;
			float dy = y2 - y1;

			if (dx * dx + dy * dy <= radius * radius)
			{
				Boid::instances[j].damage();

				// death
				if (Boid::instances[j].active == false)
				{
					//SoundManager::play(6);
					SoundManager::play(6, 32, 128);

					Explosion::create(
							Boid::instances[j].position.x,
							Boid::instances[j].position.y, 0);
					Explosion::create(
							Boid::instances[j].position.x,
							Boid::instances[j].position.y, 1);
				}
				else
				{
					Shot::instances[i].destroy();
				}
			}
		}
	}

}

void PlayState::render()
{
	float gx = ((player->position.x * SCREEN_WIDTH / 20) / SCREEN_WIDTH);
	float gy = ((player->position.y * SCREEN_HEIGHT / 20) / SCREEN_HEIGHT);

	StarField::renderAll(-gx, -gy);

	rm->data["nebula"].render(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0, 1);

	Boid::renderAll(*player);
	Explosion::renderAll();
	player->render();
	Shot::renderAll();
}

