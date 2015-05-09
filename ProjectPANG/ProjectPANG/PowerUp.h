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

	bool falling;

	unsigned int quantity, source_index;

	PowerUp(Application* app, int position_in_list, unsigned int type, unsigned int x, unsigned int y);
	~PowerUp(){}

	void Update();
	void Print();
	void Kill();

	bool Check_Collision_Bricks();
	bool Check_Collision_Players();
	bool Check_Collision_Harpoons();

};

#endif