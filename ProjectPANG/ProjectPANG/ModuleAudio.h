#include "Module.h"
#include "Globals.h"
#include "Application.h"

#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

#ifndef __ModuleAudio_H__
#define __ModuleAudio_H__

#define DEFAULT_MUSIC_FADE_TIME 2.0f

class ModuleAudio : public Module
{
private:
	Mix_Music* music;
	DoubleNodedList<Mix_Chunk*>	fx;

public:

	const char* music_paths[19];

	unsigned int balloon_pop;
	unsigned int insert_coin;

	ModuleAudio(Application* app);
	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	bool PlayMusic(const char* path, float fade_time = DEFAULT_MUSIC_FADE_TIME); // Play a music file
	unsigned int LoadFx(const char* path); // Load a WAV in memory
	bool PlayFx(unsigned int fx, int repeat = 0); // Play a previously loaded WAV
};

#endif