#include "Balloon.h"




Balloon::Balloon(Application* app, int x, int y, int type, int max_height)
{
	this->app = app;
	this->type = RED_1;
	rect = { x, y, 16, 16 };
	this->max_height = max_height;
}



void Balloon::Update()
{

}



void Balloon::Hit()
{

}



void Balloon::Reset(unsigned int x, unsigned int y, unsigned int type, unsigned int max_height)
{
	this->type = RED_1;
	rect = { x, y, 16, 16 };
	this->max_height = max_height;
}