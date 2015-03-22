#include "Module.h"
#include "Globals.h"
#include "Application.h"

#ifndef __ModuleTextures_H__
#define __ModuleTextures_H__

class ModuleTextures : public Module{
public:
	ModuleTextures(Application* app);
	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
};

#endif