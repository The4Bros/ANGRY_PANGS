#include "Module.h"
#include "Globals.h"
#include "Application.h"


#ifndef __ModuleChooseCity_H__
#define __ModuleChooseCity_H__

class ModuleChooseCity : public Module{
public:
	ModuleChooseCity(Application* app);
	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
};

#endif