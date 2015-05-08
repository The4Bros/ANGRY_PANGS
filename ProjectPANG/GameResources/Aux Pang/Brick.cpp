#include "Brick.h"


Brick::Brick(Application* app, unsigned int x, unsigned int y, unsigned int type) :
app(app),
alive(true),
type(type)
{
	if (type < 12)
	{
		rect = { x * app->windowModule->scale, y * app->windowModule->scale,
			8 * ((type / 3) + 1) * app->windowModule->scale, 8 * app->windowModule->scale };
	}
	else if (type < 14)
	{
		rect = { x * app->windowModule->scale, y * app->windowModule->scale,
			8 * app->windowModule->scale, 32 * app->windowModule->scale };
	}
	else
	{
		switch (type)
		{
		case 14:
			rect = { x * app->windowModule->scale, y * app->windowModule->scale,
				8 * app->windowModule->scale, 16 * app->windowModule->scale };
			break;
		case 15:
			rect = { x * app->windowModule->scale, y * app->windowModule->scale,
				8 * app->windowModule->scale, 24 * app->windowModule->scale };
			break;
		}
	}

}

void Brick::Print()
{
	app->renderModule->Print(app->texturesModule->bricks_sprite, &app->entityManagerModule->source_brick_rect[type], &rect);
}

void Brick::Hit()
{
	if (type < 16)
	{
		alive = false;

		//app->entityManagerModule->particles->push_back(new Particles( app, type, rect.x, rect.y));
	}
}


