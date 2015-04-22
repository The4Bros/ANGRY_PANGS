#include "Module.h"
#include "Globals.h"
#include "Application.h"
#include "Player.h"


#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

class ModulePlayer : public Module{
public:

	Player* player1;
	Player* player2;

	unsigned int player_speed;

	ModulePlayer(Application* app);
	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
};
#endif