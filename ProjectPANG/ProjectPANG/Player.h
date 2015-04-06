#include "Globals.h"
#include "Application.h"
#include "Harpoon.h"

#ifndef __Player_H__
#define __Player_H__

enum PlayerState
{
	LEFT,
	RIGHT,
	DOWN,
	UP,
	STILL,
	SHOOT
};

class Player
{
public:
	Application* app;
	SDL_Rect character_rect;
	SDL_Rect character_const_source_rect;
	const SDL_Rect* character_const_rect;

	Harpoon* harpoon;

	unsigned int score, lives, update_counter;
	PlayerState state;
	bool alive;

	Player(Application* app, bool player1);
	~Player(){}

	void LeftTrigger();
	void RightTrigger();
	void UpTrigger();
	void DownTrigger();
	void Shoot();
	void Still();
};
#endif