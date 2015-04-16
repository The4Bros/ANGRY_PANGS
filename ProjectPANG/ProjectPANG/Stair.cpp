#include "Stair.h"



Stair::Stair(Application* app, unsigned int x, unsigned int y, unsigned int size)
{
	this->app = app;
	rect = { x * app->windowModule->scale, y * app->windowModule->scale, 32 * app->windowModule->scale, 8 * size * app->windowModule->scale };
	rects = new DynArray<SDL_Rect>(size);
	for (unsigned int i = 0; i < size; i++)
	{
		rects->PushBack({ x * app->windowModule->scale, (y + (i * 8)) * app->windowModule->scale, 32 * app->windowModule->scale, 8 * app->windowModule->scale });
	}
}

void Stair::Print()
{
	for (unsigned int i = 0; i < rects->Count(); i++)
	{
		app->renderModule->Print(app->texturesModule->bricks_sprite, app->entityManagerModule->source_stair_rect, rects->At(i));
	}

}

void Stair::Reset(unsigned int x, unsigned int y, unsigned int size)
{
	rect = { x * app->windowModule->scale, y * app->windowModule->scale, 32 * app->windowModule->scale, 8 * size * app->windowModule->scale };
	rects->Clear();
	for (int i = 0; i < size; i++)
	{
		rects->PushBack({ x * app->windowModule->scale, (y + (i * 8)) * app->windowModule->scale, 32 * app->windowModule->scale, 8 * app->windowModule->scale });
	}
}




