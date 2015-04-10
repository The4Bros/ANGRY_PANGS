#include "Globals.h"
#include "Application.h"
#include "Particles.h"

#ifndef __Balloon_H__
#define __Balloon_H__

enum BALL_COLOR
{
	RED,
	BLUE,
	GREEN
};


class Balloon
{
	Application* app;

	unsigned int size;
	BALL_COLOR color;

	SDL_Rect rect;
	SDL_Rect* source_rect;
	Particles* particles;

	Balloon();
	~Balloon(){}

	void Update();
	void Hit();
	// particles->Play();

};
#endif