#include "ModuleScene.h"

ModuleScene::ModuleScene(Application* app) : Module(app)
{
	time_count = NULL;

	ready_source_rect = NULL;
	game_over_source_rect = NULL;

	pause_pressed = false;
}

bool ModuleScene::Init()
{
	time_count = new Time_Count(app);

	game_state = READY;
	update_counter = 0;

	load_stage(app->stage);

	ready_rect = { 100, 100, 160 * app->windowModule->scale,  32 * app->windowModule->scale };
	game_over_rect = { 100, 100, 160 * app->windowModule->scale, 32 * app->windowModule->scale };

	background_rect = { 0, 0, SCREEN_WIDTH * app->windowModule->scale, (SCREEN_HEIGHT - 32) * app->windowModule->scale };

	return true;
}

update_status ModuleScene::PreUpdate()
{
	if (difftime(time(NULL), time_count->timer) >= 1 && game_state == PLAYING) { time_count->Update(); }

	if (app->inputModule->key[SDL_SCANCODE_5] == 1)
	{
		if (!insert_coin_pressed){ app->Add_Coin(); insert_coin_pressed = true; }
	}
	else { insert_coin_pressed = false; }


	if (app->inputModule->key[SDL_SCANCODE_9] == 1)
	{
		reset_stage();
	}

	return UPDATE_CONTINUE;
}
update_status ModuleScene::Update()
{
	Print_All_Objects();

	switch (game_state)
	{
	case PLAYING || PLAYER_KILLED:
		if (app->inputModule->key[SDL_SCANCODE_P] == 1)
		{
			game_state = PAUSED;
			update_counter = 0;
			pause_pressed = true;
		}

		break;

	case READY:
		if (update_counter < 30){ app->renderModule->Print(app->texturesModule->ready, ready_source_rect, &ready_rect); }
		else if (update_counter % 30 > 15){ app->renderModule->Print(app->texturesModule->ready, ready_source_rect, &ready_rect); }

		if (update_counter > 120){ game_state = PLAYING; update_counter = 0; }
		else { update_counter++; }

		break;

	case COUNTDOWN:
		// Handle countdown??
		break;

	case GAME_OVER:
		app->renderModule->Print(app->texturesModule->ready, game_over_source_rect, &game_over_rect);

		if (update_counter > 240){ return CHANGE_TO_TITLE; }
		else { update_counter++; }

		break;

	case PAUSED:
		app->renderModule->Print(app->texturesModule->ready, game_over_source_rect, &game_over_rect);

		if (app->inputModule->key[SDL_SCANCODE_P] == 1)
		{
			if (!pause_pressed){ game_state = PLAYING; }
		}
		else{ pause_pressed = false; }

		break;
	}

	return UPDATE_CONTINUE;
}


update_status ModuleScene::PostUpdate(){ return UPDATE_CONTINUE; }


bool ModuleScene::CleanUp(){ return true; }




void ModuleScene::Print_All_Objects()
{


	// PRINT SCORES
	app->fontManagerModule->Write_On_Screen("Player-1", 8 * app->windowModule->scale, 209 * app->windowModule->scale, 8 * app->windowModule->scale);
	app->fontManagerModule->Write_On_Screen(app->coins, 8 * app->windowModule->scale, 230 * app->windowModule->scale, 8 * app->windowModule->scale);


	// PRINT BACKGROUND
	app->renderModule->Print(app->texturesModule->background_sprite, background_source_rect, &background_rect);

	// PRINT TIMER
	time_count->Print_Timer();

	// PRINT STAIRS
	for (unsigned int i = 0; i < app->entityManagerModule->stairs->Count(); i++)
	{
		(*app->entityManagerModule->stairs->at(i))->Print();
	}

	// PRINT BRICKS
	for (unsigned int i = 0; i < app->entityManagerModule->bricks->Count(); i++)
	{
		(*app->entityManagerModule->bricks->at(i))->Print();
	}


	// PRINT HARPOONS

	if (app->playerModule->player1->harpoon[0]->alive) { app->playerModule->player1->harpoon[0]->Print(); }
	if (app->playerModule->player1->harpoon[1]->alive) { app->playerModule->player1->harpoon[1]->Print(); }

	if (app->playerModule->player2 != NULL)
	{
		if (app->playerModule->player2->harpoon[0]->alive) { app->playerModule->player2->harpoon[0]->Print(); }
		if (app->playerModule->player2->harpoon[1]->alive) { app->playerModule->player2->harpoon[1]->Print(); }
	}

	// PRINT BULLETS



	// PRINT PLAYERS
	app->renderModule->Print(app->texturesModule->players_sprite, app->playerModule->player1->source_rect[app->playerModule->player1->source_index], &app->playerModule->player1->rect);

	if (app->playerModule->player2 != NULL)
	{
		app->renderModule->Print(app->texturesModule->players_sprite, app->playerModule->player2->source_rect[app->playerModule->player2->source_index], &app->playerModule->player2->rect);
	}


	// PRINT BALLS

	for (unsigned int i = 0; i < app->entityManagerModule->balloons->Count(); i++)
	{
		(*app->entityManagerModule->balloons->at(i))->Print();
	}

	// PRINT PARTICLES
	for (unsigned int i = 0; i < app->entityManagerModule->particles->Count(); i++)
	{
		(*app->entityManagerModule->particles->at(i))->Print();
	}
}















void ModuleScene::reset_stage()
{
	game_state = READY;

	// TIME COUNT
	time_count->Reset(stage_arrangement.time_limit);

	// PLAYER POS
	app->playerModule->player1->Reset(stage_arrangement.player_pos[0], stage_arrangement.player_pos[1]);
	if (app->playerModule->player2 != NULL){ app->playerModule->player1->Reset(stage_arrangement.player_pos[0], stage_arrangement.player_pos[1]); }

	
	// BRICKS
	unsigned int i = 0;
	if (!stage_arrangement.bricks.empty())
	{
		while (i < app->entityManagerModule->bricks->Count() && i < stage_arrangement.bricks.size())
		{
			(*app->entityManagerModule->bricks->at(i))->Reset(
				stage_arrangement.bricks.at(i).x,
				stage_arrangement.bricks.at(i).y,
				stage_arrangement.bricks.at(i).type);
			i++;
		}

		app->entityManagerModule->bricks->Reduce_To(i);

		while (i < stage_arrangement.bricks.size())
		{
			app->entityManagerModule->bricks->push_back(new Brick(
				app,
				stage_arrangement.bricks.at(i).x,
				stage_arrangement.bricks.at(i).y,
				stage_arrangement.bricks.at(i).type));
			i++;
		}
	}
	

	// STAIRS
	i = 0;
	if (!stage_arrangement.stairs.empty())
	{
		while (i < app->entityManagerModule->stairs->Count() && i < stage_arrangement.stairs.size())
		{
			(*app->entityManagerModule->stairs->at(i))->Reset(
				stage_arrangement.stairs.at(i).x,
				stage_arrangement.stairs.at(i).y,
				stage_arrangement.stairs.at(i).type);
			i++;
		}
		while (i < stage_arrangement.stairs.size())
		{
			app->entityManagerModule->stairs->push_back(new Stair(
				app,
				stage_arrangement.stairs.at(i).x,
				stage_arrangement.stairs.at(i).y,
				stage_arrangement.stairs.at(i).type));
			i++;
		}
	}

	// BALLOONS
	i = 0;
	if (!stage_arrangement.balloons.empty())
	{
		while (i < app->entityManagerModule->balloons->Count() && i < stage_arrangement.balloons.size())
		{
			(*app->entityManagerModule->balloons->at(i))->Reset(
				stage_arrangement.balloons[i].x,
				stage_arrangement.balloons[i].y,
				stage_arrangement.balloons[i].type,
				stage_arrangement.balloons[i].aux1,
				stage_arrangement.balloons[i].aux2,
				stage_arrangement.balloons[i].aux3);
			i++;
		}
		while (i < stage_arrangement.balloons.size())
		{
			app->entityManagerModule->balloons->push_back(new Balloon(
				app,
				stage_arrangement.balloons.at(i).x,
				stage_arrangement.balloons.at(i).y,
				stage_arrangement.balloons.at(i).type,
				stage_arrangement.balloons.at(i).aux1,
				stage_arrangement.balloons.at(i).aux2,
				stage_arrangement.balloons.at(i).aux3));
			i++;
		}
		app->entityManagerModule->balloons->Reduce_To(i);
	}

	/*
	// ENEMIES
	i = 0;
	if (!stage_arrangement.enemies.empty())
	{
		while (i < app->entityManagerModule->enemies->Count() && i < stage_arrangement.enemies.Size())
		{
			(*app->entityManagerModule->enemies->At(i))->Reset(
			stage_arrangement.enemies.At(i).x,
			stage_arrangement.enemies.At(i).y,
			stage_arrangement.enemies.At(i).type,
			stage_arrangement.enemies.At(i).aux1,
			stage_arrangement.enemies.At(i).aux2,
			stage_arrangement.enemies.At(i).aux3);
			i++;
		}
		while (i < stage_arrangement.enemies.Size())
		{
			app->entityManagerModule->enemies->PushBack(new Enemy(
			app,
			stage_arrangement.enemies.At(i).x,
			stage_arrangement.enemies.At(i).y,
			stage_arrangement.enemies.At(i).type,
			stage_arrangement.enemies.At(i).aux1,
			stage_arrangement.enemies.At(i).aux2,
			stage_arrangement.enemies.At(i).aux3));
			i++;
		}
	}*/
}



bool ModuleScene::load_stage(int stage)
{
	if (fopen_s(&level_file, "txt files/LevelArrangment.txt", "r") != 0){ return false; }

	current_stage = stage;

	char line[100];
	for (unsigned int i = 0; i < current_stage; i++)
	{
		fgets(line, 300, level_file);
		if (line == NULL){ return false; }
	}

	parser(line);
	fclose(level_file);

	if (background_source_rect != NULL){ delete background_source_rect; background_source_rect = NULL; }
	background_source_rect = new SDL_Rect({ ((current_stage - 1) % 3) * 384, ((current_stage - 1) / 3) * 208, 384, 208 });

	reset_stage();

	return true;

}


void ModuleScene::parser(char *line)
{
	char *token = NULL;
	char *tmp_string = NULL;
	int max;
	Tri_Struct tmp_3;
	Hexa_Struct tmp_6;

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
		max = atoi(strtok_s(NULL, ";", &tmp_string));
		for (int i = 0; i < max; i++)
		{
			tmp_3.x = atoi(strtok_s(NULL, ",", &tmp_string));
			tmp_3.y = atoi(strtok_s(NULL, ",", &tmp_string));
			tmp_3.type = atoi(strtok_s(NULL, ";", &tmp_string));

			stage_arrangement.bricks.push_back(tmp_3);
		}
	}

	// stairs
	tmp_string = strtok_s(NULL, "%", &token);
	stage_arrangement.stairs.clear();
	if (strcmp(tmp_string, "0") != 0)
	{
		max = atoi(strtok_s(NULL, ";", &tmp_string));
		for (int i = 0; i < max; i++)
		{
			tmp_3.x = atoi(strtok_s(NULL, ",", &tmp_string));
			tmp_3.y = atoi(strtok_s(NULL, ",", &tmp_string));
			tmp_3.type = atoi(strtok_s(NULL, ";", &tmp_string));

			stage_arrangement.stairs.push_back(tmp_3);
			}
	}

	// balloons
	tmp_string = strtok_s(NULL, "%", &token);
	stage_arrangement.balloons.clear();
	if (strcmp(tmp_string, "0") != 0)
	{
		max = atoi(strtok_s(NULL, ";", &tmp_string));
		for (int i = 0; i < max; i++)
		{
			tmp_6.x = atoi(strtok_s(NULL, ",", &tmp_string));
			tmp_6.y = atoi(strtok_s(NULL, ",", &tmp_string));
			tmp_6.type = atoi(strtok_s(NULL, ",", &tmp_string));
			tmp_6.aux1 = atoi(strtok_s(NULL, ",", &tmp_string));
			tmp_6.aux2 = atoi(strtok_s(NULL, ",", &tmp_string));
			tmp_6.aux3 = atoi(strtok_s(NULL, ";", &tmp_string));

			stage_arrangement.balloons.push_back(tmp_6);
		}
	}

	// enemies
	tmp_string = strtok_s(NULL, "%", &token);
	stage_arrangement.enemies.clear();
	if (strcmp(tmp_string, "0") != 0)
	{
		max = atoi(strtok_s(NULL, ";", &tmp_string));
		for (int i = 0; i < max; i++)
		{
			tmp_6.x = atoi(strtok_s(NULL, ",", &tmp_string));
			tmp_6.y = atoi(strtok_s(NULL, ",", &tmp_string));
			tmp_6.type = atoi(strtok_s(NULL, ",", &tmp_string));
			tmp_6.aux1 = atoi(strtok_s(NULL, ",", &tmp_string));
			tmp_6.aux2 = atoi(strtok_s(NULL, ",", &tmp_string));
			tmp_6.aux3 = atoi(strtok_s(NULL, ";", &tmp_string));

			stage_arrangement.enemies.push_back(tmp_6);
		}
	}
}
