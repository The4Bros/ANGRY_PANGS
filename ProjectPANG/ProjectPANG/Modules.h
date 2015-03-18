

#include "DoubleNodedStack.h"






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



class ApplicationModule : public Module{
private:
	DoubleNodedStack<Module*> modules_Stack;

public:

	ApplicationModule()
	{
		DoubleNodedStack<Module*> modules_Stack = new DoubleNodedStack<Module*>();
	}
	bool Init()
	{
		DoubleNodedStack<Module*>* item = modules_Stack.start();
		while (item)
		{
			if (!item->data->Init()){ return false; }
			item = item->next();
		}
		return true;

	}
	int Update()
	{
		DoubleNodedStack<Module*>* item = modules_Stack.start();
		while (item)
		{
			item->data->Update();
			item = item->next();
		}
	}

	bool CleanUp()
	{
		DoubleNodedStack<Module*>* item = modules_Stack.getLast();
		while (item)
		{
			if (!item->data->CleanUp()){ return false; }
			item = item->previous();
		}
		return true;
	}
};






class Module
{
public:
	virtual bool Init(){ return true; }
	virtual int Update(){ return 2; }
	virtual bool CleanUp(){ return true; }
};


class WindowModule : public Module{
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

class SceneModule : public Module{
public:
	bool Init(){ return true; }
	int Update(){ return 2; }
	bool CleanUp(){ return true; }
}; //map

class EntityManagerModule : public Module{
public:
	bool Init(){ return true; }
	int Update(){ return 2; }
	bool CleanUp(){ return true; }
}; //(player, enemies)

class ConfigurationModule : public Module{
public:
	bool Init(){ return true; }
	int Update(){ return 2; }
	bool CleanUp(){ return true; }
};

class RenderModule : public Module{
public:
	bool Init(){ return true; }
	int Update(){ return 2; }
	bool CleanUp(){ return true; }
};

class AudioModule : public Module{
public:
	bool Init(){ return true; }
	int Update(){ return 2; }
	bool CleanUp(){ return true; }
};

class InputModule : public Module{
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






