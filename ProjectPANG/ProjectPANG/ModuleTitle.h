#include "Module.h"
#include "Globals.h"
#include "Application.h"


#ifndef __ModuleTitle_H__
#define __ModuleTitle_H__


class ModuleTitle : public Module{
public:

	int ticks;
	SDL_Rect rect;
	SDL_Rect insert_coin_rect;
	SDL_Rect* source_rect[5];
	int dir;
	SDL_Rect balloon_rects[4];
	SDL_Rect* balloon_source_rect;

	bool insert_coin_pressed;

	ModuleTitle(Application* app);
	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	void Update_Balloons();
};

#endif