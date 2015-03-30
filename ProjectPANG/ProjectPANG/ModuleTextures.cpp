#include "ModuleTextures.h"

#include "SDL_image/include/SDL_image.h"
#pragma comment( lib, "SDL_image/libx86/SDL2_image.lib" )

ModuleTextures::ModuleTextures(Application* app) : Module(app)
{
	background_sprite = NULL;
	character_sprite = NULL;
	enemy_sprite = NULL;
	balloon_sprite = NULL;
	harpoon_sprite = NULL;
	powerUp_sprite = NULL;
}
bool ModuleTextures::Init()
{
	background_sprite = IMG_LoadTexture(app->renderModule->renderer, "images/Edited/Backgrounds.png");
	if (background_sprite == NULL){ LOG("______________________________________________________"); return false; }

	character_sprite = IMG_LoadTexture(app->renderModule->renderer, "images/Edited/Players.png");
	if (character_sprite == NULL){ return false; }

	enemy_sprite = IMG_LoadTexture(app->renderModule->renderer, "images/enemies.png");
	//if (enemy_sprite == NULL){ return false; }

	balloon_sprite = IMG_LoadTexture(app->renderModule->renderer, "images/balloons.png");
	//if (balloon_sprite == NULL){ return false; }

	harpoon_sprite = IMG_LoadTexture(app->renderModule->renderer, "images/harpoons.png");
	//if (harpoon_sprite == NULL){ return false; }

	powerUp_sprite = IMG_LoadTexture(app->renderModule->renderer, "images/harpoons.png");
	//if (powerUp_sprite == NULL){ return false; }

	return true;
}
update_status ModuleTextures::PreUpdate(){ return UPDATE_CONTINUE; }
update_status ModuleTextures::Update(){ return UPDATE_CONTINUE; }
update_status ModuleTextures::PostUpdate(){ return UPDATE_CONTINUE; }
bool ModuleTextures::CleanUp(){ return true; }
