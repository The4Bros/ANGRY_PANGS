#include "Module.h"
#include "Globals.h"
#include "Application.h"

#ifndef __ModuleScene_H__
#define __ModuleScene_H__

class ModuleScene : public Module{
public:

	//timer

	SDL_Rect background_rect;
	SDL_Rect background_const_source_rect;
	const SDL_Rect* background_const_rect;


	

	ModuleScene(Application* app);
	bool Init();

	background_rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT - 66 };

	background_const_source_rect = { 0, 0, 384, 208 };


	update_status PreUpdate();
	update_status Update();


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




	update_status PostUpdate();
	bool CleanUp();
};
#endif