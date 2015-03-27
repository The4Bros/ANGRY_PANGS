
#include "Globals.h"
#include "Module.h"
#include "Application.h"
#include "ModuleInput.h"

ModuleInput::ModuleInput(Application* app) : Module(app)
{
	key = NULL;
	mainEvent = NULL;
}

bool ModuleInput::Init()
{
	mainEvent = new SDL_Event();
	if (mainEvent == NULL){ return false; }

	return true;
}

update_status ModuleInput::PreUpdate()
{
	//SDL_PumpEvents();

	SDL_PollEvent(mainEvent);
	
	key = SDL_GetKeyboardState(NULL);

	if (key[SDL_SCANCODE_ESCAPE])
	{
		return UPDATE_STOP;
	}

	return UPDATE_CONTINUE;
}

update_status ModuleInput::Update()
{
	if (mainEvent->type == SDL_QUIT){ return UPDATE_STOP; }

	if (key[SDLK_ESCAPE]){ return UPDATE_STOP; }

	return UPDATE_CONTINUE;
}

update_status ModuleInput::PostUpdate(){ return UPDATE_CONTINUE; }

bool ModuleInput::CleanUp()
{
	delete[] mainEvent;
	//delete key;
	return true;
}