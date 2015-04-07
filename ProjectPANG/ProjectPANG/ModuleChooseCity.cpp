#include "ModuleChooseCity.h"

ModuleChooseCity::ModuleChooseCity(Application* app) : Module(app){}
bool ModuleChooseCity::Init(){ return true; }
update_status ModuleChooseCity::PreUpdate(){ return UPDATE_CONTINUE; }
update_status ModuleChooseCity::Update(){ return CHANGE_TO_PLAY; }
update_status ModuleChooseCity::PostUpdate(){ return UPDATE_CONTINUE; }
bool ModuleChooseCity::CleanUp(){ return true; }