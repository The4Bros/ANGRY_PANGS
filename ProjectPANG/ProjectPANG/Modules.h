

#include "Globals.h"


#include "SDL_image/include/SDL_image.h"
#pragma comment( lib, "SDL_image/libx86/SDL2_image.lib" )

#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

class WindowModule;
class RenderModule;
class InputModule;
class EntityManagerModule; //(player, enemies)
class AudioModule;
class ConfigurationModule;
class TextureManagerModule;
class FontManagerModule;
class PersistentDataModule;
class NetworkModule;
class SceneModule; //map






class Module
{
	/*
protected:
	//App Module:
	DoubleNodedStack<Module*>* modules_Stack;
	DoubleNode<Module*>* item;

	//Window Module:
	SDL_Event* mainEvent;
	SDL_Window* window;
	Uint32 windowFlags;

	//Renderer Module:
	SDL_Renderer* renderer;
	Uint32 rendererFlags;

	//Input Module:
	const Uint8 *key;

	//Entity Manager Module:



	// Module:



	// Module:



	//Texture Manager Module:



	//Configuration Module:
	


	//Scene Module:



	//Network Module:



	//Persistent Data Module:


	*/



public:
	Module(){}
	virtual main_states Init(){ return MAIN_UPDATE; }
	virtual update_status Update(){ return UPDATE_CONTINUE; }
	virtual main_states CleanUp(){ return MAIN_EXIT; }

	/*
	modules:

	window
	persistent data
	scene(map)
	entity manager(player, enemies)
	configuration
	render
	audio
	input
	network
	texture manager
	font manager
	*/
};


class ApplicationModule{
private:
	DoubleNodedStack<Module*>* modules_Stack;
	DoubleNode<Module*>* item;

public:
	//Window Module:
	WindowModule* windowModule;
	RenderModule* renderModule;
	InputModule* inputModule;

	main_states Init()
	{
		modules_Stack = new DoubleNodedStack<Module*>();
		
		inputModule = new InputModule(this);
		renderModule = new RenderModule(this);
		windowModule = new WindowModule(this);
		/*
		modules_Stack.push(new PersistentDataModule);
		modules_Stack.push(new NetworkModule);
		modules_Stack.push(new SceneModule);
		*/

		//modules_Stack->push(new ConfigurationModule(this));
		//modules_Stack->push(new TextureManagerModule(this));
		//modules_Stack->push(new FontManagerModule(this));
		//modules_Stack->push(new AudioModule(this));
		//modules_Stack->push(new EntityManagerModule(this));
		modules_Stack->push(inputModule);
		modules_Stack->push(renderModule);
		modules_Stack->push(windowModule);

		item = modules_Stack->start();

		main_states returnValue;
		while (item)
		{
			returnValue = item->getData()->Init();
			item = item->getNext();
		}
		return true;
	}
	main_states AppUpdate()
	{
		item = modules_Stack->start();
		update_status returnValue;
		while (item)
		{
			returnValue = item->getData()->Update();
			switch (returnValue)
			{
			case UPDATE_CONTINUE:
				item = item->getNext();
				break;
			case UPDATE_PAUSE:
				//pause managed
			case UPDATE_STOP:
				return MAIN_FINISH;

			case UPDATE_ERROR:
				return MAIN_ERROR;
			}
		}
		return MAIN_UPDATE;
	}
	bool CleanUp()
	{
		item = modules_Stack->getLast();
		while (item)
		{
			if (!item->getData()->CleanUp()){ return false; }
			item = item->getPrevious();
		}
		delete item;
		delete[] modules_Stack;
		return true;
	}
};


class WindowModule : public Module{
private:
	ApplicationModule* app;
	Uint32 windowFlags;
	SDL_Event* mainEvent;

public:

	SDL_Window* window;

	WindowModule(ApplicationModule* const app)
	{
		this->app = app;
	}
	main_states Init()
	{
		windowFlags = SDL_WINDOW_SHOWN;
		window = SDL_CreateWindow("PANG", 80, 80, 600, 400, windowFlags);
		if (window == NULL){ return MAIN_ERROR; }
		SDL_Event* MAIN_EVENT = new SDL_Event();
		if (MAIN_EVENT == NULL){ return MAIN_ERROR; }
		return MAIN_UPDATE;
	}
	update_status Update()
	{
		SDL_PollEvent(mainEvent);
		if (mainEvent->type == SDL_QUIT){ return UPDATE_STOP; }

		//manage window size and properties HowTo:
		/*
		int SDL_GetCurrentDisplayMode(int displayIndex, SDL_DisplayMode &current);

		SDL_DisplayMode current;
		for(i = 0; i < SDL_GetNumVideoDisplays(); ++i){
		int should_be_zero = SDL_GetCurrentDisplayMode(i, &current);
		if(should_be_zero != 0)
		SDL_Log("Could not get display mode for video display #%d: %s", i, SDL_GetError());
		else
		SDL_Log("Display #%d: current display mode is %dx%dpx @ %dhz. \n", i, current.w, current.h, current.refresh_rate);
		}
		*/

		return UPDATE_CONTINUE;
	}
	main_states CleanUp()
	{
		delete[] mainEvent;
		delete &windowFlags;
		SDL_DestroyWindow(window);
	}
};

class RenderModule : public Module{
private:
	ApplicationModule* app;
	Uint32 rendererFlags;

public:

	SDL_Renderer* renderer;

	RenderModule(ApplicationModule* const app)
	{
		this->app = app;
	}
	bool Init()
	{
		SDL_Renderer* renderer = SDL_CreateRenderer(app->windowModule->window, -1, rendererFlags);
	}
	update_status Update()
	{
		return UPDATE_CONTINUE;
	}
	bool CleanUp()
	{
		delete &rendererFlags;
		SDL_DestroyRenderer(app->renderModule->renderer);
		return true;
	}
};

class InputModule : public Module{
private:
	ApplicationModule* app;

protected:
	const Uint8 *key;

public:

	InputModule(ApplicationModule* const app)
	{
		this->app = app;
	}
	bool Init()
	{
		return true;
	}
	update_status Update()
	{
		key = SDL_GetKeyboardState(NULL);

		if (key[SDLK_ESCAPE]){ return UPDATE_STOP; }




		if (app->inputModule->key[SDLK_LEFT]){ LOG("\n LEFT pressed"); }
		if (app->inputModule->key[SDLK_RIGHT]){ LOG("\n RIGHT pressed"); }
		if (app->inputModule->key[SDLK_UP]){ LOG("\n UP pressed"); }
		if (app->inputModule->key[SDLK_DOWN]){ LOG("\n DOWN pressed"); }
		if (app->inputModule->key[SDLK_SPACE]){ LOG("\n SPACE pressed"); }

		return UPDATE_CONTINUE;

	}
	bool CleanUp()
	{
		delete key;
	}
};




class EntityManagerModule : public Module{
public:
	bool Init()
	{
		//load players and enemies
	}
	update_status Update(){ return UPDATE_CONTINUE; }
	bool CleanUp(){ return true; }
}; //(player, enemies)
class AudioModule : public Module{
public:
	bool Init(){ return true; }
	update_status Update(){ return UPDATE_CONTINUE; }
	bool CleanUp(){ return true; }
};
class ConfigurationModule : public Module{
public:
	bool Init(){ return true; }
	update_status Update(){ return UPDATE_CONTINUE; }
	bool CleanUp(){ return true; }
};
class TextureManagerModule : public Module{
public:
	bool Init(){ return true; }
	update_status Update(){ return UPDATE_CONTINUE; }
	bool CleanUp(){ return true; }
};
class FontManagerModule : public Module{
public:
	bool Init(){ return true; }
	update_status Update(){ return UPDATE_CONTINUE; }
	bool CleanUp(){ return true; }
};
class PersistentDataModule : public Module{
public:
	bool Init(){ return true; }
	update_status Update(){ return UPDATE_CONTINUE; }
	bool CleanUp(){ return true; }
};
class NetworkModule : public Module{
public:
	bool Init(){ return true; }
	update_status Update(){ return UPDATE_CONTINUE; }
	bool CleanUp(){ return true; }
};
class SceneModule : public Module{
public:
	bool Init(){ return true; }
	update_status Update(){ return UPDATE_CONTINUE; }
	bool CleanUp(){ return true; }
}; //map




