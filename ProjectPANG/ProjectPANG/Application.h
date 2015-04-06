#pragma once

#include <time.h>

#include "Globals.h"
#include "Queue.h"

#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleEntityManager.h"
#include "ModuleScene.h"
#include "ModuleAudio.h"
#include "ModuleFontManager.h"




class Application{
private:
	DoubleNodedQueue<Module*> modules_Queue;
	DoubleNode<Module*>* item;
	Uint32 timer;
	update_status returnValue;

public:
	ModuleWindow* windowModule;
	ModuleRender* renderModule;
	ModuleInput* inputModule;
	ModuleTextures* texturesModule;
	ModulePlayer playerModule;
	ModuleEntityManager* entityManagerModule;
	ModuleScene* sceneModule;
	ModuleAudio* audioModule;
	ModuleFontManager* fontManagerModule;

	Application();
	~Application();
	bool Init();
	update_status Update();
	bool CleanUp();
	void AddModule(Module* mod);

};