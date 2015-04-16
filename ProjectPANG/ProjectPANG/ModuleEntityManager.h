#include "Module.h"
#include "Globals.h"
#include "Application.h"

#ifndef __ModuleEntityManager_H__
#define __ModuleEntityManager_H__


#include "Balloon.h"
#include "Stair.h"
#include "Brick.h"


class ModuleEntityManager : public Module{
public:

	unsigned int balloon_speed;

	DynArray<Brick*>* bricks;
	Brick* brick_sample;
	SDL_Rect* source_brick_rect[18];

	DynArray<Stair*>* stairs;
	SDL_Rect* source_stair_rect;

	DynArray<Balloon*>* balloons;
	Balloon* balloon_sample;
	SDL_Rect* source_balloon_rect[12];

	//DynArray<Enemy*>* enemies;
	SDL_Rect* source_enemy_rect[74];
	

	ModuleEntityManager(Application* app);
	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	bool colision(SDL_Rect* rect_1, SDL_Rect* rect_2);
	bool colisionHarpoonBall(SDL_Rect* rect_1, SDL_Rect* rect_2);
};

#endif