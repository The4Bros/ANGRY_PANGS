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
	SHOOT_LEFT,
	SHOOT_RIGHT,
};

enum Weapon
{
	WEAPON_DOUBLE_HARPOON,
	WEAPON_HARPOON,
	WEAPON_GRAPPLE,
	WEAPON_SHOTGUN
};

class Player
{
public:
	Application* app;

	SDL_Rect rect;
	SDL_Rect* source_rect[25];
	int source_index;

	Harpoon* harpoon[2];
	Weapon current_weapon;

	unsigned int score, lives, update_counter, shoot_update_counter;
	PlayerState state;
	bool alive; // , shoot_key_pressed;

	Player(Application* app, bool player1);
	~Player(){}

	void LeftTrigger();
	void RightTrigger();
	void UpTrigger();
	void DownTrigger();
	void Shoot();
	void Still();

	void Update();
	void setPos(unsigned int x, unsigned int y);

};
#endif