#include "Globals.h"
#include "Application.h"

#ifndef __Particles_H__
#define __Particles_H__


class Particles
{
public:
	Application* app;

	bool alive;
	SDL_Rect rect;
	unsigned int quantity, update_counter, source_index;

	Particles(Application* app, unsigned int type, int x, int y);
	~Particles(){}

	void Update();
	void Print();

};
#endif