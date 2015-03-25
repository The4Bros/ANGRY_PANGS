#include "ModuleEntityManager.h"

ModuleEntityManager::ModuleEntityManager(Application* app) : Module(app)
{
	character_rect = { 250, 250, 45, 45 };
	background_rect = { 0, 0, SCREEN_WIDTH, BACKGROUND_HEIGHT };
}
bool ModuleEntityManager::Init()
{

	background_const_source_rect = { 8, 8, 384, 208 };
	background_const_rect = new SDL_Rect(background_const_source_rect);

	character_const_source_rect = { 10, 2, 32, 32 };
	character_const_rect = new SDL_Rect(character_const_source_rect);
	

	//https:// umbrello.kde.org/




	return true;
}
update_status ModuleEntityManager::PreUpdate(){ return UPDATE_CONTINUE; }
update_status ModuleEntityManager::Update()
{
	
	if (&app->inputModule->key[SDLK_SPACE] && character_rect.x > 1)
	{
		character_rect.x -= 1;
	}
	//if (&app->inputModule->key[SDL_SCANCODE_RIGHT]){ character_rect.x += 1; }
	//if (&app->inputModule->key[SDLK_UP]){ character_rect.y -= 1; }
	//if (&app->inputModule->key[SDLK_DOWN]){ character_rect.y += 1; }
	//if (key[SDLK_SPACE]){ pass }

	
	return UPDATE_CONTINUE;
}
update_status ModuleEntityManager::PostUpdate(){ return UPDATE_CONTINUE; }
bool ModuleEntityManager::CleanUp(){ return true; }
