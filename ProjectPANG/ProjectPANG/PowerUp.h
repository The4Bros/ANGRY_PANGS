#include "Globals.h"
#include "Application.h"

#ifndef __Power_Up_H__
#define __Power_Up_H__

class PowerUp
{
public:
	Application* app;

	SDL_Rect rect;
	int position_in_list;
	int power_up_initial_time;
	int power_up_max_time;
	bool falling;

	unsigned int quantity, source_index;

	PowerUp(Application* app, int position_in_list, unsigned int type, unsigned int x, unsigned int y);
	~PowerUp(){}

	void Update();
	void Print();
	void Kill();
	void Blink_PowerUp_Sprite();

	bool Check_Collision_Bricks();
	
};

#endif