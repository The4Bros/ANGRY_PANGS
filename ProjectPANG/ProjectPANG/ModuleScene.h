#include "Module.h"
#include "Globals.h"
#include "Application.h"

#ifndef __ModuleScene_H__
#define __ModuleScene_H__

class ModuleScene : public Module{
public:
	ModuleScene(Application* app);
	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
};
#endif