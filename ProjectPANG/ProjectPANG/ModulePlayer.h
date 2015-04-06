#include "Module.h"
#include "Globals.h"
#include "Classes.h"
#include "Application.h"
#include "Player1.h"
#include "Player2.h"

#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

class ModulePlayer : public Module{
public:

	Player1 player1;
	Player2 player2;

	ModulePlayer(Application* app);
	bool Init();
	update_status PreUpdate();
	update_status Update();

	player1.LeftTrigger();

	update_status PostUpdate();
	bool CleanUp();
};
#endif