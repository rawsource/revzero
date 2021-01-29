#include "shotemitter.h"

#include <iostream>

#include "shot.h"
#include "soundmanager.h"

ShotEmitter::ShotEmitter()
{
	numshots = 1;
	numbursts = 1;
	shotinterval = 1;
	burstinterval = 8;
}

void ShotEmitter::reset()
{
	shottimer = 0;
	bursttimer = 0;
	shotnum = 0;
	burstnum = 0;
}

bool ShotEmitter::update(float x, float y, float angle)
{
	this->x = x;
	this->y = y;
	this->angle = angle;

	if (shotnum == numshots && burstnum == numbursts)
	{
		if (bursttimer == 0)
		{
			return true;
		}

	}
	if (bursttimer == 0)
	{
		shottimer = 0;
		shotnum = 0;
		burstnum = 0;
	}
	if (shotnum < numshots)
	{
		if (shottimer == 0)
		{
			execute();
			shotnum++;
		}
		shottimer = (shottimer + 1) % shotinterval;
	}
	bursttimer = (bursttimer + 1) % burstinterval;

	return false;
}

void ShotEmitter::execute()
{
	SoundManager::play(10, 64);
	Shot::create(x, y, angle);
}

