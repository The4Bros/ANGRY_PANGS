#include "ModulePlane.h"

ModulePlane::ModulePlane(Application* app) : Module(app){}
bool ModulePlane::Init()
{
	// if (app->stage % 3 == 1){}  plane
	background_rect = { 0, 0, SCREEN_WIDTH * app->windowModule->scale, SCREEN_HEIGHT * app->windowModule->scale };
	source_rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	app->audioModule->PlayMusic(17);

	ticks = 0;
	return true;
}
update_status ModulePlane::PreUpdate(){ return UPDATE_CONTINUE; }
update_status ModulePlane::Update()
{
	if (ticks > 180){ return CHANGE_TO_PLAY; }

	ticks++;

	app->renderModule->Print(app->texturesModule->level_complete, &source_rect, &background_rect);

	app->fontManagerModule->Write_On_Screen("Player-1", 8 * app->windowModule->scale, 209 * app->windowModule->scale, 8 * app->windowModule->scale);
	app->fontManagerModule->Write_On_Screen(ticks, 8 * app->windowModule->scale, 230 * app->windowModule->scale, 8 * app->windowModule->scale);

	return UPDATE_CONTINUE;
}
update_status ModulePlane::PostUpdate(){ return UPDATE_CONTINUE; }
bool ModulePlane::CleanUp(){ return true; }