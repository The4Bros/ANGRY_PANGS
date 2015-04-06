#pragma once

#include "Globals.h"

enum Direction
{
	LEFT,
	RIGHT,
	DOWN,
	UP
};

class Player
{
public:
	SDL_Rect character_rect;
	SDL_Rect character_const_source_rect;
	const SDL_Rect* character_const_rect;

	unsigned int score, lives;
	Direction direction;
	bool alive;


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