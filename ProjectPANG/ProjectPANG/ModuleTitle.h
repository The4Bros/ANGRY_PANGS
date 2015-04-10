#include "Module.h"
#include "Globals.h"
#include "Application.h"


#ifndef __ModuleTitle_H__
#define __ModuleTitle_H__

class ModuleTitle : public Module{
public:

	SDL_Rect background_rect, insert_coin_rect;

	int current_time;
	time_t 	timer;

	ModuleTitle(Application* app);
	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
};

#endif