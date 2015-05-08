
#include "ModuleStageEnd.h"

ModuleStageEnd::ModuleStageEnd(Application* app) : Module(app)
{
	for (unsigned int i = 0; i < 1; i++)
	{
		image_source_rect[0][i] = { i * 141, 0, 141, 94 };
	}

	for (unsigned int i = 0; i < 1; i++)
	{
		image_source_rect[1][i] = { i * 141, 141, 141, 94 };
	}

	for (unsigned int i = 0; i < 1; i++)
	{
		image_source_rect[2][i] = { i * 141, 282, 141, 94 };
	}

	for (unsigned int i = 0; i < 1; i++)
	{
		image_source_rect[3][i] = { i * 141, 463, 141, 94 };
	}

	max_index[0] = 0;
	max_index[1] = 0;
	max_index[2] = 0;
	max_index[3] = 0;

	ticks = 0;
	source_index_1 = source_index_2 = 0;
	push_button_shown = true;
}


bool ModuleStageEnd::Init()
{
	app->audioModule->PlayMusic(17);

	image_rect = { 118 * app->windowModule->scale, 32 * app->windowModule->scale, 141 * app->windowModule->scale, 94 * app->windowModule->scale };

	ticks = 0;

	// handle source_index_1 algorithm
	source_index_1 = 0;

	source_index_2 = 0;

	push_button_shown = true;

	return true;
}

update_status ModuleStageEnd::Update()
{
	app->audioModule->StopMusic();

	return CHANGE_TO_PLAY;





	// -------------------------------------------------------------------------------------------------------------------------------------------

	if (ticks > 180)
	{
		if ((app->stage - 1) % 3 == 0) { return CHANGE_TO_PLAY; } // planne module if travelng to new city
		return CHANGE_TO_MAP_PLANE;
	}

	// Update push_button_shown state
	if (ticks % 30 == 0)
	{
		if (push_button_shown) { push_button_shown = false; }
		else{ push_button_shown = true; }
	}

	// Update source_index_2
	if (ticks % 10 == 0)
	{
		if (source_index_2 < max_index[source_index_1]){ source_index_2++; }
		else{ source_index_2 = 0; }
	}



	// Print All

	app->renderModule->Print(app->texturesModule->level_complete, &image_source_rect[source_index_1][source_index_2], &image_rect); // print map

	if ((app->stage - 1) / 10 != 0)
	{
		// print: (app->stage - 1) / 10
	}
	// print: (app->stage - 1) % 10
	// print: STAGE
	// print: TIME BONUS 200 PTS.

	if (ticks > 90)
	{
		// print: NEXT EXTEND 100000 PTS.
	}

	if (push_button_shown)
	{
		// print: PUSH BUTTON
	}

	ticks++;

	return UPDATE_CONTINUE;
}

bool ModuleStageEnd::CleanUp(){ return true; }