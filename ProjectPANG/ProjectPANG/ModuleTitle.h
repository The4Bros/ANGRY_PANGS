#include "Module.h"
#include "Globals.h"
#include "Application.h"

#ifndef __ModuleTitle_H__
#define __ModuleTitle_H__

class ModuleTitle : public Module{
public:

	int gravity[4];
	int ticks;
	SDL_Rect rect;
	SDL_Rect insert_coin_rect;
	SDL_Rect source_rect[5];


	int dir[4];
	int aux[4];
	SDL_Rect balloon_rects[4];
	SDL_Rect balloon_source_rect;
	SDL_Rect balloon_split[4];
	SDL_Rect balloon_split_source_rect[4];
	bool insert_coin_pressed;
	bool balloons_title_up[4];

	ModuleTitle(Application* app);
	bool Init();
	update_status PreUpdate();
	update_status Update();
	bool CleanUp();

	void Update_Balloons();
};

#endif