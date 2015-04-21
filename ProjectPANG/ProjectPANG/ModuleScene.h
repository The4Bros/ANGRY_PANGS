#include "Module.h"
#include "Globals.h"
#include "Application.h"
#include "Balloon.h"
#include "Stair.h"
#include "Brick.h"

#ifndef __ModuleScene_H__
#define __ModuleScene_H__

#include "Time_Count.h"

struct Tri_Struct // Bricks and Stairs
{
	unsigned int x;
	unsigned int y;
	unsigned int type;
	Tri_Struct()
	{
		x = 0;
		y = 0;
		type = 0;
	}
	~Tri_Struct(){}
};
struct Hexa_Struct // Balloons and Enemies
{
	unsigned int x;
	unsigned int y;
	unsigned int type;
	unsigned int aux1;
	unsigned int aux2;
	unsigned int aux3;
	Hexa_Struct()
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
	std::vector<Tri_Struct> bricks;
	std::vector<Tri_Struct> stairs;
	std::vector<Hexa_Struct> balloons;
	std::vector<Hexa_Struct> enemies;
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
	bool pause_pressed;

	SDL_Rect ready_rect;
	SDL_Rect* ready_source_rect;

	SDL_Rect game_over_rect;
	SDL_Rect* game_over_source_rect;

	bool insert_coin_pressed;

	unsigned int current_stage;
	Stage_Arrangement stage_arrangement;

	SDL_Rect background_rect;
	SDL_Rect* background_source_rect;

	ModuleScene(Application* app);
	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	void Print_All_Objects();
	void reset_stage();
	bool load_stage(int stage);

};
#endif