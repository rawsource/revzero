#ifndef RZ_SOUNDMANAGER_H
#define RZ_SOUNDMANAGER_H

class SoundManager
{
	public:
		SoundManager();
		~SoundManager();

		static void init();
		static void deinit();
		static void playMusic();
		static void stopMusic();
		static void play(int s);
		static void play(int s, int n);
		static void play(int s, int n, int v);
	
		void setTrack();
		int track;
};

#endif

