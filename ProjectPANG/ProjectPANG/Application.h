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
#include "ModuleChooseCity.h"
#include "ModulePlane.h"
#include "ModuleStageEnd.h"
#include "ModuleCredits.h"
#include "ModuleHighscore.h"


class Application
{
private:
	DoubleNodedList<Module*> modules_Queue;

public:

	int coins, stage, city;
	char* city_names[17];

	bool player_2_enabled;

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
	ModuleChooseCity* chooseCityModule;
	ModulePlane* planeModule;
	ModuleStageEnd* stageEndModule;
	ModuleCredits* creditsModule;
	ModuleHighscore* highscoreModule;

	// Other Module nodes
	DoubleNode<Module*>* playerModule_Node;
	DoubleNode<Module*>* entityManagerModule_Node;
	DoubleNode<Module*>* sceneModule_Node;
	DoubleNode<Module*>* titleModule_Node;
	DoubleNode<Module*>* chooseCityModule_Node;
	DoubleNode<Module*>* planeModule_Node;
	DoubleNode<Module*>* stageEndModule_Node;
	DoubleNode<Module*>* creditsModule_Node;
	DoubleNode<Module*>* highscoreModule_Node;

	Application();
	~Application();
	bool Init();
	update_status Update();
	bool CleanUp();

	bool ChangeTo(update_status new_state);

	void Add_Coin();
	bool Lose_Coin();
};