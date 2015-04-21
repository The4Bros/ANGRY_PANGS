#include "Globals.h"
#include "Application.h"
#include "Particles.h"


#ifndef _BRICK_H_
#define _BRICK_H_



class Brick
{
	public:
		Application* app;

		SDL_Rect rect;
		bool alive;
		unsigned int type;
		int position_in_list;

		Brick(Application* app, int position_in_list, unsigned int x, unsigned int y, unsigned int type);
		~Brick(){}

		void Print();
		void Hit();

		void Reset(int position_in_list, unsigned int x, unsigned int y, unsigned int type);
	
};





#endif _BRICK_H_