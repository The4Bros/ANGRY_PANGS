#include "ModuleTitle.h"

ModuleTitle::ModuleTitle(Application* app) : Module(app){}
bool ModuleTitle::Init(){ return true; }
update_status ModuleTitle::PreUpdate(){ return UPDATE_CONTINUE; }
update_status ModuleTitle::Update(){ return CHANGE_TO_PLAY; }
update_status ModuleTitle::PostUpdate(){ return UPDATE_CONTINUE; }
bool ModuleTitle::CleanUp(){ return true; }