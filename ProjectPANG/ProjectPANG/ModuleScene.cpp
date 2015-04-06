#include "ModuleScene.h"

ModuleScene::ModuleScene(Application* app) : Module(app){}
bool ModuleScene::Init()
{
	background_rect = { 0, 0, SCREEN_WIDTH * app->windowModule->scale, (SCREEN_HEIGHT - 32) * app->windowModule->scale };
	background_const_source_rect = { 0, 0, 384, 208};
	background_const_rect = new SDL_Rect(background_const_source_rect);

	return true;
}
update_status ModuleScene::PreUpdate(){ return UPDATE_CONTINUE; }
update_status ModuleScene::Update(){ return UPDATE_CONTINUE; }
update_status ModuleScene::PostUpdate(){ return UPDATE_CONTINUE; }
bool ModuleScene::CleanUp(){ return true; }
