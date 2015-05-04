#include "ModulePlane.h"

ModulePlane::ModulePlane(Application* app) : Module(app)
{
	// if (app->stage % 3 == 1){}  plane
	background_rect = { 0, 0, SCREEN_WIDTH * app->windowModule->scale, SCREEN_HEIGHT * app->windowModule->scale };
	background_source_rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	// city rects
	city_rect[0] =  { 344 * app->windowModule->scale,  72 * app->windowModule->scale, 8 * app->windowModule->scale, 8 * app->windowModule->scale };
	city_rect[1] =  { 304 * app->windowModule->scale,  72 * app->windowModule->scale, 8 * app->windowModule->scale, 8 * app->windowModule->scale };
	city_rect[2] =  { 288 * app->windowModule->scale, 104 * app->windowModule->scale, 8 * app->windowModule->scale, 8 * app->windowModule->scale };
	city_rect[3] =  { 304 * app->windowModule->scale, 104 * app->windowModule->scale, 8 * app->windowModule->scale, 8 * app->windowModule->scale };
	city_rect[4] =  { 332 * app->windowModule->scale, 164 * app->windowModule->scale, 8 * app->windowModule->scale, 8 * app->windowModule->scale };
	city_rect[5] =  { 268 * app->windowModule->scale, 100 * app->windowModule->scale, 8 * app->windowModule->scale, 8 * app->windowModule->scale };
	city_rect[6] =  { 208 * app->windowModule->scale,  40 * app->windowModule->scale, 8 * app->windowModule->scale, 8 * app->windowModule->scale };
	city_rect[7] =  { 176 * app->windowModule->scale,  48 * app->windowModule->scale, 8 * app->windowModule->scale, 8 * app->windowModule->scale };
	city_rect[8] =  { 152 * app->windowModule->scale,  40 * app->windowModule->scale, 8 * app->windowModule->scale, 8 * app->windowModule->scale };
	city_rect[9] =  { 132 * app->windowModule->scale,  68 * app->windowModule->scale, 8 * app->windowModule->scale, 8 * app->windowModule->scale };
	city_rect[10] = { 180 * app->windowModule->scale,  68 * app->windowModule->scale, 8 * app->windowModule->scale, 8 * app->windowModule->scale };
	city_rect[11] = { 204 * app->windowModule->scale,  84 * app->windowModule->scale, 8 * app->windowModule->scale, 8 * app->windowModule->scale };
	city_rect[12] = { 204 * app->windowModule->scale, 124 * app->windowModule->scale, 8 * app->windowModule->scale, 8 * app->windowModule->scale };
	city_rect[13] = {  80 * app->windowModule->scale,  64 * app->windowModule->scale, 8 * app->windowModule->scale, 8 * app->windowModule->scale };
	city_rect[14] = {  44 * app->windowModule->scale, 100 * app->windowModule->scale, 8 * app->windowModule->scale, 8 * app->windowModule->scale };
	city_rect[15] = {  88 * app->windowModule->scale, 192 * app->windowModule->scale, 8 * app->windowModule->scale, 8 * app->windowModule->scale };
	city_rect[16] = {  12 * app->windowModule->scale, 156 * app->windowModule->scale, 8 * app->windowModule->scale, 8 * app->windowModule->scale };
	
	city_source_rect[0] = { 216, 208, 8, 8 };
	city_source_rect[1] = { 216, 216, 8, 8 };

	for (unsigned int i = 0; i < 6; i++)
	{
		plane_source_rect[i] = { 224 + (i * 16), 208, 16, 16 };
	}

}


bool ModulePlane::Init()
{
	app->audioModule->PlayMusic(17);

	plane_rect = app->chooseCityModule->selection_rect[(app->stage - 1) / 3];

	ticks = 0;
	return true;
}
update_status ModulePlane::PreUpdate(){ return UPDATE_CONTINUE; }
update_status ModulePlane::Update()
{
	if (ticks > 180){ return CHANGE_TO_PLAY; }

	ticks++;

	app->renderModule->Print(app->texturesModule->level_complete, &background_source_rect, &background_rect);

	app->fontManagerModule->Write_On_Screen("Player-1", 8 * app->windowModule->scale, 209 * app->windowModule->scale, 8 * app->windowModule->scale);
	app->fontManagerModule->Write_On_Screen(ticks, 8 * app->windowModule->scale, 230 * app->windowModule->scale, 8 * app->windowModule->scale);

	return UPDATE_CONTINUE;
}
update_status ModulePlane::PostUpdate(){ return UPDATE_CONTINUE; }
bool ModulePlane::CleanUp(){ return true; }