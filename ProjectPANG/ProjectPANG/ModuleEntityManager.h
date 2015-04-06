#include "Module.h"
#include "Globals.h"
#include "Application.h"

#ifndef __ModuleEntityManager_H__
#define __ModuleEntityManager_H__

class ModuleEntityManager : public Module{
public:



	ModuleEntityManager(Application* app);
	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	bool colision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
	bool colisionHarpoonBall(int x1, int y1, int r, int x2, int y2, int w2);
};

#endif