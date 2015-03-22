#include "Module.h"
#include "Globals.h"
#include "Application.h"

#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

#ifndef __ModuleAudio_H__
#define __ModuleAudio_H__

class ModuleAudio : public Module{
public:
	ModuleAudio(Application* app);
	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
};

#endif