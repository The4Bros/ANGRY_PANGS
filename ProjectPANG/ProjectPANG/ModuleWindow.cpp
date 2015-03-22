
#include "Globals.h"
#include "Module.h"
#include "ModuleWindow.h"

ModuleWindow::ModuleWindow(Application* app) : Module(app)
{
	window = NULL;
}

bool ModuleWindow::Init()
{
	windowFlags = SDL_WINDOW_SHOWN;
	window = SDL_CreateWindow(WINDOW_TITLE, 80, 80, 600, 400, windowFlags);
	mainEvent = new SDL_Event();
	if (window == NULL || mainEvent == NULL){ return false; }
	return true;
}

update_status ModuleWindow::PreUpdate()
{
	return UPDATE_CONTINUE;
}

update_status ModuleWindow::Update()
{
	SDL_PollEvent(mainEvent);
	if (mainEvent->type == SDL_QUIT){ return UPDATE_STOP; }
	return UPDATE_CONTINUE;
}

update_status ModuleWindow::PostUpdate()
{
	return UPDATE_CONTINUE;
}

bool ModuleWindow::CleanUp()
{
	delete[] mainEvent;
	delete &windowFlags;
	if (window != NULL)
	{
		SDL_DestroyWindow(window);
	}
	return true;
}
