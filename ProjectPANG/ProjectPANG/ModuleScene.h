#include "Module.h"
#include "Globals.h"
#include "Application.h"

#ifndef __ModuleScene_H__
#define __ModuleScene_H__

#include "Time_Count.h"
#include <string.h>
#include <stdio.h>
#include <vector>
#include <iterator>

struct Stage_Arrangement
{
	int time_limit;
	int player_pos[4];
	std::vector<int[4]> balloons, bricks, enemies, stairs;

	~Stage_Arrangement(){}
};




class ModuleScene : public Module{
private:
	FILE* level_file;

	void parser(char *line);
	int fast_atoi(const char * str);


public:

	Time_Count* time_count;

	int current_stage;
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
	bool load_stage(int stage);

};
#endif