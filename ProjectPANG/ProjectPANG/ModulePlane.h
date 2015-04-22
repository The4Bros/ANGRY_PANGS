#include "Module.h"
#include "Globals.h"
#include "Application.h"


#ifndef __ModulePlane_H__
#define __ModulePlane_H__

class ModulePlane : public Module{
public:

	SDL_Rect background_rect;
	SDL_Rect source_rect;

	unsigned int ticks;

	ModulePlane(Application* app);
	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
};

#endif