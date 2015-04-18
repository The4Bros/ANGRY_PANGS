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

	DynArray<Stair*>* stairs;
	SDL_Rect* source_stair_rect;

	DynArray<Balloon*>* balloons;
	SDL_Rect* source_balloon_rect[12];
	unsigned int balloon_speed;
	Balloon* tmp_balloon;

	//DynArray<Enemy*>* enemies;
	SDL_Rect* source_enemy_rect[74];
	

	DynArray<Particles*>* particles;
	

	ModuleEntityManager(Application* app);
	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	// Collisions
	bool Collision(SDL_Rect* rect_1, SDL_Rect* rect_2);

	bool Collision_Player_Brick_Horizontal(SDL_Rect* rect_1, SDL_Rect* rect_2);
	bool Collision_Player_Brick_Vertical(SDL_Rect* rect_1, SDL_Rect* rect_2);

	bool Collision_Harpoon_Balloon(SDL_Rect* balloon_rect);
	bool Collision_Harpoon_Brick(SDL_Rect* balloon_rect);

	bool Collision_Bullet_Balloon(SDL_Rect* balloon_rect);

	void Collision_Balloon_Players(SDL_Rect* balloon_rect);
	bool Collision_Balloon_Brick_Vertical(SDL_Rect* balloon_rect);
	bool Collision_Balloon_Brick_Horizontal(SDL_Rect* balloon_rect);
};

#endif