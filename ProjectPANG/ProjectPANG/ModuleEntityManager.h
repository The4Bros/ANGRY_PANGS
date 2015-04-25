#include "Module.h"
#include "Globals.h"
#include "Application.h"
#include "Balloon.h"
#include "Stair.h"
#include "Brick.h"
#include "Particles.h"

#ifndef __ModuleEntityManager_H__
#define __ModuleEntityManager_H__


class ModuleEntityManager : public Module{
public:

	SDL_Rect harpoon_source_rect[25];

	DynArray<Brick*>* bricks;
	SDL_Rect source_brick_rect[18];

	DynArray<Stair*>* stairs;
	SDL_Rect source_stair_rect;

	DynArray<Balloon*>* balloons;
	SDL_Rect source_balloon_rect[12];
	unsigned int balloon_speed;

	//DynArray<Enemy*>* enemies;
	SDL_Rect source_enemy_rect[200];

	DynArray<Particles*>* particles;
	SDL_Rect particles_source_rect[200];


	ModuleEntityManager(Application* app);
	bool Init();
	update_status PreUpdate();
	update_status Update();
	bool CleanUp();
};

#endif