#include "Module.h"
#include "Globals.h"
#include "Application.h"

#ifndef __ModuleScene_H__
#define __ModuleScene_H__

#include "Time_Count.h"
#include <string.h>

struct Stage_Arrangement
{
	int time_limit;
	int player_pos[4];
	int* balloons;
	int* bricks;
	int* enemies;
	int* stairs;

	inline Stage_Arrangement()
	{
		time_limit = 0;
		player_pos[0] = 0;
		player_pos[1] = 0;
		player_pos[2] = 0;
		player_pos[3] = 0;
		balloons = NULL;
		bricks = NULL;
		enemies = NULL;
		stairs = NULL;
	}

	~Stage_Arrangement(){}
};




class ModuleScene : public Module{
public:

	Time_Count* time_count;

	FILE* level_file;

	unsigned int current_stage;
	Stage_Arrangement stage_arrangement;

	SDL_Rect background_rect;
	SDL_Rect background_const_source_rect;
	const SDL_Rect* background_const_rect;

	ModuleScene(Application* app);
	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	void reset_stage();
	void load_stage(int stage);

};
#endif