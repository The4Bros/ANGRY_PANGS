
#include "Globals.h"
#include "Module.h"
#include "Application.h"
#include "ModuleRender.h"

ModuleRender::ModuleRender(Application* app) : Module(app)
{
	renderer = NULL;
}

bool ModuleRender::Init()
{
	Uint32 rendererFlags = NULL;
	if (ACCELERATED){ rendererFlags |= SDL_RENDERER_ACCELERATED; }
	if (VSYNC){ rendererFlags |= SDL_RENDERER_PRESENTVSYNC; }

	renderer = SDL_CreateRenderer(app->windowModule->window, -1, rendererFlags);
	if (renderer == NULL){ return false; }

	return true;
}

update_status ModuleRender::PreUpdate()
{
	SDL_RenderClear(renderer);
	return UPDATE_CONTINUE;
}

update_status ModuleRender::Update()
{
	return UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate()
{
	SDL_RenderPresent(renderer);
	return UPDATE_CONTINUE;
}

bool ModuleRender::CleanUp()
{
	if (renderer != NULL)
	{
		SDL_DestroyRenderer(app->renderModule->renderer);
		return true;
	}
	return false;
}
