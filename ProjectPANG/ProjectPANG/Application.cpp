#pragma once
#include "Application.h"

Application::Application()
{
	returnValue = UPDATE_CONTINUE;

	windowModule = new ModuleWindow(this);
	renderModule = new ModuleRender(this);
	inputModule = new ModuleInput(this);
	texturesModule = new ModuleTextures(this);
	sceneModule = new ModuleScene(this);
	entityManagerModule = new ModuleEntityManager(this);
	audioModule = new ModuleAudio(this);
	fontManagerModule = new ModuleFontManager(this);

	AddModule(windowModule);
	AddModule(renderModule);
	AddModule(inputModule);
	AddModule(texturesModule);
	AddModule(sceneModule);
	AddModule(entityManagerModule);
	AddModule(audioModule);
	AddModule(fontManagerModule);
}

bool Application::Init()
{
	item = modules_Queue.getStart();
	while (item)
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
	return returnValue;
}

bool Application::CleanUp()
{
	item = modules_Queue.getLast();
	while (item)
	{
		if (!item->data->CleanUp()){ return false; }
		item = item->previous;
	}
	modules_Queue.clear();
	return true;
}

void Application::AddModule(Module* mod)
{
	modules_Queue.push(mod);
}