#include "ModuleEntityManager.h"

ModuleEntityManager::ModuleEntityManager(Application* app) : Module(app)
{
	balloons = NULL;
	bricks = NULL;
}
bool ModuleEntityManager::Init()
{

	balloons = new DynArray<Balloon*>();

	source_balloon_rect[0] = new SDL_Rect({ 0, 0, 32, 32 });
	balloon_sample = new Balloon(app, 150, 30, 1, 20);

	source_stair_rect = new SDL_Rect({ 0, 104, 24, 8 });

	bricks = new DynArray<Brick*>();
	source_brick_rect[0] = new SDL_Rect({ 0, 0, 31, 7 });
	brick_sample = new Brick(app, 75, 48, 1);
	
	return true;
}
update_status ModuleEntityManager::PreUpdate(){ return UPDATE_CONTINUE; }
update_status ModuleEntityManager::Update()
{	
	brick_sample->Update();
	balloon_sample->Update();
	return UPDATE_CONTINUE;
}
update_status ModuleEntityManager::PostUpdate(){ return UPDATE_CONTINUE; }
bool ModuleEntityManager::CleanUp(){ return true; }
