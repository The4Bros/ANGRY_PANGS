
#include "Module.h"
#include "Globals.h"
#include "ModuleRender.h"

ModuleRender::ModuleRender(Application* app) : Module(app)
{
	renderer = NULL;
	rendererFlags = 0;
}

bool ModuleRender::Init()
{
	if (VSYNC)
	{
		rendererFlags |= SDL_RENDERER_PRESENTVSYNC;
	}
	renderer = SDL_CreateRenderer(app->windowModule->window, -1, rendererFlags);
	if (renderer == NULL)
	{
		return false;
	}
	return true;
}

update_status ModuleRender::PreUpdate()
{
	return UPDATE_CONTINUE;
}

update_status ModuleRender::Update()
{
	return UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate()
{
	return UPDATE_CONTINUE;
}

bool ModuleRender::CleanUp()
{
	delete &rendererFlags;
	if (renderer != NULL)
	{
		SDL_DestroyRenderer(app->renderModule->renderer);
	}
	return true;
}
