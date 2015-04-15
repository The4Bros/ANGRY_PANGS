#include "ModuleScene.h"

ModuleScene::ModuleScene(Application* app) : Module(app)
{
	time_count = NULL;
}

bool ModuleScene::Init()
{
	time_count = new Time_Count(app);

	current_stage = 1;
	load_stage(current_stage);

	background_rect = { 0, 0, SCREEN_WIDTH * app->windowModule->scale, (SCREEN_HEIGHT - 32) * app->windowModule->scale };
	background_const_source_rect = { 0, 0, 384, 208};
	background_const_rect = new SDL_Rect(background_const_source_rect);

	return true;
}

update_status ModuleScene::PreUpdate()
{
	if (difftime(time(NULL), time_count->timer) >= 1) { time_count->Update(); }

	//if (time_count->current_time == 0){ time_count->Reset(150); }

	return UPDATE_CONTINUE;
}
update_status ModuleScene::Update()
{
	// PRINT SCORES
	app->fontManagerModule->Write_On_Screen("Player and ruben no swag", 8 * app->windowModule->scale, 209 * app->windowModule->scale, 8 * app->windowModule->scale);
	app->fontManagerModule->Write_On_Screen(900000, 8 * app->windowModule->scale, 230 * app->windowModule->scale, 8 * app->windowModule->scale);


	// PRINT BACKGROUND
	app->renderModule->Print(app->texturesModule->background_sprite, background_const_rect, &background_rect);

	// PRINT TIMER
	time_count->Print_Timer();

	// HARPOONS

	if (app->playerModule->player1->harpoon[0]->alive) { app->playerModule->player1->harpoon[0]->Print(); }
	if (app->playerModule->player1->harpoon[1]->alive) { app->playerModule->player1->harpoon[1]->Print(); }
	
	if (app->playerModule->player2 != NULL)
	{
		if (app->playerModule->player2->harpoon[0]->alive) { app->playerModule->player2->harpoon[0]->Print(); }
		if (app->playerModule->player2->harpoon[1]->alive) { app->playerModule->player2->harpoon[1]->Print(); }
	}

	// BULLETS



	// PRINT PLAYERS
	app->renderModule->Print(app->texturesModule->players_sprite, app->playerModule->player1->source_rect[app->playerModule->player1->source_index], &app->playerModule->player1->rect);
	
	if (app->playerModule->player2 != NULL)
	{
		app->renderModule->Print(app->texturesModule->players_sprite, app->playerModule->player2->source_rect[app->playerModule->player2->source_index], &app->playerModule->player2->rect);
	}
	

	// PRINT BALLS
	



	//app->renderModule->Print(app->texturesModule->, app->, &app->);



	return UPDATE_CONTINUE;
}


update_status ModuleScene::PostUpdate(){ return UPDATE_CONTINUE; }


bool ModuleScene::CleanUp(){ return true; }





void ModuleScene::reset_stage()
{
	time_count->Reset(stage_arrangement.time_limit);

	app->playerModule->player1->setPos(stage_arrangement.player_pos[0], stage_arrangement.player_pos[1]);
	if (app->playerModule->player2 != NULL){ app->playerModule->player1->setPos(stage_arrangement.player_pos[0], stage_arrangement.player_pos[1]); }

	if (!stage_arrangement.balloons.empty())
	{
		//for (int i = 0; i < )
	}


	
}



bool ModuleScene::load_stage(int stage)
{
	if (fopen_s(&level_file, "txt files/LevelArrangment.txt", "r") != 0){ return false; }

	current_stage = stage;

	char line[100];
	for (int i = 0; i < current_stage; i++)
	{
		fgets(line, 100, level_file);
		if (line == NULL){ return false; }
	}

	delete[] background_const_rect;
	background_const_source_rect.x = ((current_stage - 1) % 3) * 384;
	background_const_source_rect.y = ((current_stage - 1) / 3) * 208;
	background_const_rect = new SDL_Rect(background_const_source_rect);

	parser(line);
	fclose(level_file);

	reset_stage();

	return true;

}


void ModuleScene::parser(char *line)
{
	char *token = NULL;
	char *tmp_string = NULL;
	int max;
	Tri_Struct tmp_3;
	Quadra_Struct tmp_4;

	// time limit
	stage_arrangement.time_limit = atoi(strtok_s(line, "%", &token));
	
	// player's initial position
	tmp_string = strtok_s(NULL, "%", &token);
	stage_arrangement.player_pos[0] = atoi(strtok_s(NULL, ",", &tmp_string));
	stage_arrangement.player_pos[1] = atoi(strtok_s(NULL, ",", &tmp_string));
	stage_arrangement.player_pos[2] = atoi(strtok_s(NULL, ",", &tmp_string));
	stage_arrangement.player_pos[3] = atoi(tmp_string);
	
	// bricks
	tmp_string = strtok_s(NULL, "%", &token);
	stage_arrangement.bricks.clear();
	if (strcmp(tmp_string, "0") != 0)
	{
		max = atoi(strtok_s(NULL, ",", &tmp_string));
		for (int i = 0; i < max; i++)
		{
			tmp_3.x = atoi(strtok_s(NULL, ",", &tmp_string));
			tmp_3.y = atoi(strtok_s(NULL, ",", &tmp_string));
			tmp_3.type = atoi(tmp_string);

			stage_arrangement.bricks.push_back(tmp_3);
		}
	}

	// stairs
	tmp_string = strtok_s(NULL, "%", &token);
	stage_arrangement.stairs.clear();
	if (strcmp(tmp_string, "0") != 0)
	{
		max = atoi(strtok_s(NULL, ",", &tmp_string));
		for (int i = 0; i < max; i++)
		{
			tmp_3.x = atoi(strtok_s(NULL, ",", &tmp_string));
			tmp_3.y = atoi(strtok_s(NULL, ",", &tmp_string));
			tmp_3.type = atoi(tmp_string);

			stage_arrangement.stairs.push_back(tmp_3);
			}
	}

	// balloons
	tmp_string = strtok_s(NULL, "%", &token);
	stage_arrangement.balloons.clear();
	if (strcmp(tmp_string, "0") != 0)
	{
		max = atoi(strtok_s(NULL, ",", &tmp_string));
		for (int i = 0; i < max; i++)
		{
			tmp_4.x = atoi(strtok_s(NULL, ",", &tmp_string));
			tmp_4.y = atoi(strtok_s(NULL, ",", &tmp_string));
			tmp_4.type = atoi(strtok_s(NULL, ",", &tmp_string));
			tmp_4.aux = atoi(tmp_string);

			stage_arrangement.balloons.push_back(tmp_4);
		}
	}

	// enemies
	tmp_string = strtok_s(NULL, "%", &token);
	stage_arrangement.enemies.clear();
	if (strcmp(tmp_string, "0") != 0)
	{
		max = atoi(strtok_s(NULL, ",", &tmp_string));
		for (int i = 0; i < max; i++)
		{
			tmp_4.x = atoi(strtok_s(NULL, ",", &tmp_string));
			tmp_4.y = atoi(strtok_s(NULL, ",", &tmp_string));
			tmp_4.type = atoi(strtok_s(NULL, ",", &tmp_string));
			tmp_4.aux = atoi(tmp_string);

			stage_arrangement.enemies.push_back(tmp_4);
		}
	}
}
