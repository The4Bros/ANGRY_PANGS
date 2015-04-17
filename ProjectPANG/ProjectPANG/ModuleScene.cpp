#include "ModuleScene.h"

ModuleScene::ModuleScene(Application* app) : Module(app)
{
	time_count = NULL;
}

bool ModuleScene::Init()
{
	time_count = new Time_Count(app);
	load_stage(1);

	background_rect = { 0, 0, SCREEN_WIDTH * app->windowModule->scale, (SCREEN_HEIGHT - 32) * app->windowModule->scale };
	background_const_source_rect = { 0, 0, 384, 208};
	background_const_rect = new SDL_Rect(background_const_source_rect);

	return true;
}

update_status ModuleScene::PreUpdate()
{
	if (difftime(time(NULL), time_count->timer) >= 1) { time_count->Update(); }

	/*
	
	change print 
	
	*/



	return UPDATE_CONTINUE;
}
update_status ModuleScene::Update()
{
	// PRINT SCORES
	app->fontManagerModule->Write_On_Screen("Player-1", 8 * app->windowModule->scale, 209 * app->windowModule->scale, 8 * app->windowModule->scale);
	//app->fontManagerModule->Write_On_Screen(900000, 8 * app->windowModule->scale, 230 * app->windowModule->scale, 8 * app->windowModule->scale);
	app->fontManagerModule->Write_On_Screen(app->titleModule->coin, 8 * app->windowModule->scale, 230 * app->windowModule->scale, 8 * app->windowModule->scale);

	// PRINT BACKGROUND
	app->renderModule->Print(app->texturesModule->background_sprite, background_const_rect, &background_rect);

	// PRINT TIMER
	time_count->Print_Timer();

	// STAIRS
	if (!app->entityManagerModule->stairs->empty())
	{
		Stair* tmp_stair = NULL;
		for (unsigned int i = 0; i < app->entityManagerModule->stairs->Count(); i++)
		{
			tmp_stair = *app->entityManagerModule->stairs->at(i);
			tmp_stair->Print();
		}
	}

	// BRICKS
	if (!app->entityManagerModule->bricks->empty())
	{
		Brick* tmp_brick = NULL;
		for (unsigned int i = 0; i < app->entityManagerModule->bricks->Count(); i++)
		{
			tmp_brick = *app->entityManagerModule->bricks->at(i);
			tmp_brick->Print();
		}
	}


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
	
	app->renderModule->Print(app->texturesModule->balls_sprite, app->entityManagerModule->source_balloon_rect[0], &app->entityManagerModule->balloon_sample->rect);
	
	if (!app->entityManagerModule->balloons->empty())
	{
		Balloon* tmp_balloon = NULL;
		for (unsigned int i = 0; i < app->entityManagerModule->balloons->Count(); i++)
		{
			tmp_balloon = *app->entityManagerModule->balloons->at(i);
			tmp_balloon->Print();
		}
	}


	//app->renderModule->Print(app->texturesModule->, app->, &app->);



	return UPDATE_CONTINUE;
}


update_status ModuleScene::PostUpdate(){ return UPDATE_CONTINUE; }


bool ModuleScene::CleanUp(){ return true; }





void ModuleScene::reset_stage()
{
	// TIME COUNT
	time_count->Reset(stage_arrangement.time_limit);

	// PLAYER POS
	app->playerModule->player1->setPos(stage_arrangement.player_pos[0], stage_arrangement.player_pos[1]);
	if (app->playerModule->player2 != NULL){ app->playerModule->player1->setPos(stage_arrangement.player_pos[0], stage_arrangement.player_pos[1]); }

	
	// BRICKS
	unsigned int i = 0;
	if (!stage_arrangement.bricks.empty())
	{
		Brick* bricks_tmp = NULL;
		while (i < app->entityManagerModule->bricks->Count() && i < stage_arrangement.bricks.size())
		{
			bricks_tmp = *app->entityManagerModule->bricks->at(i);
			bricks_tmp->Reset(
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
		Stair* stair_tmp = NULL;
		while (i < app->entityManagerModule->stairs->Count() && i < stage_arrangement.stairs.size())
		{
			stair_tmp = *app->entityManagerModule->stairs->at(i);
			stair_tmp->Reset(
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
		Balloon* balloon_tmp = NULL;
		while (i < app->entityManagerModule->balloons->Count() && i < stage_arrangement.balloons.size())
		{
			balloon_tmp = *app->entityManagerModule->balloons->at(i);
			balloon_tmp->Reset(
				stage_arrangement.balloons[i].x,
				stage_arrangement.balloons[i].y,
				stage_arrangement.balloons[i].type,
				stage_arrangement.balloons[i].aux);
			i++;
		}
		while (i < stage_arrangement.balloons.size())
		{
			app->entityManagerModule->balloons->push_back(new Balloon(
				app,
				stage_arrangement.balloons.at(i).x,
				stage_arrangement.balloons.at(i).y,
				stage_arrangement.balloons.at(i).type,
				stage_arrangement.balloons.at(i).aux));
			i++;
		}
		app->entityManagerModule->balloons->Reduce_To(i);
	}

	/*
	// ENEMIES
	i = 0;
	if (!stage_arrangement.enemies.empty())
	{
		Enemy* enemy_tmp = NULL;
		while (i < app->entityManagerModule->enemies->Count() && i < stage_arrangement.enemies.Size())
		{
			enemy_tmp = *app->entityManagerModule->enemies->At(i);
			enemy_tmp->Reset(
			stage_arrangement.enemies.At(i).x,
			stage_arrangement.enemies.At(i).y,
			stage_arrangement.enemies.At(i).type,
			stage_arrangement.enemies.At(i).aux);
			i++;
		}
		while (i < stage_arrangement.enemies.Size())
		{
			app->entityManagerModule->enemies->PushBack(new Enemy(
			app,
			stage_arrangement.enemies.At(i).x,
			stage_arrangement.enemies.At(i).y,
			stage_arrangement.enemies.At(i).type,
			stage_arrangement.enemies.At(i).aux));
			i++;
		}
	}*/
}



bool ModuleScene::load_stage(int stage)
{
	if (fopen_s(&level_file, "txt files/LevelArrangment.txt", "r") != 0){ return false; }

	current_stage = stage;

	char line[100];
	for (int i = 0; i < current_stage; i++)
	{
		fgets(line, 300, level_file);
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
			tmp_4.x = atoi(strtok_s(NULL, ",", &tmp_string));
			tmp_4.y = atoi(strtok_s(NULL, ",", &tmp_string));
			tmp_4.type = atoi(strtok_s(NULL, ",", &tmp_string));
			tmp_4.aux = atoi(strtok_s(NULL, ";", &tmp_string));

			stage_arrangement.balloons.push_back(tmp_4);
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
			tmp_4.x = atoi(strtok_s(NULL, ",", &tmp_string));
			tmp_4.y = atoi(strtok_s(NULL, ",", &tmp_string));
			tmp_4.type = atoi(strtok_s(NULL, ",", &tmp_string));
			tmp_4.aux = atoi(strtok_s(NULL, ";", &tmp_string));

			stage_arrangement.enemies.push_back(tmp_4);
		}
	}
}
