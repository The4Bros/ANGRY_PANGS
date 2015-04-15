#include "Globals.h"
#include "Application.h"
#include "Particles.h"

#ifndef __Stair_H__
#define __Stair_H__

class Stair
{
public:
	Application* app;

	SDL_Rect rect;
	DynArray<SDL_Rect>* rects;

	Stair(Application* app, unsigned int x, unsigned int y, unsigned int size);
	~Stair(){}

	void Print();

	void Reset(unsigned int x, unsigned int y, unsigned int size);

};
#endif