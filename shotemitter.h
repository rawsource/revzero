#ifndef RZ_SHOTEMITTER_H
#define RZ_SHOTEMITTER_H

class ShotEmitter
{
	public:

		ShotEmitter();

		void reset();
		bool update(float x, float y, float angle);
		void execute();

	private:

		int numshots;
		int numbursts;
		int shotinterval;
		int burstinterval;

		int delaytimer;
		int shottimer;
		int bursttimer;

		int shotnum;
		int burstnum;

		float x;
		float y;
		float angle;
};

#endif

