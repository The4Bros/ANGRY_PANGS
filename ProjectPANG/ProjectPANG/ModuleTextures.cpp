#include "ModuleTextures.h"

#include "SDL_image/include/SDL_image.h"
#pragma comment( lib, "SDL_image/libx86/SDL2_image.lib" )

ModuleTextures::ModuleTextures(Application* app) : Module(app)
{
	background_sprite = NULL;
	character_sprite = NULL;
}
bool ModuleTextures::Init()
{
	background_sprite = IMG_LoadTexture(app->renderModule->renderer, "backgrounds.png");
	if (background_sprite == NULL){ return false; }

	character_sprite = IMG_LoadTexture(app->renderModule->renderer, "Character.png");
	if (character_sprite == NULL){ return false; }
	return true;
}
update_status ModuleTextures::PreUpdate(){ return UPDATE_CONTINUE; }
update_status ModuleTextures::Update(){ return UPDATE_CONTINUE; }
update_status ModuleTextures::PostUpdate(){ return UPDATE_CONTINUE; }
bool ModuleTextures::CleanUp(){ return true; }
