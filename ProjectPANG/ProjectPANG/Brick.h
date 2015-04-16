#include "Globals.h"
#include "Application.h"
#include "Particles.h"


#ifndef _BRICK_H_
#define _BRICK_H_

enum BRICK_TYPE
{
	GOLD1,//------bricks unbreakeables-----
	GOLD2,	
	GOLD3,
	FUCSIA1,
	FUCSIA2,
	FUCSIA3,
	BLUE1,
	BLUE2,
	BLUE3,
	YELLOW1,//-----bricks breakeables-----
	YELLOW2,
	YELLOW3,
	PINK1,
	PINK2,
	PINK3,
	CIAN1,
	CIAN2,
	CIAN3
};

class Brick
{
	public:
		Application* app;

		SDL_Rect rect;

		DynArray<SDL_Rect> rects;

		BRICK_TYPE type;

		Brick(Application* app, unsigned int x, unsigned int y,  unsigned int type);
		~Brick(){}

		void Print();

		void Update();

		void Break();
	
};





#endif _BRICK_H_