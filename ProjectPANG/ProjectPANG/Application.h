#pragma once

#include "Globals.h"
#include "Queue.h"

#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleEntityManager.h"
#include "ModuleScene.h"
#include "ModuleAudio.h"
#include "ModuleFontManager.h"



class Application{
private:
	DoubleNodedQueue<Module*> modules_Stack;
	DoubleNode<Module*>* item;
	update_status returnValue;

public:
	ModuleWindow* windowModule;
	ModuleRender* renderModule;
	ModuleInput* inputModule;
	ModuleTextures* texturesModule;
	ModuleEntityManager* entityManagerModule;
	ModuleScene* sceneModule;
	ModuleAudio* audioModule;
	ModuleFontManager* fontManagerModule;

	Application();
	~Application();
	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

};