#pragma once
#include "Application.h"

Application::Application()
{
	returnValue = UPDATE_CONTINUE;

	windowModule = new ModuleWindow(this);
	renderModule = new ModuleRender(this);
	inputModule = new ModuleInput(this);
	texturesModule = new ModuleTextures(this);
	audioModule = new ModuleAudio(this);
	fontManagerModule = new ModuleFontManager(this);

	modules_Queue.push(windowModule);
	modules_Queue.push(renderModule);
	modules_Queue.push(inputModule);
	modules_Queue.push(texturesModule);
	modules_Queue.push(audioModule);
	modules_Queue.push(fontManagerModule);

	sceneModule = NULL;
	playerModule = NULL;
	entityManagerModule = NULL;
	titleModule = NULL;
	tutorialModule = NULL;
	chooseCityModule = NULL;
	planeModule = NULL;
	creditsModule = NULL;
	highscoreModule = NULL;

}

bool Application::Init()
{
	item = modules_Queue.getStart();
	while (item != NULL)
	{
		if (!item->data->Init()){ return false; }
		item = item->next;
	}
	return true;
}

Application::~Application()
{
	modules_Queue.clear();
}

update_status Application::Update()
{
	item = modules_Queue.getStart(); // ------------PreUpdate------------
	while (item != NULL)
	{
		returnValue = item->data->PreUpdate();
		switch (returnValue)
		{
		case UPDATE_CONTINUE:
			item = item->next;
			break;
		case UPDATE_PAUSE:
			// check for un-pause or close window -> window updates + input updates
			break;
		case UPDATE_ERROR:
			return returnValue;
		case UPDATE_STOP:
			return returnValue;
		}
	}

	item = modules_Queue.getStart(); // ------------Update------------
	while (item != NULL)
	{
		returnValue = item->data->Update();
		switch (returnValue)
		{
		case UPDATE_CONTINUE:
			item = item->next;
			break;
		case UPDATE_PAUSE:
			break;
			//pause managed
		case UPDATE_ERROR:
			return returnValue;
		case UPDATE_STOP:
			return returnValue;
		}
	}

	item = modules_Queue.getStart(); // ------------PostUpdate------------
	while (item != NULL)
	{
		returnValue = item->data->PostUpdate();
		switch (returnValue)
		{
		case UPDATE_CONTINUE:
			item = item->next;
			break;
		case UPDATE_PAUSE:
			break;
			//pause managed
		case UPDATE_ERROR:
			return returnValue;
		case UPDATE_STOP:
			return returnValue;
		}
	}
	/*
	//If frame finished early
	int frameTicks = capTimer.getTicks();
	if (frameTicks < TICKS_PER_FRAME)
	{
		//Wait remaining time
		SDL_Delay(TICKS_PER_FRAME - frameTicks);
	}
	*/

	return returnValue;
}

bool Application::CleanUp()
{
	item = modules_Queue.getLast();
	while (item != NULL)
	{
		if (!item->data->CleanUp()){ return false; }
		item = item->previous;
	}
	modules_Queue.clear();
	return true;
}

bool Application::ChangeTo(update_status new_state)
{
	// Clear Unnecessary Modules
	modules_Queue.ReduceTo(6);

	switch (new_state)
	{
	case CHANGE_TO_TITLE:

		if (titleModule == NULL)
		{
			titleModule = new ModuleTitle(this);
			titleModule->Init();
		}
		modules_Queue.push(titleModule);
		break;

	case CHANGE_TO_TUTORIAL:

		if (tutorialModule == NULL)
		{
			tutorialModule = new ModuleTutorial(this);
			tutorialModule->Init();
		}
		modules_Queue.push(tutorialModule);
		break;

	case CHANGE_TO_CHOOSE_CITY:

		if (chooseCityModule == NULL)
		{
			chooseCityModule = new ModuleChooseCity(this);
			chooseCityModule->Init();
		}
		modules_Queue.push(chooseCityModule);
		break;

	case CHANGE_TO_PLAY:

		if (sceneModule == NULL)
		{
			sceneModule = new ModuleScene(this);
			sceneModule->Init();
		}
		modules_Queue.push(sceneModule);

		if (playerModule == NULL)
		{
			playerModule = new ModulePlayer(this);
			playerModule->Init();
		}
		modules_Queue.push(playerModule);

		if (entityManagerModule == NULL)
		{
			entityManagerModule = new ModuleEntityManager(this);
			entityManagerModule->Init();
		}
		modules_Queue.push(entityManagerModule);
		break;

	case CHANGE_TO_MAP_PLANE:

		if (planeModule == NULL)
		{
			planeModule = new ModulePlane(this);
			planeModule->Init();
		}
		modules_Queue.push(planeModule);
		break;

	case CHANGE_TO_CREDITS:

		if (creditsModule == NULL)
		{
			creditsModule = new ModuleCredits(this);
			creditsModule->Init();
		}
		modules_Queue.push(creditsModule);
		break;

	case CHANGE_TO_HIGHSCORE:

		if (highscoreModule == NULL)
		{
			highscoreModule = new ModuleHighscore(this);
			highscoreModule->Init();
		}
		modules_Queue.push(highscoreModule);
		break;

	}
	
	return true;
}

