#include "ModuleEntityManager.h"

ModuleEntityManager::ModuleEntityManager(Application* app) : Module(app)
{
	balloons = NULL;
	stairs = NULL;
	bricks = NULL;
	particles = NULL;

	tmp_balloon = NULL;
	tmp_stair = NULL;
	tmp_brick = NULL;
	tmp_particle = NULL;
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


	// PARTICLES
	particles = new DynArray<Particles*>();

	for (int i2 = 0; i2 < 3; i2++)
	{
		for (int i = 0; i < 4; i++)
		{
			particles_source_rect[i + (i2 * 4)] = new SDL_Rect({ i * 48 + (i2 * 192), 0, 48, 40 });
			particles_source_rect[i + 12 + (i2 * 4)] = new SDL_Rect({ i * 32 + (i2 * 192), 40, 32, 29 });
			particles_source_rect[i + 24 + (i2 * 4)] = new SDL_Rect({ i * 16 + (i2 * 192), 69, 16, 16 });
			particles_source_rect[i + 36 + (i2 * 4)] = new SDL_Rect({ i * 8 + (i2 * 192), 85, 8, 8 });
		}
	}
	for (int i = 0; i < 5; i++){ particles_source_rect[i + 48] = new SDL_Rect({ i * 28, 93, 28, 26 }); }
	for (int i = 0; i < 4; i++){ particles_source_rect[i + 52] = new SDL_Rect({ i * 15, 119, 15, 15 }); }

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
		for (unsigned int i = 0; i < particles->Count(); i++)
		{
			tmp_particle = *particles->at(i);
			tmp_particle->Update();
		}
	}
	



	return UPDATE_CONTINUE;
}

update_status ModuleEntityManager::PostUpdate(){ return UPDATE_CONTINUE; }

bool ModuleEntityManager::CleanUp(){ return true; }


