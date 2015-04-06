#include "Module.h"
#include "Globals.h"
#include "Application.h"

#ifndef __ModuleScene_H__
#define __ModuleScene_H__

class ModuleScene : public Module{
public:
	SDL_Rect background_rect;
	SDL_Rect background_const_source_rect;
	const SDL_Rect* background_const_rect;

	ModuleScene(Application* app);
	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
};
#endif