#include "Module.h"
#include "Globals.h"
#include "Application.h"

#ifndef __ModuleWindow_H__
#define __ModuleWindow_H__

class Application;

class ModuleWindow : public Module{
private:
	Application* app;
	Uint32 windowFlags;
	SDL_Event* mainEvent;

public:

	SDL_Window* window;

	ModuleWindow(Application* app);
	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
};

#endif