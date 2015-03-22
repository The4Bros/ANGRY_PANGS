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

	modules_Stack.push(windowModule);
	modules_Stack.push(renderModule);
	modules_Stack.push(inputModule);
	modules_Stack.push(texturesModule);
	modules_Stack.push(sceneModule);
	modules_Stack.push(entityManagerModule);
	modules_Stack.push(audioModule);
	modules_Stack.push(fontManagerModule);
}

bool Application::Init()
{
	item = modules_Stack.start();
	while (item)
	{
		if (!item->data->Init()){ return false; }
		item = item->next;
	}
	return true;
}

Application::~Application()
{
	delete[] windowModule;
	delete[] renderModule;
	delete[] inputModule;
	delete[] texturesModule;
	delete[] sceneModule;
	delete[] entityManagerModule;
	delete[] audioModule;
	delete[] fontManagerModule;
}

update_status Application::PreUpdate()
{
	item = modules_Stack.start();
	while (item != NULL)
	{
		returnValue = item->data->PreUpdate();
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

update_status Application::Update()
{
	item = modules_Stack.start();
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
	return returnValue;
}

update_status Application::PostUpdate()
{
	item = modules_Stack.start();
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
	item = modules_Stack.getLast();
	while (item)
	{
		if (!item->data->CleanUp()){ return false; }
		item = item->previous;
	}
	modules_Stack.clear();
	return true;
}
