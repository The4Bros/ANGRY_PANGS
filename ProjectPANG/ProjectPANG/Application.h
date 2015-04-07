#pragma once

#include "Globals.h"
#include "Queue.h"

#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleFontManager.h"

#include "ModulePlayer.h"
#include "ModuleEntityManager.h"
#include "ModuleScene.h"
/*
#include "ModuleTitle
#include "ModuleTutorial"
#include "ModuleChooseCity"
#include "ModulePlane"
#include "ModuleCredits"
#include "ModuleHighscoreInput"
#include "ModuleHishscoreTable"
*/



class Application{
private:
	DoubleNodedQueue<Module*> modules_Queue;
	DoubleNode<Module*>* item;
	update_status returnValue;

public:
	// General Modules
	ModuleWindow* windowModule;
	ModuleRender* renderModule;
	ModuleInput* inputModule;
	ModuleTextures* texturesModule;
	ModuleAudio* audioModule;
	ModuleFontManager* fontManagerModule;

	// Specific Modules
	ModulePlayer* playerModule;
	ModuleEntityManager* entityManagerModule;
	ModuleScene* sceneModule;

	/*
	ModuleTitle* titleModule;
	ModuleTutorial* tutorialModule;
	ModuleChooseCity* chooseCityModule;
	ModulePlane* planeModule;
	ModuleCredits* creditsModule;
	ModuleHighscoreInput* highscoreInputModule;
	ModuleHishscoreTable* highscoreTableModule;
	*/


	Application();
	~Application();
	bool Init();
	update_status Update();
	bool CleanUp();

	bool ChangeTo(update_status new_state);

};