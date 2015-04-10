#include "ModuleScene.h"

ModuleScene::ModuleScene(Application* app) : Module(app)
{
	
	time_count = NULL;
	
}

bool ModuleScene::Init()
{
	time_count = new Time_Count(app);
	//level_file = fopen("dadesED2014-100.txt", "r");
	//if (level_file == NULL){ LOG("ERROR LOADING FILE"); return false; }

	

	current_stage = 1;
	load_stage(current_stage);

	background_rect = { 0, 0, SCREEN_WIDTH * app->windowModule->scale, (SCREEN_HEIGHT - 32) * app->windowModule->scale };
	background_const_source_rect = { 0, 0, 384, 208};
	background_const_rect = new SDL_Rect(background_const_source_rect);

	return true;
}

update_status ModuleScene::PreUpdate()
{
	if (difftime(time(NULL), time_count->timer) >= 1){ time_count->Update(); }

	//if (time_count->current_time == 0){ time_count->Reset(150); }

	return UPDATE_CONTINUE;
}
update_status ModuleScene::Update()
{
	// PRINT BACKGROUND
	app->fontManagerModule->Write_On_Screen("P", 8 * app->windowModule->scale, 208 * app->windowModule->scale, 7 * app->windowModule->scale);
	app->fontManagerModule->Write_On_Screen("L", 16 * app->windowModule->scale, 208 * app->windowModule->scale, 7 * app->windowModule->scale);
	app->fontManagerModule->Write_On_Screen("A", 24 * app->windowModule->scale, 208 * app->windowModule->scale, 7 * app->windowModule->scale);
	app->fontManagerModule->Write_On_Screen("Y", 32 * app->windowModule->scale, 208 * app->windowModule->scale, 7 * app->windowModule->scale);
	app->fontManagerModule->Write_On_Screen("E", 40 * app->windowModule->scale, 208 * app->windowModule->scale, 7 * app->windowModule->scale);
	app->fontManagerModule->Write_On_Screen("R", 48 * app->windowModule->scale, 208 * app->windowModule->scale, 7 * app->windowModule->scale);


	app->renderModule->Print(app->texturesModule->background_sprite, background_const_rect, &background_rect);

	// PRINT TIMER
	time_count->Print_Timer();

	// HARPOONS

	if (app->playerModule->player1->harpoon[0]->alive) { app->renderModule->Print(app->texturesModule->harpoons_sprite, app->playerModule->player1->harpoon[0]->const_rect, &app->playerModule->player1->harpoon[0]->rect); }
	if (app->playerModule->player1->harpoon[1]->alive) { app->renderModule->Print(app->texturesModule->harpoons_sprite, app->playerModule->player1->harpoon[1]->const_rect, &app->playerModule->player1->harpoon[1]->rect); }
	
	if (app->playerModule->player2 != NULL)
	{
		if (app->playerModule->player2->harpoon[0]->alive) { app->renderModule->Print(app->texturesModule->harpoons_sprite, app->playerModule->player2->harpoon[0]->const_rect, &app->playerModule->player2->harpoon[0]->rect); }
		if (app->playerModule->player2->harpoon[1]->alive) { app->renderModule->Print(app->texturesModule->harpoons_sprite, app->playerModule->player2->harpoon[1]->const_rect, &app->playerModule->player2->harpoon[1]->rect); }
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





	time_count->Reset(150);
}



void ModuleScene::load_stage(int stage)
{
	/*
	User parser(char *line){
		User user; char *it;
		user.init();
		user.setUid(strtok(line, "|"));
		user.setCountry(strtok(NULL, "|"));
		user.setMostListenedArtist(strtok(NULL, "&") + 1);
		user.setTimesListened(strtok(NULL, "&"));
		user.setMostRelevance(strtok(NULL, "|") + 2);			//num_type temp = ::strtod(str_num.c_str(), 0);  from <cstdlib>
		user.addArtist(strtok(NULL, "%") + 1);
		user.addRelevance(strtok(NULL, "&") + 1);
		while (true){
			it = strtok(NULL, "%");
			if (it == NULL){ break; }
			user.addArtist(it + 2);
			user.addRelevance(strtok(NULL, "&") + 1);
		}
		return user;
	}
	
	
		else{
			char line[100];
			for (int i = 0; fgets(line, 2820, fichero) != NULL; i++){ userList[i] = parser(line); }
			fclose(fichero);
			//printAllUsers(userList);
			Stack stack;
			stack.initialize();
			for (int i2 = 0; i2 <= i; i2++){
				stack
			}



			*/
	time_count->Reset(150);

}