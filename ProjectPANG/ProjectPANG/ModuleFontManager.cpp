#include "ModuleFontManager.h"

ModuleFontManager::ModuleFontManager(Application* app) : Module(app){}
bool ModuleFontManager ::Init(){ return true; }
update_status ModuleFontManager::PreUpdate(){ return UPDATE_CONTINUE; }
update_status ModuleFontManager::Update(){ return UPDATE_CONTINUE; }
update_status ModuleFontManager::PostUpdate(){ return UPDATE_CONTINUE; }
bool ModuleFontManager::CleanUp(){ return true; }
