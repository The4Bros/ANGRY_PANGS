#include "Module.h"
#include "Globals.h"
#include "Application.h"

#ifndef __ModuleInput_H__
#define __ModuleInput_H__

class ModuleInput : public Module{
private:
	Application* app;

public:

	const Uint8 *key;

	ModuleInput(Application* app);
	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
};

#endif