#include "ModuleTitle.h"

ModuleTitle::ModuleTitle(Application* app) : Module(app){}

bool ModuleTitle::Init()
{
	
	//app->current_time = 0;
	return true;
}

update_status ModuleTitle::PreUpdate()
{
	
	return UPDATE_CONTINUE;
}
update_status ModuleTitle::Update()
{	
	int resto = app->current_time % 2;
	//Print inital screens
	if (app->current_time < 10){
		SDL_Rect tmp = { 0, 0, 384 * app->windowModule->scale, 240 * app->windowModule->scale };
		SDL_Rect tmp2 = { 0, 0, 384 , 240};
		app->renderModule->Print(app->texturesModule->title_sprite, &tmp2, &tmp);
	}
	else{
		if (app->current_time < 20){
			SDL_Rect tmp = { 0, 0, 384 * app->windowModule->scale, 240 * app->windowModule->scale };
			SDL_Rect tmp2 = { 384, 0, 384, 240 };
			app->renderModule->Print(app->texturesModule->title_sprite, &tmp2, &tmp);
		}
		else{
			if (app->current_time < 150){
				SDL_Rect tmp = { 0, 0, 384 * app->windowModule->scale, 240 * app->windowModule->scale };
				SDL_Rect tmp2 = { 768, 0, 384, 240 };
				app->renderModule->Print(app->texturesModule->title_sprite, &tmp2, &tmp);
			}
			else{
				SDL_Rect tmp = { 0, 0, 384 * app->windowModule->scale, 240 * app->windowModule->scale };
				SDL_Rect tmp2 = { 1152, 0, 384, 240 };
				app->renderModule->Print(app->texturesModule->title_sprite, &tmp2, &tmp);
				SDL_Rect tmp4 = { 100 * app->windowModule->scale, 200 * app->windowModule->scale, 177 * app->windowModule->scale, 15 * app->windowModule->scale };
				SDL_Rect tmp3 = { 1536, 0, 176, 15 };
				if (resto == 0)app->renderModule->Print(app->texturesModule->title_sprite, &tmp3, &tmp4); 
			}
		}
	}




	if (app->current_time > 500 || app->inputModule->key[SDL_SCANCODE_SPACE] == 1){ return CHANGE_TO_PLAY; }
	return UPDATE_CONTINUE;
}
	
update_status ModuleTitle::PostUpdate(){ return UPDATE_CONTINUE; }

bool ModuleTitle::CleanUp(){ return true; }