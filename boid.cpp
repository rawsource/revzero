#include "boid.h"

#include <iostream>

#include "globals.h"
#include "constants.h"
#include "actor.h"

int Boid::index;
Boid Boid::instances[MAX_INSTANCES];
Mesh* Boid::gfx;
Mesh* Boid::frames[MAX_FRAMES];
Mesh* Boid::gfx2;

void Boid::init()
{
	// assign data
	gfx = &rm->data["boid"];
	gfx2 = &rm->data["void"];

	frames[0] = &rm->data["boid"];
	frames[1] = &rm->data["boid-2"];
	frames[2] = &rm->data["boid"];
	frames[3] = &rm->data["boid-3"];

	// init array
	for (int i = 0; i < MAX_INSTANCES; i++)
	{
		instances[i] = Boid();
		instances[i].active = false;
	}
}

void Boid::renderAll(Actor player)
{
	// render all
	for (int i = 0; i < MAX_INSTANCES; i++)
	{
		if (instances[i].active)
		{
			instances[i].render(player);
		}
	}
}

Boid::Boid()
{
	group = 0;
	hit = false;

	// steering behavior
	mass = 80.f;

	position.x = 0;
	position.y = 0;
}

void Boid::create(int group, float x, float y, int loc)
{
	instances[index].active = true;
	instances[index].group = group;
	if (loc == 0) {
		instances[index].position.x = x - (1280/1.5);
		instances[index].position.y = y;
	}
	if (loc == 1) {
		instances[index].position.x = x + (1280/1.5);
		instances[index].position.y = y;
	}
	if (loc == 2) {
		instances[index].position.x = x;
		instances[index].position.y = y - (720/1.5);
	}
	if (loc == 3) {
		instances[index].position.x = x;
		instances[index].position.y = y + (720/1.5);
	}
	instances[index].health = 2;
	index++;
	if (index == MAX_INSTANCES)
	{
		index = 0;
	}
}

void Boid::create(int group)
{
	instances[index].active = true;
	instances[index].group = group;
	index++;
	if (index == MAX_INSTANCES)
	{
		index = 0;
	}
}

int Boid::rotateDir(float a1, float a2)
{
	a1 = fmod(a1, 360);
	if (a1 < 0) a1 += 360;

	a2 = fmod(a2, 360);
	if (a2 < 0) a2 += 360;

	if (a1 < a2)
	{
		if (abs(a1 - a2) < 180) {
			return 1;
		}
		else {
			return -1;
		}
	}
	else
	{
		if (abs(a1 - a2) < 180) {
			return -1;
		}
		else {
			return 1;
		}
	}
}

void Boid::damage()
{
	hit = true;
	health -= 1;
	if (health == 0) {
		active = false;
	}
}

void Boid::render(Actor player)
{
	// steering behavior

	if (group == 0)
	{
		mass = 80.f;
		steering = wander();

		vec2f v2 = separation();
		steering = steering + v2;

		vec2f v3 = queue();
		steering = steering + v3;

		steering.truncate(MAX_FORCE);
		steering = steering * (1.f / mass);
		velocity = velocity + steering;
		velocity.truncate(MAX_VELOCITY * 0.75f);
	}
	if (group == 1)
	{
		mass = 20.f;
		//steering = follow(player);

		vec2f v1 = seek(player.position);
		steering = steering + v1;
		vec2f v2 = separation();
		steering = steering + v2;

		steering.truncate(MAX_FORCE);
		steering = steering * (1.f / mass);
		velocity = velocity + steering;
		velocity.truncate(MAX_VELOCITY * 1.5f);
	}

	position = position + velocity;

	angle = 90.f - atan2(velocity.y, velocity.x) * RADDEG;

	//direction = atan2(player.position.x - position.x, player.position.y - position.y) * RADDEG;

	/*
	float aa = atan2(player.position.x - position.x, player.position.y - position.y) * RADDEG;
	int rd = rotateDir(direction, aa);
	if (rd == 1) {
		direction += 2.1f;
	} else {
		direction -= 2.1f;
	}
	*/

	//static float offset = 0.f;//128.f;

	// screen collisions
	/*
	if (position.x < 0 - offset) {
		position.x = 0 - offset;
		velocity.x = -velocity.x;
	}
	if (position.x > SCREEN_WIDTH + offset) {
		position.x = SCREEN_WIDTH + offset;
		velocity.x = -velocity.x;
	}
	if (position.y < 0 - offset) {
		position.y = 0 - offset;
		velocity.y = -velocity.y;
	}
	if (position.y > SCREEN_HEIGHT + offset) {
		position.y = SCREEN_HEIGHT + offset;
		velocity.y = -velocity.y;
	}
	*/

	// state change
	/*
	if ( getDistance(position, player.position) < 350.f )
	{
		state = 2;
	}
	else {
		state = 1;
	}
	*/

	// gfx
	if (group == 0)
	{
		gfx2->render(position.x, position.y, angle, 1, hit);
		if (hit) hit = false;
	}

	// animation
	if (group == 1)
	{
		frames[frame]->render(position.x, position.y, angle, 1, hit);
		timer += 1;
		if (timer == 3)
		{
			if (hit) hit = false;
			timer = 0;
			frame += 1;
			if (frame == MAX_FRAMES) frame = 0;
		}
	}
}

vec2f Boid::collisionAvoidance()
{
	vec2f tv = vec2f(velocity);
	tv.normalize();
	tv = tv * (MAX_AVOID_AHEAD * velocity.length() / MAX_VELOCITY);
	ahead = vec2f(position) + tv;
	return avoidance;
}

bool Boid::isOnLeaderSight(Actor leader, vec2f ahead)
{
	return getDistance(ahead, position) <= LEADER_SIGHT_RADIUS
		|| getDistance(leader.position, position) <= LEADER_SIGHT_RADIUS;
}

vec2f Boid::follow(Actor leader)
{
	vec2f force;
	vec2f tv = vec2f(leader.velocity);

	tv.normalize();
	tv = tv * LEADER_BEHIND_DIST;

	ahead = vec2f(leader.position) + tv;

	tv = tv * -1.f;
	vec2f behind = vec2f(leader.position) + tv;

	if (isOnLeaderSight(leader, ahead))
	{
		vec2f v1 = evade(leader);
		force = force + v1;
		force = force * 10.8f;
	}
	else {
	}

	vec2f v2 = arrival(behind);
	force = force + v2;
	vec2f v3 = separation();
	force = force + v3;

	return force;
}

Boid* Boid::getNeighborAhead()
{
	Boid ret;
	vec2f qa = vec2f(velocity);
	qa.normalize();
	qa = qa * MAX_QUEUE_AHEAD;
	ahead = vec2f(position) + qa;
	for (int i = 0; i < MAX_INSTANCES; i++)
	{
		Boid *neighbor = &instances[i];
		if (! neighbor->active) continue;
		float d = getDistance(ahead, neighbor->position);
		if (neighbor != this && d <= MAX_QUEUE_RADIUS)
		{
			return neighbor;
		}
	}
	return NULL;
}

float Boid::getDistance(vec2f a, vec2f b)
{
	return sqrt((a.x - b.x) * (a.x - b.x)  + (a.y - b.y) * (a.y - b.y));
}

vec2f Boid::avoid()
{
	vec2f tv = vec2f(velocity);
	tv.normalize();
	tv = tv * (MAX_AVOID_AHEAD * velocity.length() / MAX_VELOCITY);
	ahead = vec2f(position) + tv;

	return vec2f(0, 0);
}

vec2f Boid::queue()
{
	vec2f v = vec2f(velocity);
	vec2f brake;
	Boid *neighbor = getNeighborAhead();
	if (neighbor)
	{
		brake.x = -steering.x * 0.5;
		brake.y = -steering.y * 0.5;
		v = v * -1.f;
		brake = brake + v;
		vec2f v1 = separation();
		brake = brake + v1;
		if (getDistance(position, neighbor->position)
				<= MAX_QUEUE_RADIUS)
		{
			velocity = velocity * 0.3f;
		}
	}
	return brake;
}

vec2f Boid::separation()
{
	vec2f force;
	int neighborcount = 0;
	for (int i = 0; i < MAX_INSTANCES; i++)
	{
		Boid *b = &instances[i];
		if (! b->active) continue;
		if (b != this && getDistance(b->position, position)
				<= SEPARATION_RADIUS)
		{
			force.x += b->position.x - position.x;
			force.y += b->position.y - position.y;
			neighborcount++;
		}
	}
	if (neighborcount != 0)
	{
		force.x /= neighborcount;
		force.y /= neighborcount;
		force = force * -1.f;
	}
	force.normalize();
	force = force * MAX_SEPARATION;
	return force;
}

vec2f Boid::seek(vec2f t)
{
	vec2f force;
	desired = t - position;
	desired.normalize();
	desired = desired * MAX_VELOCITY;
	force = desired - velocity;
	return force;
}

vec2f Boid::arrival(vec2f t)
{
	vec2f force;
	float distance, slowingradius = SLOWING_RADIUS;
	desired = t - position;
	distance = desired.length();
	desired.normalize();
	if (distance <= slowingradius) {
		desired = desired * (MAX_VELOCITY * distance / slowingradius);
	}
	else {
		desired = desired * MAX_VELOCITY;
	}
	force = desired - velocity;
	return force;
}

vec2f Boid::flee(vec2f t)
{
	vec2f force;
	desired = position - t;
	desired.normalize();
	desired = desired * MAX_VELOCITY;
	force = desired - velocity;
	return force;
}

vec2f Boid::persuit(Actor p)
{
	distance = p.position - position;
	if (distance.length() < 3000)
	{
		float updates = distance.length() / MAX_VELOCITY;
		vec2f tv;
		tv.x = p.velocity.x;
		tv.y = p.velocity.y;
		tv = tv * updates;
		targetfutureposition = p.position + tv;
		return seek(targetfutureposition);
	}
	else
	{
		return seek(p.position);
	}
}

vec2f Boid::evade(Actor p)
{
	distance = p.position - position;
	float updates = distance.length() / MAX_VELOCITY;
	vec2f tv;
	tv.x = p.velocity.x;
	tv.y = p.velocity.y;
	tv = tv * updates;
	targetfutureposition = p.position + tv;
	return flee(targetfutureposition);
}

vec2f Boid::wander()
{
	vec2f wanderforce, circlecenter, displacement;
	circlecenter = vec2f(velocity.x, velocity.y);
	circlecenter.normalize();
	circlecenter = circlecenter * CIRCLE_DISTANCE;
	displacement = vec2f(0.f, -1.f);
	displacement = displacement * CIRCLE_RADIUS;
	displacement = setAngle(displacement, wanderangle);
	wanderangle += rand() * ANGLE_CHANGE - ANGLE_CHANGE * 0.5f;
	wanderforce = circlecenter + displacement;
	return wanderforce;
}

vec2f Boid::setAngle(vec2f vector, float value)
{
	float len = vector.length();
	vector.x = cos(value) * len;
	vector.y = sin(value) * len;
	return vector;
}

