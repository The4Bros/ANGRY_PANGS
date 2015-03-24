
#include "Globals.h"
#include "Module.h"
#include "Application.h"
#include "ModuleWindow.h"

ModuleWindow::ModuleWindow(Application* app) : Module(app)
{
	window = NULL;
}

bool ModuleWindow::Init()
{
	Uint32 windowFlags = NULL;
	if (SHOWN){ windowFlags |= SDL_WINDOW_SHOWN; }
	if (FULLSCREEN){ windowFlags |= SDL_WINDOW_FULLSCREEN; }
	if (RESIZABLE){ windowFlags |= SDL_WINDOW_RESIZABLE; }

	window = SDL_CreateWindow(WINDOW_TITLE, 80, 80, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);
	if (window == NULL){ return false; }

	return true;
}

update_status ModuleWindow::PreUpdate()
{
	return UPDATE_CONTINUE;
}

update_status ModuleWindow::Update()
{
	
	return UPDATE_CONTINUE;
}

update_status ModuleWindow::PostUpdate()
{
	return UPDATE_CONTINUE;
}

bool ModuleWindow::CleanUp()
{
	if (window != NULL)
	{
		SDL_DestroyWindow(window);
	}
	return true;
}
