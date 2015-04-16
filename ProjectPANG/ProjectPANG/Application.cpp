#pragma once
#include "Application.h"

Application::Application()
{
	returnValue = UPDATE_CONTINUE;

	windowModule = NULL;
	renderModule = NULL;
	inputModule = NULL;
	texturesModule = NULL;
	audioModule = NULL;
	fontManagerModule = NULL;

	playerModule = NULL;
	entityManagerModule = NULL;
	sceneModule = NULL;
	titleModule = NULL;
	tutorialModule = NULL;
	chooseCityModule = NULL;
	planeModule = NULL;
	creditsModule = NULL;
	highscoreModule = NULL;

}

bool Application::Init()
{

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


	item = modules_Queue.getStart();
	while (item != NULL)
	{
		if (!item->data->Init()){ return false; }
		item = item->next;
	}

	current_time = 0;
	time(&timer);

	return true;
}

Application::~Application()
{
	modules_Queue.clear();
}

update_status Application::Update()
{
	// UPDATE TIME COUNTER
	if (difftime(time(NULL), timer) >= 1){ current_time++; }

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
		default:
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
		default:
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
		default:
			return returnValue;
		}
	}

	return returnValue;
}

bool Application::CleanUp()
{
	modules_Queue.ReduceTo(6);

	if (playerModule != NULL){        if (playerModule->CleanUp() == false) {        return false; } }
	if (entityManagerModule != NULL){ if (entityManagerModule->CleanUp() == false) { return false; } }
	if (sceneModule != NULL){         if (sceneModule->CleanUp() == false) {         return false; } }
	if (titleModule != NULL){         if (titleModule->CleanUp() == false) {         return false; } }
	if (tutorialModule != NULL){      if (tutorialModule->CleanUp() == false) {      return false; } }
	if (chooseCityModule != NULL){    if (chooseCityModule->CleanUp() == false) {    return false; } }
	if (planeModule != NULL){         if (planeModule->CleanUp() == false) {         return false; } }
	if (creditsModule != NULL){       if (creditsModule->CleanUp() == false) {       return false; } }
	if (highscoreModule != NULL){     if (highscoreModule->CleanUp() == false) {     return false; } }

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
			if (titleModule->Init() == false) { return false; }
		}
		modules_Queue.push(titleModule);
		break;

	case CHANGE_TO_TUTORIAL:

		if (tutorialModule == NULL)
		{
			tutorialModule = new ModuleTutorial(this);
			if (tutorialModule->Init() == false) { return false; }
		}
		modules_Queue.push(tutorialModule);
		break;

	case CHANGE_TO_CHOOSE_CITY:

		if (chooseCityModule == NULL)
		{
			chooseCityModule = new ModuleChooseCity(this);
			if (chooseCityModule->Init() == false) { return false; }
		}
		modules_Queue.push(chooseCityModule);
		break;

	case CHANGE_TO_PLAY:

		if (playerModule == NULL)
		{
			playerModule = new ModulePlayer(this);
			if (playerModule->Init() == false) { return false; }
		}
		modules_Queue.push(playerModule);

		if (entityManagerModule == NULL)
		{
			entityManagerModule = new ModuleEntityManager(this);
			if (entityManagerModule->Init() == false) { return false; }
		}
		modules_Queue.push(entityManagerModule);

		if (sceneModule == NULL)
		{
			sceneModule = new ModuleScene(this);
			if (sceneModule->Init() == false) { return false; }
		}
		modules_Queue.push(sceneModule);
		break;

	case CHANGE_TO_MAP_PLANE:

		if (planeModule == NULL)
		{
			planeModule = new ModulePlane(this);
			if (planeModule->Init() == false) { return false; }
		}
		modules_Queue.push(planeModule);
		break;

	case CHANGE_TO_CREDITS:

		if (creditsModule == NULL)
		{
			creditsModule = new ModuleCredits(this);
			if (creditsModule->Init() == false) { return false; }
		}
		modules_Queue.push(creditsModule);
		break;

	case CHANGE_TO_HIGHSCORE:

		if (highscoreModule == NULL)
		{
			highscoreModule = new ModuleHighscore(this);
			if (highscoreModule->Init() == false) { return false; }
		}
		modules_Queue.push(highscoreModule);
		break;

	}
	
	return true;
}

void  Application::Reset_Time()
{
	current_time = 0;
}