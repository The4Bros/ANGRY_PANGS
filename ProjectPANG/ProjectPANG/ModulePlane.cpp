#include "ModulePlane.h"

ModulePlane::ModulePlane(Application* app) : Module(app){}
bool ModulePlane::Init(){ return true; }
update_status ModulePlane::PreUpdate(){ return UPDATE_CONTINUE; }
update_status ModulePlane::Update(){ return CHANGE_TO_PLAY; }
update_status ModulePlane::PostUpdate(){ return UPDATE_CONTINUE; }
bool ModulePlane::CleanUp(){ return true; }