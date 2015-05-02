#include "Module.h"
#include "Globals.h"
#include "Application.h"

#include "Balloon.h"
#include "Stair.h"
#include "Brick.h"
#include "Time_Count.h"

#ifndef __ModuleScene_H__
#define __ModuleScene_H__

struct Hexa_Struct // Balloons and Enemies
{
	unsigned int x;
	unsigned int y;
	unsigned int type;
	unsigned int aux1;
	unsigned int aux2;
	unsigned int aux3;

	void Reset()
	{
		x = 0;
		y = 0;
		type = 0;
		aux1 = 0;
		aux2 = 0;
		aux3 = 0;
	}
	~Hexa_Struct(){}
};

struct Stage_Arrangement
{
	int time_limit;
	int player_pos[4];
	DynArray<Hexa_Struct> bricks;
	DynArray<Hexa_Struct> stairs;
	DynArray<Hexa_Struct> balloons;
	DynArray<Hexa_Struct> enemies;
	~Stage_Arrangement(){}
};

enum Game_State
{
	PLAYING,
	PLAYER_KILLED,
	READY,
	COUNTDOWN,
	GAME_OVER,
	PAUSED

};


class ModuleScene : public Module{
private:
	FILE* level_file;
	void parser(char *line);

public:

	Time_Count* time_count;

	Game_State game_state;
	unsigned int update_counter;
	bool pause_pressed, stage_cleared;

	SDL_Rect ready_rect;
	SDL_Rect ready_source_rect;

	SDL_Rect game_over_rect;
	SDL_Rect game_over_source_rect;

	bool insert_coin_pressed;

	unsigned int current_stage;
	Stage_Arrangement stage_arrangement;

	SDL_Rect background_rect;
	SDL_Rect background_source_rect;

	ModuleScene(Application* app);
	bool Init();
	update_status PreUpdate();
	update_status Update();
	bool CleanUp();

	void Pause_Scene();
	bool Resume_Scene();

	void Print_All_Objects();
	void reset_stage();
	bool load_stage(int stage);

};
#endif