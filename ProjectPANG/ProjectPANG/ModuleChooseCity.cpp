#include "ModuleChooseCity.h"

ModuleChooseCity::ModuleChooseCity(Application* app) : Module(app)
{
	// number countdown
	countdown_rect = { 200 * app->windowModule->scale, 40 * app->windowModule->scale, 24 * app->windowModule->scale, 31 * app->windowModule->scale };

	for (unsigned int i = 0; i < 10; i++)
	{
		countdown_source_rect[i] = { (i * 24), 0, 24, 31 };
	}

	// selection squares
	selection_rect[0]  = { 340 * app->windowModule->scale,  68 * app->windowModule->scale, 16 * app->windowModule->scale, 16 * app->windowModule->scale };
	selection_rect[1]  = { 300 * app->windowModule->scale,  68 * app->windowModule->scale, 16 * app->windowModule->scale, 16 * app->windowModule->scale };
	selection_rect[2]  = { 284 * app->windowModule->scale, 100 * app->windowModule->scale, 16 * app->windowModule->scale, 16 * app->windowModule->scale };
	selection_rect[3]  = { 300 * app->windowModule->scale, 100 * app->windowModule->scale, 16 * app->windowModule->scale, 16 * app->windowModule->scale };
	selection_rect[4]  = { 328 * app->windowModule->scale, 160 * app->windowModule->scale, 16 * app->windowModule->scale, 16 * app->windowModule->scale };
	selection_rect[5]  = { 264 * app->windowModule->scale,  96 * app->windowModule->scale, 16 * app->windowModule->scale, 16 * app->windowModule->scale };
	selection_rect[6]  = { 204 * app->windowModule->scale,  36 * app->windowModule->scale, 16 * app->windowModule->scale, 16 * app->windowModule->scale };
	selection_rect[7]  = { 172 * app->windowModule->scale,  44 * app->windowModule->scale, 16 * app->windowModule->scale, 16 * app->windowModule->scale };
	selection_rect[8]  = { 148 * app->windowModule->scale,  36 * app->windowModule->scale, 16 * app->windowModule->scale, 16 * app->windowModule->scale };
	selection_rect[9]  = { 128 * app->windowModule->scale,  64 * app->windowModule->scale, 16 * app->windowModule->scale, 16 * app->windowModule->scale };
	selection_rect[10] = { 176 * app->windowModule->scale,  64 * app->windowModule->scale, 16 * app->windowModule->scale, 16 * app->windowModule->scale };
	selection_rect[11] = { 200 * app->windowModule->scale,  80 * app->windowModule->scale, 16 * app->windowModule->scale, 16 * app->windowModule->scale };
	selection_rect[12] = { 200 * app->windowModule->scale, 120 * app->windowModule->scale, 16 * app->windowModule->scale, 16 * app->windowModule->scale };
	selection_rect[13] = {  76 * app->windowModule->scale,  60 * app->windowModule->scale, 16 * app->windowModule->scale, 16 * app->windowModule->scale };
	selection_rect[14] = {  40 * app->windowModule->scale,  96 * app->windowModule->scale, 16 * app->windowModule->scale, 16 * app->windowModule->scale };
	selection_rect[15] = {  84 * app->windowModule->scale, 188 * app->windowModule->scale, 16 * app->windowModule->scale, 16 * app->windowModule->scale };
	selection_rect[16] = {   8 * app->windowModule->scale, 152 * app->windowModule->scale, 16 * app->windowModule->scale, 16 * app->windowModule->scale };

	selection_source_rect[0] = { 184, 208, 16, 16 };
	selection_source_rect[1] = { 200, 208, 16, 16 };

	// forward return controls
	controls_rect = { 40 * app->windowModule->scale, 208 * app->windowModule->scale, 184 * app->windowModule->scale, 45 * app->windowModule->scale };
	controls_source_rect = { 0, 208, 184, 45 };

	selection_index = 0;
	selection_source_index = 0;
	current_number = 9;
	seconds = 0;
}

bool ModuleChooseCity::Init()
{
	selection_index = 0;
	selection_source_index = 0;
	current_number = 9;
	seconds = app->current_time;




	return true;
}




update_status ModuleChooseCity::Update()
{
	if (seconds != app->current_time) // handle countdown numbers
	{
		if (current_number > 0){ current_number--; seconds = app->current_time; }
		else{ return CHANGE_TO_PLAY;}
	}

	if (app->inputModule->key[SDL_SCANCODE_E] == 1)
	{
		//if (!pause_pressed){ Pause_Scene(); }
	}


	app->renderModule->Print(app->texturesModule->map_sprite, &app->planeModule->background_source_rect, &app->planeModule->background_rect); // print map
	app->renderModule->Print(app->texturesModule->map_countdown_sprite, &countdown_source_rect[current_number], &countdown_rect); // print countdown numbers
	app->renderModule->Print(app->texturesModule->map_sprite, &controls_source_rect, &controls_rect); // print controls
	app->renderModule->Print(app->texturesModule->map_sprite, &selection_source_rect[selection_source_index], &selection_rect[selection_index]); // print selection square

	ticks++;

	return UPDATE_CONTINUE;
}




bool ModuleChooseCity::CleanUp()
{




	return true;
}