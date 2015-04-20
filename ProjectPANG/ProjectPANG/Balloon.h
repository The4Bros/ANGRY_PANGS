#include "Globals.h"
#include "Application.h"
#include "Particles.h"
#include "Module.h"

#ifndef __Balloon_H__
#define __Balloon_H__

enum BALL_TYPE
{
	RED_1,
	BLUE_1,
	GREEN_1,

	RED_2,
	BLUE_2,
	GREEN_2,

	RED_3,
	BLUE_3,
	GREEN_3,

	RED_4,
	BLUE_4,
	GREEN_4


};
enum BALLOON_STATE_VERTICAL
{
	BALLOON_UP,
	BALLOON_DOWN


};

enum BALLOON_STATE_HORIZONTAL
{
	BALLOON_LEFT,
	BALLOON_RIGHT


};

class Balloon
{
public:

	Application* app;

	unsigned int max_height;
	unsigned int position_in_list;
	int gravity;
	int horizontal_speed;
	int gravity_aux;

	BALL_TYPE type;
	BALLOON_STATE_VERTICAL state_balloon_V;
	BALLOON_STATE_HORIZONTAL state_balloon_H;
	BOOL change_movement_V;// true if the ball has to change its direction, change it on Hit()
	BOOL change_movement_H;
	SDL_Rect rect;
	


	Balloon(Application* app, int x, int y, int type, int max_height);
	~Balloon(){}

	void Update();
	void Print();
	

	void Hit();
	// particles->PushBack(x, y, type);

	void Check_Collision_Balloon_Players();
	bool Deep_Check_Collision_Balloon_Player1();
	void Deep_Check_Collision_Balloon_Player2();


	void Check_Collision_Balloon_Brick_Vertical();
	void Check_Collision_Balloon_Brick_Horizontal();

	void Reset(unsigned int x, unsigned int y, unsigned int type, unsigned int max_height);


};
#endif