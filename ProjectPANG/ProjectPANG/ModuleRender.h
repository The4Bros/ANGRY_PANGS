#include "Module.h"
#include "Globals.h"
#include "Application.h"

#ifndef __ModuleRender_H__
#define __ModuleRender_H__


class Application;

class ModuleRender : public Module{
public:

	SDL_Renderer* renderer;

	ModuleRender(Application* app);
	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
};

#endif