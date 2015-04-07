#include "Module.h"
#include "Globals.h"
#include "Application.h"


#ifndef __ModuleTutorial_H__
#define __ModuleTutorial_H__

class ModuleTutorial : public Module{
public:
	ModuleTutorial(Application* app);
	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
};

#endif