#include "ModuleEntityManager.h"

ModuleEntityManager::ModuleEntityManager(Application* app) : Module(app)
{
	unsigned int i, i2;
	// HARPOON BODIES
	for (i = 0; i < 8; i++)
	{
		harpoon_source_rect[i + 8] = { 0, 0, 7, (i + 1) * 2 };
		harpoon_source_rect[i] = { 7, 0, 7, (i + 1) * 2 };
	}

	// HARPOON HEADS
	harpoon_source_rect[16] = { 14, 0, 9, 9 };
	harpoon_source_rect[17] = { 22, 0, 9, 9 };

	// HARPOON GRAPPLE HEADS
	harpoon_source_rect[18] = { 14, 9, 9, 6 };
	harpoon_source_rect[19] = { 22, 9, 9, 6 };

	// HARPOON GRAPPLED HEADS
	harpoon_source_rect[20] = { 31, 0, 9, 4 };
	harpoon_source_rect[21] = { 31, 4, 9, 4 };
	harpoon_source_rect[22] = { 31, 8, 9, 4 };

	// HARPOON GRAPPLED BODIES
	harpoon_source_rect[23] = { 31, 13, 3, 2 };
	harpoon_source_rect[24] = { 34, 13, 3, 2 };
	harpoon_source_rect[25] = { 37, 13, 3, 2 };

	// BRICKS
	for (i = 0; i < 3; i++)
	{
		source_brick_rect[i] = { 120, 24 + (i * 8), 8, 8 };
		source_brick_rect[i + 3] = { 0, 48 + (i * 8), 16, 8 };
		source_brick_rect[i + 6] = { 0, 24 + (i * 8), 24, 8 };
		source_brick_rect[i + 9] = { 0, i * 8, 32, 8 };
	}
	source_brick_rect[12] = { 0, 72, 8, 32 };
	source_brick_rect[13] = { 40, 72, 8, 32 };
	source_brick_rect[14] = { 80, 72, 8, 16 };
	source_brick_rect[15] = { 80, 88, 8, 24 };


	// STAIRS
	source_stair_rect = { 0, 104, 24, 8 };

	// BALLOONS
	source_balloon_rect[0] = { 0, 0, 48, 40 };
	source_balloon_rect[1] = { 48, 0, 48, 40 };
	source_balloon_rect[2] = { 0, 40, 48, 40 };

	source_balloon_rect[3] = { 48, 40, 32, 26 };
	source_balloon_rect[4] = { 80, 40, 32, 26 };
	source_balloon_rect[5] = { 48, 66, 32, 26 };

	source_balloon_rect[6] = { 80, 66, 16, 14 };
	source_balloon_rect[7] = { 96, 66, 16, 14 };
	source_balloon_rect[8] = { 80, 80, 16, 14 };

	source_balloon_rect[9] = { 96, 80, 8, 7 };
	source_balloon_rect[10] = { 104, 80, 8, 7 };
	source_balloon_rect[11] = { 96, 87, 8, 7 };



	// ENEMIES
	//enemies = new DynArray<Enemy*>();
	/*
	for (int i = 0; i < 16; i++){ source_enemy_rect[i] = { i * 32, 0, 32, 32 }; }
	for (int i = 0; i < 10; i++){ source_enemy_rect[i + 16] = { i * 32, 32, 32, 32 }; }
	for (int i = 0; i < 22; i++){ source_enemy_rect[i + 26] = { i * 32, 64, 32, 32 }; }
	for (int i = 0; i < 11; i++){ source_enemy_rect[i + 48] = { i * 32, 96, 32, 32 }; }
	for (int i = 0; i < 13; i++){ source_enemy_rect[i + 59] = { i * 32, 128, 32, 32 }; }
	source_enemy_rect[72] = { 416, 128, 36, 24 };
	source_enemy_rect[73] = { 452, 182, 36, 24 };
	*/


	// PARTICLES
	for (i2 = 0; i2 < 3; i2++)
	{
		for (i = 0; i < 4; i++)
		{
			particles_source_rect[i + (i2 * 4)] = { i * 48 + (i2 * 192), 0, 48, 40 };
			particles_source_rect[i + 12 + (i2 * 4)] = { i * 32 + (i2 * 192), 40, 32, 29 };
			particles_source_rect[i + 24 + (i2 * 4)] = { i * 16 + (i2 * 192), 69, 16, 16 };
			particles_source_rect[i + 36 + (i2 * 4)] = { i * 8 + (i2 * 192), 85, 8, 8 };
		}
	}
	for (i = 0; i < 5; i++){ particles_source_rect[i + 48] = { i * 28, 93, 28, 26 }; }
	for (i = 0; i < 4; i++){ particles_source_rect[i + 52] = { i * 15, 119, 15, 15 }; }

	for (i2 = 0; i2 < 3; i2++)
	{
		for (i = 0; i < 4; i++)
		{
			particles_source_rect[i + 57 + (i2 * 4)] = { (i + 1) * 32, i2 * 8, 32, 8 };
		}
	}

	for (i2 = 0; i2 < 3; i2++)
	{
		for (i = 0; i < 4; i++)
		{
			particles_source_rect[i + 69 + (i2 * 4)] = { (i + 1) * 24, (i2 + 3) * 8, 24, 8 };
		}
	}

	for (i2 = 0; i2 < 3; i2++)
	{
		for (i = 0; i < 4; i++)
		{
			particles_source_rect[i + 81 + (i2 * 4)] = { (i + 1) * 16, (i2 + 6) * 8, 16, 8 };
		}
	}

	for (i2 = 0; i2 < 3; i2++)
	{
		for (i = 0; i < 4; i++)
		{
			particles_source_rect[i + 93 + (i2 * 4)] = { (i * 8) + 128, (i2 * 8) + 24, 8, 8 };
		}
	}

	for (i2 = 0; i2 < 2; i2++)
	{
		for (i = 0; i < 4; i++)
		{
			particles_source_rect[i + 105 + (i2 * 4)] = { (i + 1) * 8, i2 * 32, 8, 32 };
		}
	}

	for (i2 = 0; i2 < 1; i2++)
	{
		for (i = 0; i < 4; i++)
		{
			particles_source_rect[i + 115 + (i2 * 4)] = { (i + 1) * 8, i2 * 16, 8, 16 };
		}
	}

	for (i2 = 0; i2 < 1; i2++)
	{
		for (i = 0; i < 4; i++)
		{
			particles_source_rect[i + 119 + (i2 * 4)] = { (i + 1) * 8, i2 * 24, 8, 24 };
		}
	}


	balloon_speed = 2.0f;

	stop_time = slow_time = false;
	stop_time_counter = slow_time_counter = 0;
}

bool ModuleEntityManager::Init()
{
	stop_time = slow_time = false;
	stop_time_counter = slow_time_counter = 0;
	balloon_speed = 2.0f;

	return true;
}

update_status ModuleEntityManager::Update()
{
	if (slow_time)
	{
		if (slow_time_counter < 300){ slow_time_counter++; }
		else{ balloon_speed = 2; slow_time = false; }
	}

	if (app->sceneModule->game_state == PLAYING)
	{
		// BALLOONS
		if (!stop_time)
		{
			for (unsigned int i = 0; i < balloons.Count(); i++){ (*balloons.at(i))->Update(); }
		}
		else
		{
			if (stop_time_counter < 300){ stop_time_counter++; }
			else{ stop_time = false; }
		}

		// PARTICLES
		for (unsigned int i = 0; i < particles.Count(); i++){ (*particles.at(i))->Update(); }
	}

	return UPDATE_CONTINUE;
}



bool ModuleEntityManager::CleanUp()
{
	return true;
}


void ModuleEntityManager::StopTime()
{
	stop_time_counter = 0;
	stop_time = true;
}

void ModuleEntityManager::SlowTime()
{
	balloon_speed = 1;
	slow_time_counter = 0;
	slow_time = true;
}
