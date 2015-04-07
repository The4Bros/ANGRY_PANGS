#include "ModuleTutorial.h"

ModuleTutorial::ModuleTutorial(Application* app) : Module(app){}
bool ModuleTutorial::Init(){ return true; }
update_status ModuleTutorial::PreUpdate(){ return UPDATE_CONTINUE; }
update_status ModuleTutorial::Update(){ return CHANGE_TO_PLAY; }
update_status ModuleTutorial::PostUpdate(){ return UPDATE_CONTINUE; }
bool ModuleTutorial::CleanUp(){ return true; }