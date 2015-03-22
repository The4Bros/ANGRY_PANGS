#include "ModuleEntityManager.h"

ModuleEntityManager::ModuleEntityManager(Application* app) : Module(app)
{
	character_rect = {50, 50, 200, 200};
	character_const_rect = NULL;
}
bool ModuleEntityManager::Init()
{
	background_rect = { 1, 1, 598, 300 };
	background_const_source_rect = { 8, 8, 384, 208 };
	background_const_rect = new SDL_Rect(background_const_source_rect);
	
	return true;
}
update_status ModuleEntityManager::PreUpdate(){ return UPDATE_CONTINUE; }
update_status ModuleEntityManager::Update()
{
	
	//if (app->inputModule->key[SDLK_LEFT]){ character_rect.x -= 1; }
	//if (app->inputModule->key[SDLK_RIGHT]){ character_rect.x += 1; }
	//if (app->inputModule->key[SDLK_UP]){ character_rect.y -= 1; }
	//if (app->inputModule->key[SDLK_DOWN]){ character_rect.y += 1; }
	//if (key[SDLK_SPACE]){ pass }

	
	return UPDATE_CONTINUE;
}
update_status ModuleEntityManager::PostUpdate(){ return UPDATE_CONTINUE; }
bool ModuleEntityManager::CleanUp(){ return true; }
