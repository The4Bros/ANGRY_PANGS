#include "Module.h"
#include "Globals.h"
#include "Application.h"

#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

#ifndef __ModuleAudio_H__
#define __ModuleAudio_H__

enum fx_sound
{
	BALLOON_POP,
	COIN
};

class ModuleAudio : public Module
{
private:

	Mix_Music* music;
	Mix_Chunk fx[2];
	unsigned int music_playing;

public:

	char* music_paths[19];

	ModuleAudio(Application* app);
	ModuleAudio(const ModuleAudio& audio);
	bool Init();
	bool CleanUp();

	bool PlayMusic(); // Resume music
	bool PlayMusic(const unsigned int position); // Play indicated music
	void PauseMusic(); // Pause (free) music
	void PlayFx(fx_sound fx, int repeat = 0); // Play a previously loaded WAV
};

#endif