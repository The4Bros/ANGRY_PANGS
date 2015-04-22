#include "ModuleTextures.h"

#include "SDL_image/include/SDL_image.h"
#pragma comment( lib, "SDL_image/libx86/SDL2_image.lib" )

ModuleTextures::ModuleTextures(Application* app) : Module(app)
{
	background_sprite = NULL;
	balls_sprite = NULL;
	bricks_sprite = NULL;
	enemies_sprite = NULL;
	harpoons_sprite = NULL;
	instructions_sprite = NULL;
	map_countdown_sprite = NULL;
	map_sprite = NULL;
	particles_sprite = NULL;
	players_sprite = NULL;
	ready = NULL;
	scores_sprite = NULL;
	timer_sprite = NULL;
	title_sprite = NULL;

}
bool ModuleTextures::Init()
{
	background_sprite = IMG_LoadTexture(app->renderModule->renderer, "images/Backgrounds.png");
	if (background_sprite == NULL){ return false; }

	balls_sprite = IMG_LoadTexture(app->renderModule->renderer, "images/Balls.png");
	if (balls_sprite == NULL){ return false; }

	bricks_sprite = IMG_LoadTexture(app->renderModule->renderer, "images/Bricks.png");
	if (bricks_sprite == NULL){ return false; }

	enemies_sprite = IMG_LoadTexture(app->renderModule->renderer, "images/Enemies.png");
	if (enemies_sprite == NULL){ return false; }

	harpoons_sprite = IMG_LoadTexture(app->renderModule->renderer, "images/Harpoons.png");
	if (harpoons_sprite == NULL){ return false; }

	map_countdown_sprite = IMG_LoadTexture(app->renderModule->renderer, "images/Map Countdown.png");
	if (map_countdown_sprite == NULL){ return false; }

	map_sprite = IMG_LoadTexture(app->renderModule->renderer, "images/Map.png");
	if (map_sprite == NULL){ return false; }

	particles_sprite = IMG_LoadTexture(app->renderModule->renderer, "images/Particles.png");
	if (particles_sprite == NULL){ return false; }

	players_sprite = IMG_LoadTexture(app->renderModule->renderer, "images/Players.png");
	if (players_sprite == NULL){ return false; }

	ready = IMG_LoadTexture(app->renderModule->renderer, "images/Ready.png");
	if (ready == NULL){ return false; }

	scores_sprite = IMG_LoadTexture(app->renderModule->renderer, "images/Score.png");
	if (scores_sprite == NULL){ return false; }

	timer_sprite = IMG_LoadTexture(app->renderModule->renderer, "images/Timer.png");
	if (timer_sprite == NULL){ return false; }

	title_sprite = IMG_LoadTexture(app->renderModule->renderer, "images/Title.png");
	if (title_sprite == NULL){ return false; }

	level_complete = IMG_LoadTexture(app->renderModule->renderer, "images/SpriteEndStage/Stage1.png");
	if (level_complete == NULL){ return false; }
	

	return true;
}
update_status ModuleTextures::PreUpdate(){ return UPDATE_CONTINUE; }
update_status ModuleTextures::Update(){ return UPDATE_CONTINUE; }
update_status ModuleTextures::PostUpdate(){ return UPDATE_CONTINUE; }
bool ModuleTextures::CleanUp(){ return true; }
