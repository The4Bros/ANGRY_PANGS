#include "ModuleEntityManager.h"

ModuleEntityManager::ModuleEntityManager(Application* app) : Module(app)
{
	character_rect = { 250, 334, 64, 64 };
	background_rect = { 0, 0, SCREEN_WIDTH, BACKGROUND_HEIGHT };

	background_const_source_rect = { 0, 0, 384, 208 };
	character_const_source_rect = { 0, 0, 32, 32 };

	update_sprite_character_counter = 0;
	character_direction = 0; // right, left, up, down - 0, 1, 2, 3
}
bool ModuleEntityManager::Init()
{
	background_const_rect = new SDL_Rect(background_const_source_rect);
	character_const_rect = new SDL_Rect(character_const_source_rect);
	
	//https:// umbrello.kde.org/

	return true;
}
update_status ModuleEntityManager::PreUpdate(){ return UPDATE_CONTINUE; }
update_status ModuleEntityManager::Update()
{
	
	if (app->inputModule->key[SDL_SCANCODE_G] == 1)
	{
		if (background_const_source_rect.x < 768)
		{
			background_const_source_rect.x += 384;
		}
		else if (background_const_source_rect.y < 3328)
		{
			background_const_source_rect.x = 0;
			background_const_source_rect.y += 208;
		}
		else
		{
			background_const_source_rect.x = 0;
			background_const_source_rect.y = 0;
		}
		background_const_rect = new SDL_Rect(background_const_source_rect);
		SDL_Delay(200);
	}



	if (app->inputModule->key[SDL_SCANCODE_LEFT] == 1 && character_rect.x > 18)
	{
		if (character_direction == 1)
		{
			if (update_sprite_character_counter > 2)
			{
				delete[] character_const_rect;
				if (character_const_source_rect.x < 288){ character_const_source_rect.x += 32; }
				else { character_const_source_rect.x = 160; }
				character_const_rect = new SDL_Rect(character_const_source_rect);
				update_sprite_character_counter = 0;
			}
			else { update_sprite_character_counter++; }
			character_rect.x -= 5;
		}
		else
		{
			delete[] character_const_rect;
			character_direction = 1;
			character_const_source_rect.x = 160;
			character_const_rect = new SDL_Rect(character_const_source_rect);
			update_sprite_character_counter = 0;
		}
	}




	if (app->inputModule->key[SDL_SCANCODE_RIGHT] == 1 && character_rect.x < SCREEN_WIDTH - 82)
	{
		if (character_direction == 0)
		{
			if (update_sprite_character_counter > 1)
			{
				if (character_const_source_rect.x < 128){ character_const_source_rect.x += 32; }
				else { character_const_source_rect.x = 0; }
				delete[] character_const_rect;
				character_const_rect = new SDL_Rect(character_const_source_rect);
				update_sprite_character_counter = 0;
			}
			else { update_sprite_character_counter++; }
			character_rect.x += 5;
		}
		else
		{
			delete[] character_const_rect;
			character_direction = 0;
			character_const_source_rect.x = 0;
			character_const_rect = new SDL_Rect(character_const_source_rect);
			update_sprite_character_counter = 0;
		}
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
