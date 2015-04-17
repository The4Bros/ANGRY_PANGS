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
#include "ModuleTitle.h"
#include "ModuleTutorial.h"
#include "ModuleChooseCity.h"
#include "ModulePlane.h"
#include "ModuleCredits.h"
#include "ModuleHighscore.h"




class Application
{
private:
	DoubleNodedQueue<Module*> modules_Queue;
	DoubleNode<Module*>* item;
	update_status returnValue;

public:

	int current_time;
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