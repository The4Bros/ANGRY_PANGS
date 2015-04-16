#include "Brick.h"

Brick::Brick(Application* app, unsigned int x, unsigned int y, unsigned int type)
{
	this->app = app;
	this->type = GOLD1;
	rect = { x, y, 31, 7 };
}

void Brick::Update()
{

}

