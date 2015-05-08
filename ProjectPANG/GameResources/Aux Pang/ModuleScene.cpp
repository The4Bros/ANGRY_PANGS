#include "ModuleScene.h"

ModuleScene::ModuleScene(Application* app) : Module(app),
time_count(NULL),
pause_pressed(false),
stage_cleared(false)
{

}

bool ModuleScene::Init()
{
	if (time_count == NULL){ time_count = new Time_Count(app); }
	time_count->Reset(100);

	game_state = READY;
	update_counter = 0;

	load_stage(app->stage);

	ready_rect = { 100, 100, 160 * app->windowModule->scale,  32 * app->windowModule->scale };
	game_over_rect = { 100, 100, 160 * app->windowModule->scale, 32 * app->windowModule->scale };

	background_rect = { 0, 0, SCREEN_WIDTH * app->windowModule->scale, (SCREEN_HEIGHT - 32) * app->windowModule->scale };

	app->audioModule->PlayMusic((app->stage - 1) / 3);

	return true;
}

update_status ModuleScene::PreUpdate()
{
	if (app->inputModule->key[SDL_SCANCODE_5] == 1)
	{
		if (!insert_coin_pressed){ app->Add_Coin(); insert_coin_pressed = true; }
	}
	else { insert_coin_pressed = false; }

	// STAGE CHEAT - 9: RESET STAGE
	if (app->inputModule->key[SDL_SCANCODE_9] == 1){ reset_stage(); }

	return UPDATE_CONTINUE;
}
update_status ModuleScene::Update()
{
	// PRINT ALL OBJECTS ON SCREEN
	Print_All_Objects();

	switch (game_state)
	{
	case PLAYING:
		// PAUSE MANAGED
		if (app->inputModule->key[SDL_SCANCODE_P] == 1)
		{
			if (!pause_pressed){ Pause_Scene(); }
		}
		else{ pause_pressed = false; }

		// STAGE CLEARED MANAGED
		if (stage_cleared)
		{
			if (update_counter > 180)
			{
				app->stage++;
				stage_cleared = false;
				return CHANGE_TO_STAGE_END;
			}
			update_counter++;
		}
		else
		{
			//TIMER MANAGED
			if (difftime(time(NULL), time_count->timer) >= 1 && game_state == PLAYING) { time_count->Update(); }

			// CHECK IF STAGE CLEARED
			if (app->entityManagerModule->balloons.empty())
			{
				stage_cleared = true;
				update_counter = 0;
			}
		}
		break;

	case PLAYER_KILLED:
		if (update_counter > 300)
		{
			if (app->playerModule->player1->lives > 0)
			{
				app->playerModule->player1->lives--;
				update_counter = 0;
				reset_stage();
			}
			else{ return CHANGE_TO_TITLE; }
		}
		else { update_counter++; }
		break;

	case READY:
		if (update_counter < 30){ app->renderModule->Print(app->texturesModule->ready, &ready_source_rect, &ready_rect); }
		else if (update_counter % 30 > 15){ app->renderModule->Print(app->texturesModule->ready, &ready_source_rect, &ready_rect); }

		if (update_counter > 120){ game_state = PLAYING; update_counter = 0; }
		else { update_counter++; }

		break;

	case COUNTDOWN:
		// Handle countdown??
		break;

	case GAME_OVER:
		app->renderModule->Print(app->texturesModule->ready, &game_over_source_rect, &game_over_rect);

		if (update_counter > 240){ return CHANGE_TO_TITLE; }
		else { update_counter++; }

		break;

	case PAUSED:
		app->renderModule->Print(app->texturesModule->ready, &game_over_source_rect, &game_over_rect);

		// darken screen
		app->renderModule->Fade_Screen();

		if (app->inputModule->key[SDL_SCANCODE_P] == 1)
		{
			if (!pause_pressed)
			{
				if (!Resume_Scene()){ return UPDATE_ERROR; }
			}
		}
		else{ pause_pressed = false; }

		break;
	}

	return UPDATE_CONTINUE;
}

bool ModuleScene::CleanUp()
{
	delete time_count;

	return true;
}

void ModuleScene::Pause_Scene()
{
	app->audioModule->PauseMusic();

	game_state = PAUSED;
	pause_pressed = true;
}

bool ModuleScene::Resume_Scene()
{
	app->audioModule->ResumeMusic();

	game_state = PLAYING;
	pause_pressed = true;

	return true;
}






void ModuleScene::Print_All_Objects()
{
	// PRINT TEXT & SCORES
	app->fontManagerModule->Write_On_Screen("Player-1",                        17 * app->windowModule->scale, 208 * app->windowModule->scale, 8 * app->windowModule->scale, WHITE);
	app->fontManagerModule->Write_On_Screen("Player-2",                       270 * app->windowModule->scale, 208 * app->windowModule->scale, 8 * app->windowModule->scale, WHITE);
	app->fontManagerModule->Write_On_Screen("lives:",                          16 * app->windowModule->scale, 222 * app->windowModule->scale, 8 * app->windowModule->scale, WHITE);
	app->fontManagerModule->Write_On_Screen("0",                              104 * app->windowModule->scale, 214 * app->windowModule->scale, 8 * app->windowModule->scale, WHITE);
	app->fontManagerModule->Write_On_Screen(app->playerModule->player1->lives, 64 * app->windowModule->scale, 230 * app->windowModule->scale, 8 * app->windowModule->scale, WHITE);
	app->fontManagerModule->Write_On_Screen("mt.fuji",                        160 * app->windowModule->scale, 208 * app->windowModule->scale, 8 * app->windowModule->scale, WHITE);
	app->fontManagerModule->Write_On_Screen(app->stage,                       160 * app->windowModule->scale, 220 * app->windowModule->scale, 8 * app->windowModule->scale, WHITE);
	app->fontManagerModule->Write_On_Screen("~",                              167 * app->windowModule->scale, 220 * app->windowModule->scale, 8 * app->windowModule->scale, WHITE);
	app->fontManagerModule->Write_On_Screen(app->stage,                       174 * app->windowModule->scale, 220 * app->windowModule->scale, 8 * app->windowModule->scale, WHITE);
	app->fontManagerModule->Write_On_Screen("stage",                          185 * app->windowModule->scale, 220 * app->windowModule->scale, 8 * app->windowModule->scale, WHITE);
	app->fontManagerModule->Write_On_Screen("HI:",                            160 * app->windowModule->scale, 230 * app->windowModule->scale, 8 * app->windowModule->scale, WHITE);
	app->fontManagerModule->Write_On_Screen(10000,                            185 * app->windowModule->scale, 230 * app->windowModule->scale, 8 * app->windowModule->scale, WHITE);
	app->fontManagerModule->Write_On_Screen(app->coins,                       360 * app->windowModule->scale, 230 * app->windowModule->scale, 8 * app->windowModule->scale, WHITE);


	// PRINT BACKGROUND
	app->renderModule->Print(app->texturesModule->background_sprite, &background_source_rect, &background_rect);

	// PRINT TIMER
	time_count->Print_Timer();

	// PRINT STAIRS
	DoubleNode<Stair*>* tmp_stair = app->entityManagerModule->stairs.getStart();
	for (; tmp_stair != NULL; tmp_stair = tmp_stair->next)
	{
		tmp_stair->data->Print();
	}

	// PRINT BRICKS
	DoubleNode<Brick*>* tmp_brick = app->entityManagerModule->bricks.getStart();
	for (; tmp_brick != NULL; tmp_brick = tmp_brick->next)
	{
		tmp_brick->data->Print();
	}


	// PRINT HARPOONS

	if (app->playerModule->player1->harpoon1->alive) { app->playerModule->player1->harpoon1->Print(); }
	if (app->playerModule->player1->harpoon2->alive) { app->playerModule->player1->harpoon2->Print(); }

	if (app->playerModule->player2 != NULL)
	{
		if (app->playerModule->player2->harpoon1->alive) { app->playerModule->player2->harpoon1->Print(); }
		if (app->playerModule->player2->harpoon2->alive) { app->playerModule->player2->harpoon2->Print(); }
	}

	// PRINT BULLETS



	// PRINT PLAYERS
	app->renderModule->Print(app->texturesModule->players_sprite, &app->playerModule->player1->source_rect[app->playerModule->player1->source_index], &app->playerModule->player1->rect);

	if (app->playerModule->player2 != NULL)
	{
		app->renderModule->Print(app->texturesModule->players_sprite, &app->playerModule->player2->source_rect[app->playerModule->player2->source_index], &app->playerModule->player2->rect);
	}


	// PRINT BALLOONS
	DoubleNode<Balloon*>* tmp_balloon = app->entityManagerModule->balloons.getStart();
	for (; tmp_balloon != NULL; tmp_balloon = tmp_balloon->next)
	{
		tmp_balloon->data->Print();
	}

	// PRINT PARTICLES
	DoubleNode<Particles*>* tmp_particle = app->entityManagerModule->particles.getStart();
	for (; tmp_particle != NULL; tmp_particle = tmp_particle->next)
	{
		tmp_particle->data->Print();
	}
}


void ModuleScene::reset_stage()
{
	game_state = READY;

	// PARTICLES
	app->entityManagerModule->particles.clear();

	// TIME COUNT
	time_count->Reset(stage_arrangement.time_limit);

	// PLAYER POS
	app->playerModule->player1->Reset(stage_arrangement.player_pos[0], stage_arrangement.player_pos[1]);
	if (app->playerModule->player2 != NULL){ app->playerModule->player1->Reset(stage_arrangement.player_pos[0], stage_arrangement.player_pos[1]); }

	
	// BRICKS____________________________________________________________________________________________________________________________
	app->entityManagerModule->bricks.clear();
	for (unsigned int i = 0; i < stage_arrangement.bricks.Count(); i++)
	{
		app->entityManagerModule->bricks.push(
			new Brick(app,
			stage_arrangement.bricks.at(i)->x,
			stage_arrangement.bricks.at(i)->y,
			stage_arrangement.bricks.at(i)->type));
	}

	// STAIRS____________________________________________________________________________________________________________________________
	app->entityManagerModule->stairs.clear();
	for (unsigned int i = 0; i < stage_arrangement.stairs.Count(); i++)
	{
		app->entityManagerModule->stairs.push(
			new Stair(app,
			(*stage_arrangement.stairs.at(i)).x,
			(*stage_arrangement.stairs.at(i)).y,
			(*stage_arrangement.stairs.at(i)).type));
	}

	// BALLOONS____________________________________________________________________________________________________________________________
	app->entityManagerModule->balloons.clear();
	for (unsigned int i = 0; i < stage_arrangement.balloons.Count(); i++)
	{
		app->entityManagerModule->balloons.push(
			new Balloon(app,
			(*stage_arrangement.balloons.at(i)).x,
			(*stage_arrangement.balloons.at(i)).y,
			(*stage_arrangement.balloons.at(i)).type,
			(*stage_arrangement.balloons.at(i)).aux1));
	}

	/*
	// ENEMIES____________________________________________________________________________________________________________________________
	app->entityManagerModule->balloons.clear();
	for (unsigned int i = 0; i < stage_arrangement.enemies.Count(); i++)
	{
		app->entityManagerModule->enemies->push(
			new Enemy(app,
			(*stage_arrangement.enemies.at(i)).x,
			(*stage_arrangement.enemies.at(i)).y,
			(*stage_arrangement.enemies.at(i)).type
			(*stage_arrangement.enemies.at(i)).aux1,
			(*stage_arrangement.enemies.at(i)).aux2,
			(*stage_arrangement.enemies.at(i)).aux3));
	}
	*/

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

	background_source_rect = { ((current_stage - 1) % 3) * 384, ((current_stage - 1) / 3) * 208, 384, 208 };

	reset_stage();

	return true;

}


void ModuleScene::parser(char *line)
{
	char *main_token = NULL;
	char *tmp_string = NULL;
	int max;
	Hexa_Struct tmp_struct;
	tmp_struct.Reset();

	// time limit
	stage_arrangement.time_limit = atoi(strtok_s(line, "%", &main_token));
	
	// player's initial position
	tmp_string = strtok_s(NULL, "%", &main_token);
	stage_arrangement.player_pos[0] = atoi(strtok_s(NULL, ",", &tmp_string));
	stage_arrangement.player_pos[1] = atoi(strtok_s(NULL, ",", &tmp_string));
	stage_arrangement.player_pos[2] = atoi(strtok_s(NULL, ",", &tmp_string));
	stage_arrangement.player_pos[3] = atoi(tmp_string);
	
	// bricks
	tmp_string = strtok_s(NULL, "%", &main_token);
	stage_arrangement.bricks.clear();
	if (strcmp(tmp_string, "0") != 0)
	{
		max = atoi(strtok_s(NULL, ";", &tmp_string));
		for (int i = 0; i < max; i++)
		{
			tmp_struct.x = atoi(strtok_s(NULL, ",", &tmp_string));
			tmp_struct.y = atoi(strtok_s(NULL, ",", &tmp_string));
			tmp_struct.type = atoi(strtok_s(NULL, ";", &tmp_string));

			stage_arrangement.bricks.push_back(tmp_struct);
		}
	}

	// stairs
	tmp_string = strtok_s(NULL, "%", &main_token);
	stage_arrangement.stairs.clear();
	if (strcmp(tmp_string, "0") != 0)
	{
		max = atoi(strtok_s(NULL, ";", &tmp_string));
		for (int i = 0; i < max; i++)
		{
			tmp_struct.x = atoi(strtok_s(NULL, ",", &tmp_string));
			tmp_struct.y = atoi(strtok_s(NULL, ",", &tmp_string));
			tmp_struct.type = atoi(strtok_s(NULL, ";", &tmp_string));

			stage_arrangement.stairs.push_back(tmp_struct);
			}
	}

	// balloons
	tmp_string = strtok_s(NULL, "%", &main_token);
	stage_arrangement.balloons.clear();
	if (strcmp(tmp_string, "0") != 0)
	{
		max = atoi(strtok_s(NULL, ";", &tmp_string));
		for (int i = 0; i < max; i++)
		{
			tmp_struct.x = atoi(strtok_s(NULL, ",", &tmp_string));
			tmp_struct.y = atoi(strtok_s(NULL, ",", &tmp_string));
			tmp_struct.type = atoi(strtok_s(NULL, ",", &tmp_string));
			tmp_struct.aux1 = atoi(strtok_s(NULL, ";", &tmp_string));

			stage_arrangement.balloons.push_back(tmp_struct);
		}
	}

	// enemies
	tmp_string = strtok_s(NULL, "%", &main_token);
	stage_arrangement.enemies.clear();
	if (strcmp(tmp_string, "0") != 0)
	{
		max = atoi(strtok_s(NULL, ";", &tmp_string));
		for (int i = 0; i < max; i++)
		{
			tmp_struct.x = atoi(strtok_s(NULL, ",", &tmp_string));
			tmp_struct.y = atoi(strtok_s(NULL, ",", &tmp_string));
			tmp_struct.type = atoi(strtok_s(NULL, ",", &tmp_string));
			tmp_struct.aux1 = atoi(strtok_s(NULL, ";", &tmp_string));

			stage_arrangement.enemies.push_back(tmp_struct);
		}
	}
}