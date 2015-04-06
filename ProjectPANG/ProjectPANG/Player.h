#pragma once

#include "Globals.h"

class Player
{
public:
	SDL_Rect character_rect;
	SDL_Rect character_const_source_rect;
	const SDL_Rect* character_const_rect;

	Player()
	{
		character_rect = { 0, 0, 32, 32 };
		character_const_source_rect = { 0, 0, 0, 0 };
	}
	~Player(){}

	void LeftTrigger();
	void RightTrigger();
	void UpTrigger();
	void DownTrigger();

	virtual bool Init(){ return true; }
	virtual bool CleanUp(){ return true; }
};