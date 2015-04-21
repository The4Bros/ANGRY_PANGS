#include "Module.h"
#include "Globals.h"
#include "Application.h"

#ifndef __ModuleEntityManager_H__
#define __ModuleEntityManager_H__


#include "Balloon.h"
#include "Stair.h"
#include "Brick.h"
#include "Particles.h"


class ModuleEntityManager : public Module{
public:

	
	SDL_Rect* harpoon_source_rect[25];

	DynArray<Brick*>* bricks;
	SDL_Rect* source_brick_rect[18];
	Brick* tmp_brick;

	DynArray<Stair*>* stairs;
	SDL_Rect* source_stair_rect;
	Stair* tmp_stair;

	DynArray<Balloon*>* balloons;
	SDL_Rect* source_balloon_rect[12];
	unsigned int balloon_speed;
	Balloon* tmp_balloon;


	//DynArray<Enemy*>* enemies;
	SDL_Rect* source_enemy_rect[74];
	

	DynArray<Particles*>* particles;
	SDL_Rect* particles_source_rect[5];
	Particles* tmp_particle;

	ModuleEntityManager(Application* app);
	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	// Collisions
	bool Collision(SDL_Rect* rect_1, SDL_Rect* rect_2);

	void Collision_Balloon_Players(SDL_Rect* balloon_rect);
};

#endif