#include "Globals.h"
#include "Application.h"
#include "Particles.h"

#ifndef __Balloon_H__
#define __Balloon_H__

enum BALL_TYPE
{
	RED_1,
	RED_2,
	RED_3,
	RED_4,

	BLUE_1,
	BLUE_2,
	BLUE_3,
	BLUE_4,

	GREEN_1,
	GREEN_2,
	GREEN_3,
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
	int bounce_height = 100;// ?
	int bounce_height_start = 100;// ?
    int gravity_strenght = 1;
	
	int gravity = 2;
	int gravity_start = 2;
	int horizontal_speed = 2;
	BALL_TYPE type;
	
	BALLOON_STATE_VERTICAL state_balloon_V;
	BALLOON_STATE_HORIZONTAL state_balloon_H;
	BOOL alive_balloon;
	BOOL change_movement; // true if the ball has to change its direction, change it on Hit()
	SDL_Rect rect;

	Balloon(Application* app, int x, int y, int type, int max_height);
	~Balloon(){}

	void Update();
	
	void Print();

	void Hit();
	// particles->PushBack(x, y, type);

	void Reset(unsigned int x, unsigned int y, unsigned int type, unsigned int max_height);


};
#endif