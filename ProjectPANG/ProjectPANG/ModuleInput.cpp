
#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"


ModuleInput::ModuleInput(Application* app) : Module(app)
{
	key = NULL;
}

bool ModuleInput::Init()
{
	key = NULL;
	return true;
}

update_status ModuleInput::PreUpdate(){ return UPDATE_CONTINUE; }

update_status ModuleInput::Update()
{
	key = SDL_GetKeyboardState(NULL);

	if (key[SDLK_ESCAPE]){ return UPDATE_STOP; }
	if (app->inputModule->key[SDLK_LEFT]){ LOG("\n LEFT pressed"); }
	if (app->inputModule->key[SDLK_RIGHT]){ LOG("\n RIGHT pressed"); }
	if (app->inputModule->key[SDLK_UP]){ LOG("\n UP pressed"); }
	if (app->inputModule->key[SDLK_DOWN]){ LOG("\n DOWN pressed"); }
	if (app->inputModule->key[SDLK_SPACE]){ LOG("\n SPACE pressed"); }

	return UPDATE_CONTINUE;
}

update_status ModuleInput::PostUpdate(){ return UPDATE_CONTINUE; }

bool ModuleInput::CleanUp()
{
	delete key;
	return true;
}
