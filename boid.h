#ifndef RZ_BOID_H
#define RZ_BOID_H

#include "vec2.h"
#include "mesh.h"
#include "actor.h"

class Boid : public Actor
{
	public:
		Boid();

		static const int MAX_INSTANCES = 1024;
		static const int MAX_FRAMES = 4;

		void render(Actor player);

		// active
		bool active;
		bool hit;

		// begin temp
		int group;
		void damage();
		// end temp

		// instances
		static int index;
		static void init();
		static void create(int group);
		static void create(int group, float x, float y, int loc);
		static void renderAll(Actor player);
		static Boid instances[MAX_INSTANCES];

		// pointers to data
		static Mesh* gfx;
		static Mesh* gfx2;
		static Mesh* frames[MAX_FRAMES];

	private:
		int frame = 0;
		int timer = 0;

		float angle;
		float direction;
		int rotateDir(float a1, float a2);

		// begin temp
		int health;
		// end temp

		// steering behavior
		static constexpr float MAX_FORCE = 17.5f;
		static constexpr float MAX_VELOCITY = 2.f;

		// arrive
		static constexpr float SLOWING_RADIUS = 400.f;

		// wander
		static constexpr float CIRCLE_DISTANCE = 20.f;
		static constexpr float CIRCLE_RADIUS = 120.f;
		static constexpr float ANGLE_CHANGE = 120.1f;

		// avoidance
		static constexpr float MAX_AVOID_AHEAD = 50;
		static constexpr float AVOID_FORCE = 600;

		// queuing
		static constexpr float MAX_QUEUE_AHEAD = 80;
		static constexpr float MAX_QUEUE_RADIUS = 100;

		// separation
		static constexpr float MAX_SEPARATION = 8;
		static constexpr float SEPARATION_RADIUS = 60;

		// follow
		static constexpr float LEADER_BEHIND_DIST = 50;
		static constexpr float LEADER_SIGHT_RADIUS = 100;

		vec2f seek(vec2f t);
		vec2f arrival(vec2f t);
		vec2f flee(vec2f t);
		vec2f wander();
		vec2f persuit(Actor p);
		vec2f follow(Actor p);
		vec2f evade(Actor p);
		vec2f queue();
		vec2f separation();
		vec2f avoid();
		vec2f collisionAvoidance();

		float getDistance(vec2f a, vec2f b);
		Boid* getNeighborAhead();
		vec2f setAngle(vec2f vector, float value);
		bool isOnLeaderSight(Actor leader, vec2f ahead);

		vec2f desired;
		vec2f steering;
		vec2f distance;
		vec2f targetfutureposition;
		vec2f ahead;
		vec2f ahead2;
		vec2f avoidance;
		vec2f braking;

		float mass;
		float wanderangle;
};

#endif

