#include "ModuleEntityManager.h"

ModuleEntityManager::ModuleEntityManager(Application* app) : Module(app)
{
	balloons = NULL;
	tmp_balloon = NULL;
	
	stairs = NULL;
	bricks = NULL;
}
bool ModuleEntityManager::Init()
{
	// HARPOONS

	// BODIES
	for (int i = 0; i < 8; i++)
	{
		harpoon_source_rect[i + 8] = new SDL_Rect({ 0, 0, 7, (i + 1) * 2 });
		harpoon_source_rect[i] = new SDL_Rect({ 7, 0, 7, (i + 1) * 2 });
	}

	// HEADS
	harpoon_source_rect[16] = new SDL_Rect({ 14, 0, 9, 9 });
	harpoon_source_rect[17] = new SDL_Rect({ 22, 0, 9, 9 });

	// GRAPPLE HEADS
	harpoon_source_rect[18] = new SDL_Rect({ 14, 9, 9, 6 });
	harpoon_source_rect[19] = new SDL_Rect({ 22, 9, 9, 6 });

	// GRAPPLED HEADS
	harpoon_source_rect[20] = new SDL_Rect({ 31, 0, 9, 4 });
	harpoon_source_rect[21] = new SDL_Rect({ 31, 4, 9, 4 });
	harpoon_source_rect[22] = new SDL_Rect({ 31, 8, 9, 4 });

	// GRAPPLED BODIES
	harpoon_source_rect[23] = new SDL_Rect({ 31, 13, 3, 2 });
	harpoon_source_rect[24] = new SDL_Rect({ 34, 13, 3, 2 });
	harpoon_source_rect[25] = new SDL_Rect({ 37, 13, 3, 2 });




	// BRICKS
	bricks = new DynArray<Brick*>();
	for (int i = 0; i < 3; i++)
	{
		source_brick_rect[i] = new SDL_Rect({ 120, 24 + (i * 8), 8, 8 });
		source_brick_rect[i + 3] = new SDL_Rect({ 0, 48 + (i * 8), 0, 0 });
		source_brick_rect[i + 6] = new SDL_Rect({ 0, 24 + (i * 8), 0, 0 });
		source_brick_rect[i + 9] = new SDL_Rect({ 0, i * 8, 0, 0 });
	}
	source_brick_rect[12] = new SDL_Rect({ 0, 72, 32, 8 });
	source_brick_rect[13] = new SDL_Rect({ 40, 72, 32, 8 });
	source_brick_rect[14] = new SDL_Rect({ 80, 72, 16, 8 });
	source_brick_rect[15] = new SDL_Rect({ 80, 88, 24, 8 });

	


	// STAIRS
	stairs = new DynArray<Stair*>();
	source_stair_rect = new SDL_Rect({ 0, 104, 24, 8 });


	// BALLOONS
	balloons = new DynArray<Balloon*>();

	source_balloon_rect[0] = new SDL_Rect({ 0, 0, 48, 40 });
	source_balloon_rect[1] = new SDL_Rect({ 48, 0, 48, 40 });
	source_balloon_rect[2] = new SDL_Rect({ 0, 40, 48, 40 });

	source_balloon_rect[3] = new SDL_Rect({ 48, 40, 32, 26 });
	source_balloon_rect[4] = new SDL_Rect({ 80, 40, 32, 26 });
	source_balloon_rect[5] = new SDL_Rect({ 48, 66, 32, 26 });

	source_balloon_rect[6] = new SDL_Rect({ 80, 66, 16, 14 });
	source_balloon_rect[7] = new SDL_Rect({ 96, 66, 16, 14 });
	source_balloon_rect[8] = new SDL_Rect({ 80, 80, 16, 14 });

	source_balloon_rect[9] = new SDL_Rect({ 96, 80, 8, 7 });
	source_balloon_rect[10] = new SDL_Rect({ 104, 80, 8, 7 });
	source_balloon_rect[11] = new SDL_Rect({ 96, 87, 8, 7 });
	


	// ENEMIES
	//enemies = new DynArray<Enemy*>();
	/*
	for (int i = 0; i < 16; i++){ source_enemy_rect[i] = new SDL_Rect({ i * 32, 0, 32, 32 }); }
	for (int i = 0; i < 10; i++){ source_enemy_rect[i + 16] = new SDL_Rect({ i * 32, 32, 32, 32 }); }
	for (int i = 0; i < 22; i++){ source_enemy_rect[i + 26] = new SDL_Rect({ i * 32, 64, 32, 32 }); }
	for (int i = 0; i < 11; i++){ source_enemy_rect[i + 48] = new SDL_Rect({ i * 32, 96, 32, 32 }); }
	for (int i = 0; i < 13; i++){ source_enemy_rect[i + 59] = new SDL_Rect({ i * 32, 128, 32, 32 }); }
	source_enemy_rect[72] = new SDL_Rect({ 416, 128, 36, 24 });
	source_enemy_rect[73] = new SDL_Rect({ 452, 182, 36, 24 });
	*/


	return true;
}
update_status ModuleEntityManager::PreUpdate(){ return UPDATE_CONTINUE; }
update_status ModuleEntityManager::Update()
{
	if (app->sceneModule->game_state == PLAYING)
	{
		for (unsigned int i = 0; i < balloons->Count(); i++)
		{
			tmp_balloon = *balloons->at(i);
			tmp_balloon->Update();
		}
	}
	



	return UPDATE_CONTINUE;
}
update_status ModuleEntityManager::PostUpdate(){ return UPDATE_CONTINUE; }
bool ModuleEntityManager::CleanUp(){ return true; }



bool ModuleEntityManager::Collision(SDL_Rect* rect_1, SDL_Rect* rect_2)
{
	if (rect_1->x + rect_1->w >= rect_2->x) // rect_1 right
	{
		if (rect_2->x + rect_2->w >= rect_1->x) // rect_1 left
		{
			if (rect_1->y <= rect_2->y + rect_2->h) // rect_1 up
			{
				if (rect_1->y + rect_1->h >= rect_2->y) // rect_1 down
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool ModuleEntityManager::Collision_Player_Brick_Horizontal(SDL_Rect* player_rect, SDL_Rect* brick_rect)
{
	if (player_rect->x + player_rect->w >= brick_rect->x) // player right
	{
		if (brick_rect->x + brick_rect->w >= player_rect->x) // player left
		{
			if (player_rect->y + brick_rect->h >= player_rect->y) // player up
			{
				if (player_rect->y + player_rect->h >= brick_rect->y) // player down
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool ModuleEntityManager::Collision_Player_Brick_Vertical(SDL_Rect* player_rect, SDL_Rect* brick_rect)
{
	if (player_rect->x + player_rect->w >= brick_rect->x) // player right
	{
		if (brick_rect->x + brick_rect->w >= player_rect->x) // player left
		{
			if (player_rect->y + brick_rect->h >= player_rect->y) // player up
			{
				if (player_rect->y + player_rect->h >= brick_rect->y) // player down
				{
					return true;
				}
			}
		}
	}
	return false;
}