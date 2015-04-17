#include "Globals.h"
#include "Application.h"

#ifndef __Particles_H__
#define __Particles_H__

enum Particle_Type
{
	ENEMY_HIT,
	PLAYER_SHOOT,



	BALL_SIZE_1,
	BALL_SIZE_2,
	BALL_SIZE_3,
	BALL_SIZE_4
};

class Particles
{
public:
	Application* app;

	bool alive;
	SDL_Rect rect;
	SDL_Rect* source_rect[5];

	int quantity;

	Particles(Application* app, unsigned int type,  int x,  int y);
	~Particles(){}

	void Update();

};
#endif