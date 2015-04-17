#include "ModuleEntityManager.h"

ModuleEntityManager::ModuleEntityManager(Application* app) : Module(app)
{
	balloons = NULL;
	tmp_balloon = NULL;
	
	stairs = NULL;
	tmp_stair = NULL;

	bricks = NULL;
	tmp_brick = NULL;
}
bool ModuleEntityManager::Init()
{
	// BRICKS
	bricks = new DynArray<Brick*>();
	source_brick_rect[0] = new SDL_Rect({ 0, 0, 32, 8 });
	brick_sample = new Brick(app, 75, 48, 1);


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
	source_balloon_rect[5] = new SDL_Rect({ 48, 62, 32, 26 });

	source_balloon_rect[6] = new SDL_Rect({ 80, 62, 16, 14 });
	source_balloon_rect[7] = new SDL_Rect({ 96, 62, 16, 14 });
	source_balloon_rect[8] = new SDL_Rect({ 80, 76, 16, 14 });

	source_balloon_rect[9] = new SDL_Rect({ 96, 76, 8, 7 });
	source_balloon_rect[10] = new SDL_Rect({ 102, 76, 8, 7 });
	source_balloon_rect[11] = new SDL_Rect({ 96, 83, 8, 7 });

	balloon_sample = new Balloon(app, 150, 30, 1, 20);
	


	// ENEMIES
	//enemies = new DynArray<Enemy*>();
	//source_enemy_rect = new SDL_Rect({ 0, 104, 24, 8 });
	

	



	return true;
}
update_status ModuleEntityManager::PreUpdate(){ return UPDATE_CONTINUE; }
update_status ModuleEntityManager::Update()
{
	balloon_sample->Update();
	
	// BALLOONS
	for (unsigned int i = 0; i < balloons->Count(); i++)
	{
		tmp_balloon = *balloons->at(i);
		tmp_balloon->Update();
	}



	return UPDATE_CONTINUE;
}
update_status ModuleEntityManager::PostUpdate(){ return UPDATE_CONTINUE; }
bool ModuleEntityManager::CleanUp(){ return true; }
