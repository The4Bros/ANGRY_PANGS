#include "Module.h"
#include "Globals.h"
#include "Application.h"

#ifndef __ModuleFontManager_H__
#define __ModuleFontManager_H__

class ModuleFontManager : public Module{
public:

	ModuleFontManager(Application* app);
	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
};

#endif