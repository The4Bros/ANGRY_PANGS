#pragma once

#include "Globals.h"
#include "DoubleNodedList.h"

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
#include "ModuleTitle.h"
#include "ModuleTutorial.h"
#include "ModuleChooseCity.h"
#include "ModulePlane.h"
#include "ModuleCredits.h"
#include "ModuleHighscore.h"


class Application
{
private:
	DoubleNodedList<Module*> modules_Queue;

public:

	unsigned int current_time;
	time_t	timer;

	unsigned int coins, stage;

	// General Modules
	ModuleWindow* windowModule;
	ModuleRender* renderModule;
	ModuleInput* inputModule;
	ModuleTextures* texturesModule;
	ModuleAudio* audioModule;
	ModuleFontManager* fontManagerModule;

	// Other Modules
	ModulePlayer* playerModule;
	ModuleEntityManager* entityManagerModule;
	ModuleScene* sceneModule;
	ModuleTitle* titleModule;
	ModuleTutorial* tutorialModule;
	ModuleChooseCity* chooseCityModule;
	ModulePlane* planeModule;
	ModuleCredits* creditsModule;
	ModuleHighscore* highscoreModule;

	// Other Module nodes
	DoubleNode<Module*>* playerModule_Node;
	DoubleNode<Module*>* entityManagerModule_Node;
	DoubleNode<Module*>* sceneModule_Node;
	DoubleNode<Module*>* titleModule_Node;
	DoubleNode<Module*>* tutorialModule_Node;
	DoubleNode<Module*>* chooseCityModule_Node;
	DoubleNode<Module*>* planeModule_Node;
	DoubleNode<Module*>* creditsModule_Node;
	DoubleNode<Module*>* highscoreModule_Node;

	Application();
	~Application();
	bool Init();
	update_status Update();
	bool CleanUp();

	bool ChangeTo(update_status new_state);

	void Reset_Time();
	void Add_Coin();
	bool Lose_Coin();

};