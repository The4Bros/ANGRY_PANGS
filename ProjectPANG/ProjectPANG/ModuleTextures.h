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
	SDL_Texture* character_sprite;
	SDL_Texture* enemy_sprite;
	SDL_Texture* balloon_sprite;
	SDL_Texture* harpoon_sprite;
	SDL_Texture* powerUp_sprite;



	ModuleTextures(Application* app);
	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
};

#endif