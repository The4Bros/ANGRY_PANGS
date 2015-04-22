#include "Brick.h"


Brick::Brick(Application* app, int position_in_list, unsigned int x, unsigned int y, unsigned int type)
{
	this->app = app;
	this->position_in_list = position_in_list;
	alive = true;
	this->type = type;

	rect = { x * app->windowModule->scale, y * app->windowModule->scale,
		8*((type/4)+1) * app->windowModule->scale, 8 * app->windowModule->scale };

}

void Brick::Print()
{
	if (alive)
	{
		app->renderModule->Print(app->texturesModule->bricks_sprite, app->entityManagerModule->source_brick_rect[type], &rect);
	}
}

void Brick::Hit()
{
	if (type < 16)
	{
		for (int i = position_in_list + 1; i < app->entityManagerModule->bricks->Count(); i++)
		{
			(*app->entityManagerModule->bricks->at(i))->position_in_list--;
		}
		app->entityManagerModule->bricks->Delete_Element_At(position_in_list);

		//app->entityManagerModule->particles->push_back(new Particles( app, app->entityManagerModule->particles->Count(), type, rect.x, rect.y));
	}
}


void Brick::Reset(int position_in_list, unsigned int x, unsigned int y, unsigned int type)
{
	this->app = app;
	this->position_in_list = position_in_list;
	alive = true;
	this->type = type;
	rect = { x * app->windowModule->scale, y * app->windowModule->scale,
		8 * ((type / 4) + 1) * app->windowModule->scale, 8 * app->windowModule->scale };
}
