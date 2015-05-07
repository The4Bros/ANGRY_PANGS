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

	DoubleNodedList<Brick*> bricks;
	SDL_Rect source_brick_rect[18];

	DoubleNodedList<Stair*> stairs;
	SDL_Rect source_stair_rect;

	DoubleNodedList<Balloon*> balloons;
	SDL_Rect source_balloon_rect[12];
	float balloon_speed;

	//DoubleNodedList<Enemy*>* enemies;
	SDL_Rect source_enemy_rect[200];

	DoubleNodedList<Particles*> particles;
	SDL_Rect particles_source_rect[200];

	bool stop_time, slow_time;
	unsigned int stop_time_counter, slow_time_counter;

	ModuleEntityManager(Application* app);
	bool Init();
	update_status Update();
	bool CleanUp();

	void StopTime();
	void SlowTime();
};

#endif