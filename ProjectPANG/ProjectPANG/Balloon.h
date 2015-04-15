#include "Globals.h"
#include "Application.h"
#include "Particles.h"

#ifndef __Balloon_H__
#define __Balloon_H__

enum BALL_TYPE
{
	RED_1,
	RED_2,
	BLUE,
	GREEN
};


class Balloon
{
public:
	Application* app;

	unsigned int max_height;
	BALL_TYPE type;

	SDL_Rect rect;

	Balloon(Application* app, unsigned int x, unsigned int y, unsigned int type, unsigned int max_height);
	~Balloon(){}

	void Update();
	// 8 * app->windowModule->scale;
	// (376 * app->windowModule->scale) - rect.w;


	void Hit();
	// particles->PushBack(x, y, type);


};
#endif