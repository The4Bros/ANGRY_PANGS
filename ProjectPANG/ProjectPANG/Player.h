#pragma once

#include "Globals.h"

class Player
{
public:
	SDL_Rect rect;
	SDL_Rect source_rect;

	Player()
	{
		rect = { 0, 0, 32 * SCALE, 32 * SCALE };
		source_rect = {0, 0, 0, 0};
	}
	~Player(){}

	void LeftTrigger();
	void RightTrigger();
	void UpTrigger();
	void DownTrigger();

	virtual bool Init(){ return true; }
	virtual bool CleanUp(){ return true; }
};