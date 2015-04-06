#include "Module.h"
#include "Globals.h"
#include "Application.h"

#ifndef __ModuleEntityManager_H__
#define __ModuleEntityManager_H__

class ModuleEntityManager : public Module{
public:

	int update_sprite_character_counter;
	int character_direction;

	SDL_Rect background_rect;
	SDL_Rect background_const_source_rect;
	const SDL_Rect* background_const_rect;

	SDL_Rect character_rect;
	SDL_Rect character_const_source_rect;
	const SDL_Rect* character_const_rect;

	ModuleEntityManager(Application* app);
	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	bool colision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
	bool colisionHarpoonBall(int x1, int y1, int r, int x2, int y2, int w2);
};

#endif