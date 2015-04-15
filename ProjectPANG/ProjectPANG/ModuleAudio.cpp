#include "ModuleAudio.h"

ModuleAudio::ModuleAudio(Application* app) : Module(app){}
bool ModuleAudio::Init(){ return true; }
update_status ModuleAudio::PreUpdate(){ return UPDATE_CONTINUE; }
update_status ModuleAudio::Update(){ return UPDATE_CONTINUE; }
update_status ModuleAudio::PostUpdate()
{




	return UPDATE_CONTINUE;
}

//void Play_Sound( _____, ...)



bool ModuleAudio::CleanUp(){ return true; }
