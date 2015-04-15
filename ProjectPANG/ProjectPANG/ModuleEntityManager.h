#include "Module.h"
#include "Globals.h"
#include "Application.h"

#ifndef __ModuleEntityManager_H__
#define __ModuleEntityManager_H__

class ModuleEntityManager : public Module{
public:

	unsigned int balloon_speed;

	ModuleEntityManager(Application* app);
	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	bool colision(SDL_Rect* rect_1, SDL_Rect* rect_2);
	bool colisionHarpoonBall(SDL_Rect* rect_1, SDL_Rect* rect_2);
};

#endif