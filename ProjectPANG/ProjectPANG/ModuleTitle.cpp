#include "ModuleTitle.h"

ModuleTitle::ModuleTitle(Application* app) : Module(app){}

bool ModuleTitle::Init()
{
	background_rect = { 77, 29, 230 * app->windowModule->scale, 150 * app->windowModule->scale };
	insert_coin_rect = { 77, 29, 150 * app->windowModule->scale, 140 * app->windowModule->scale };

	current_time = 0;

	return true;
}

update_status ModuleTitle::PreUpdate()
{
	if (difftime(time(NULL), timer) >= 1)
	{
		current_time++;
		time(&timer);
	}

	return UPDATE_CONTINUE;
}
update_status ModuleTitle::Update()
{


	return CHANGE_TO_PLAY;
}
update_status ModuleTitle::PostUpdate(){ return UPDATE_CONTINUE; }

bool ModuleTitle::CleanUp(){ return true; }