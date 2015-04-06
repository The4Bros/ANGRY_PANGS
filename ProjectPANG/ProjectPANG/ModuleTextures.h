#include "Module.h"
#include "Globals.h"
#include "Application.h"

#include "SDL_image/include/SDL_image.h"
#pragma comment( lib, "SDL_image/libx86/SDL2_image.lib" )

#ifndef __ModuleTextures_H__
#define __ModuleTextures_H__

class ModuleTextures : public Module{
public:
	
	SDL_Texture* background_sprite;
	SDL_Texture* balls_sprite;
	SDL_Texture* bricks_sprite;
	SDL_Texture* enemies_sprite;
	SDL_Texture* harpoons_sprite;
	SDL_Texture* instructions_sprite;
	SDL_Texture* map_countdown_sprite;
	SDL_Texture* map_sprite;
	SDL_Texture* particles_sprite;
	SDL_Texture* players_sprite;
	SDL_Texture* ready;
	SDL_Texture* scores_sprite;
	SDL_Texture* timer_sprite;
	SDL_Texture* title_sprite;

	ModuleTextures(Application* app);
	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
};

#endif