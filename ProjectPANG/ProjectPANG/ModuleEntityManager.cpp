#include "ModuleEntityManager.h"

ModuleEntityManager::ModuleEntityManager(Application* app) : Module(app)
{
	character_rect = { 250, 336, 64, 64 };
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
	
	if (app->inputModule->key[SDL_SCANCODE_LEFT] == 1 && character_rect.x > 18)
	{
		character_rect.x -= 5;
	}
	if (app->inputModule->key[SDL_SCANCODE_RIGHT] == 1 && character_rect.x < SCREEN_WIDTH - 82)
	{
		character_rect.x += 5;
	}
	if (app->inputModule->key[SDL_SCANCODE_UP] == 1 && character_rect.y > 18)
	{
		character_rect.y -= 4;
	}
	if (app->inputModule->key[SDL_SCANCODE_DOWN] == 1 && character_rect.y < SCREEN_HEIGHT - 146)
	{
		character_rect.y += 4;
	}
	if (app->inputModule->key[SDL_SCANCODE_SPACE] == 1)
	{
		
	}

	
	return UPDATE_CONTINUE;
}
update_status ModuleEntityManager::PostUpdate(){ return UPDATE_CONTINUE; }
bool ModuleEntityManager::CleanUp(){ return true; }
