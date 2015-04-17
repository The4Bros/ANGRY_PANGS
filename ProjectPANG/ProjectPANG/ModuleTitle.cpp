#include "ModuleTitle.h"

ModuleTitle::ModuleTitle(Application* app) : Module(app){}
bool ModuleTitle::Init()
{	
	app->current_time = 0;
	ticks = 0;
	dir = 1;
	rect = { 0, 0, 384 * app->windowModule->scale, 240 * app->windowModule->scale };
	insert_coin_rect = { 100 * app->windowModule->scale, 200 * app->windowModule->scale, 177 * app->windowModule->scale, 15 * app->windowModule->scale };

	for (int i = 0; i < 4; i++){ source_rect[i] = new SDL_Rect({ i * 384, 0, 384, 240 }); }
	source_rect[4] = new SDL_Rect({ 1536, 0, 176, 15 });

	balloon_rects[0] = { 384*app->windowModule->scale, 0, 48 * app->windowModule->scale, 40 * app->windowModule->scale };
	balloon_rects[1] = { 0, 0, 48 * app->windowModule->scale, 40 * app->windowModule->scale };
	balloon_rects[2] = { 384*app->windowModule->scale, 0, 48 * app->windowModule->scale, 40 * app->windowModule->scale };
	balloon_rects[3] = { 0, 0, 48 * app->windowModule->scale, 40 * app->windowModule->scale };
	balloon_source_rect = new SDL_Rect({ 0, 0, 48, 40 });

	insert_coin_pressed = false;

	return true;
}

update_status ModuleTitle::PreUpdate()
{
	return UPDATE_CONTINUE;
}
update_status ModuleTitle::Update()
{	
	//Print inital screens
	if (app->current_time < 1){ app->renderModule->Print(app->texturesModule->title_sprite, source_rect[0], &rect); }
	else if (app->current_time < 2){ app->renderModule->Print(app->texturesModule->title_sprite, source_rect[1], &rect); }
	else if (app->current_time < 4){ app->renderModule->Print(app->texturesModule->title_sprite, source_rect[2], &rect); }
	else if (app->current_time > 12){ return CHANGE_TO_TUTORIAL; }
	else if (app->coins == 0)
	{
		app->renderModule->Print(app->texturesModule->title_sprite, source_rect[3], &rect);
		
		//begginning animation:
		if (app->current_time < 5)
		{
			Update_Balloons();
			
		}
		// insert coin 
		if (app->current_time % 2 == 1) { app->renderModule->Print(app->texturesModule->title_sprite, source_rect[4], &insert_coin_rect); }
	}
	else
	{
		app->fontManagerModule->Write_On_Screen("Push start button", 140 * app->windowModule->scale, 100 * app->windowModule->scale, 8 * app->windowModule->scale);
		app->fontManagerModule->Write_On_Screen("1 or 2 players", 150 * app->windowModule->scale, 120 * app->windowModule->scale, 8 * app->windowModule->scale);
		app->fontManagerModule->Write_On_Screen("Credits:", 250 * app->windowModule->scale, 220 * app->windowModule->scale, 8 * app->windowModule->scale);
		app->fontManagerModule->Write_On_Screen(app->coins, 320 * app->windowModule->scale, 220 * app->windowModule->scale, 8 * app->windowModule->scale);

		if (app->inputModule->key[SDL_SCANCODE_1] == 1)
		{
			return CHANGE_TO_PLAY;
		}
	}
	
	if (app->current_time > 5)
	{
		if (app->inputModule->key[SDL_SCANCODE_5] == 1)
		{
			if (!insert_coin_pressed){ app->Add_Coin(); insert_coin_pressed = true; }
		}
		else { insert_coin_pressed = false; }
	}

	return UPDATE_CONTINUE;
	
}
	
update_status ModuleTitle::PostUpdate(){ return UPDATE_CONTINUE; }

bool ModuleTitle::CleanUp(){ return true; }


void ModuleTitle::Update_Balloons()//Balls title animation 
{
	
	ticks++;
	balloon_rects[0].x -= 2*app->windowModule->scale;
	//balloon_rects[1].x += app->windowModule->scale;
	//balloon_rects[2].x -= app->windowModule->scale;
	//balloon_rects[3].x += app->windowModule->scale;

	balloon_rects[0].y += (app->windowModule->scale) + (dir*0.09*(ticks /10)*(ticks / 10));
	//balloon_rects[1].y += app->windowModule->scale;
	//balloon_rects[2].y += app->windowModule->scale;
	//balloon_rects[3].y += app->windowModule->scale;
	if (balloon_rects[0].y > 208 * app->windowModule->scale){ dir = -1; }

	for (int i = 0; i < 4; i++){ app->renderModule->Print(app->texturesModule->balls_sprite, balloon_source_rect, &balloon_rects[i]);  }
}