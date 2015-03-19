

#include "Globals.h"


#include "SDL_image/include/SDL_image.h"
#pragma comment( lib, "SDL_image/libx86/SDL2_image.lib" )

#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

class Module
{
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






public:
	virtual bool Init(){ return true; }
	virtual int Update(){ return 0; }
	virtual bool CleanUp(){ return true; }

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






class ApplicationModule : public Module{
/*private:
	DoubleNodedStack<Module*>* modules_Stack;
	DoubleNode<Module*>* item;*/

public:

	bool Init()
	{
		DoubleNodedStack<Module*>* modules_Stack = new DoubleNodedStack<Module*>();
		DoubleNode<Module*>* item;

		/*
		modules_Stack.push(new PersistentDataModule);
		modules_Stack.push(new NetworkModule);
		modules_Stack.push(new SceneModule);
		*/

		modules_Stack->push(new ConfigurationModule(this));
		modules_Stack->push(new TextureManagerModule(this));
		modules_Stack->push(new FontManagerModule(this));
		modules_Stack->push(new AudioModule(this));
		modules_Stack->push(new EntityManagerModule(this));
		modules_Stack->push(new InputModule(this));
		modules_Stack->push(new RenderModule(this));
		modules_Stack->push(new WindowModule(this));


		item = modules_Stack->start();
		while (item)
		{
			if (!item->getData()->Init()){ return false; }
			item = item->getNext();
		}
		return true;
	}
	int Update()
	{
		item = modules_Stack->start();
		while (item)
		{
			if (!item->getData()->Update()){ return false; }
			item = item->getNext();
		}
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
public:
	

	bool Init()
	{
		windowFlags = SDL_WINDOW_SHOWN;
		window = SDL_CreateWindow("PANG", 80, 80, 600, 400, windowFlags);
		SDL_Event* MAIN_EVENT = new SDL_Event();
	}
	int Update()
	{
		SDL_PollEvent(mainEvent);
		if (mainEvent->type == SDL_QUIT){ return MAIN_FINISH; }

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

		return MAIN_UPDATE;
	}
	bool CleanUp()
	{
		delete[] mainEvent;
		delete &windowFlags;
		SDL_DestroyWindow(window);
	}
};

class RenderModule : public Module{
public:
	bool Init()
	{
		SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, rendererFlags);
	}
	int Update()
	{

	}
	bool CleanUp()
	{
		SDL_DestroyRenderer(renderer);
		return true;
	}
};

class InputModule : public Module{
public:
	bool Init()
	{
		const Uint8 *key = SDL_GetKeyboardState(NULL);
	}
	int Update()
	{
		key = SDL_GetKeyboardState(NULL);
		if (key[SDLK_LEFT]){ LOG("\n LEFT pressed"); }
		if (key[SDLK_RIGHT]){ LOG("\n RIGHT pressed"); }
		if (key[SDLK_UP]){ LOG("\n UP pressed"); }
		if (key[SDLK_DOWN]){ LOG("\n DOWN pressed"); }
		if (key[SDLK_SPACE]){ LOG("\n SPACE pressed"); }
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
	int Update(){ return 2; }
	bool CleanUp(){ return true; }
}; //(player, enemies)





class AudioModule : public Module{
public:
	bool Init(){ return true; }
	int Update(){ return 2; }
	bool CleanUp(){ return true; }
};





class ConfigurationModule : public Module{
public:
	bool Init(){ return true; }
	int Update(){ return 2; }
	bool CleanUp(){ return true; }
};









class TextureManagerModule : public Module{
public:
	bool Init(){ return true; }
	int Update(){ return 2; }
	bool CleanUp(){ return true; }
};
class FontManagerModule : public Module{
public:
	bool Init(){ return true; }
	int Update(){ return 2; }
	bool CleanUp(){ return true; }
};

class PersistentDataModule : public Module{
public:
	bool Init(){ return true; }
	int Update(){ return 2; }
	bool CleanUp(){ return true; }
};
class NetworkModule : public Module{
public:
	bool Init(){ return true; }
	int Update(){ return 2; }
	bool CleanUp(){ return true; }
};
class SceneModule : public Module{
public:
	bool Init(){ return true; }
	int Update(){ return 2; }
	bool CleanUp(){ return true; }
}; //map




