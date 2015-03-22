#include "Module.h"
#include "Globals.h"
#include "Application.h"



#ifndef __ModuleAudio_H__
#define __ModuleAudio_H__

class ModuleAudio : public Module{
public:
	ModuleAudio(Application* app);
	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
};

#endif