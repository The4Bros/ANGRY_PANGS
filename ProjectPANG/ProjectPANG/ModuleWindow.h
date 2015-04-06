#include "Module.h"
#include "Globals.h"
#include "Application.h"

#ifndef __ModuleWindow_H__
#define __ModuleWindow_H__

class Application;

class ModuleWindow : public Module{
public:

	SDL_Window* window;
	unsigned int scale;

	ModuleWindow(Application* app);
	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
};

#endif