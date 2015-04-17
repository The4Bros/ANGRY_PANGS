#include "Brick.h"


Brick::Brick(Application* app, unsigned int x, unsigned int y, unsigned int type)
{
	this->app = app;
	alive = true;
	this->type = type;
	rect = { x * app->windowModule->scale, y * app->windowModule->scale,
		8*((type/4)+1) * app->windowModule->scale, 8 * app->windowModule->scale };

}

void Brick::Print()
{
	app->renderModule->Print(app->texturesModule->bricks_sprite, app->entityManagerModule->source_brick_rect[type], &rect );
}

//when a brick breaks + animation destroy brick
void Brick::Hit()
{
	alive = false;
	app->entityManagerModule->particles->push_back(new Particles( app, type, rect.x, rect.y));

}


void Brick::Reset(unsigned int x, unsigned int y, unsigned int type)
{
	this->app = app;
	alive = true;
	this->type = type;
	rect = { x * app->windowModule->scale, y * app->windowModule->scale,
		8 * ((type / 4) + 1) * app->windowModule->scale, 8 * app->windowModule->scale };
}
