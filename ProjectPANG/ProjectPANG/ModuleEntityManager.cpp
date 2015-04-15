#include "ModuleEntityManager.h"

ModuleEntityManager::ModuleEntityManager(Application* app) : Module(app)
{
	balloons = NULL;
}
bool ModuleEntityManager::Init()
{

	balloons = new DynArray<Balloon*>();

	source_balloon_rect[0] = new SDL_Rect({ 0, 0, 32, 32 });
	balloon_sample = new Balloon(app, 150, 30, 1, 20);









	return true;
}
update_status ModuleEntityManager::PreUpdate(){ return UPDATE_CONTINUE; }
update_status ModuleEntityManager::Update()
{
	balloon_sample->Update();
	return UPDATE_CONTINUE;
}
update_status ModuleEntityManager::PostUpdate(){ return UPDATE_CONTINUE; }
bool ModuleEntityManager::CleanUp(){ return true; }
