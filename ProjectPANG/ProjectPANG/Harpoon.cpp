#include "Harpoon.h"


Harpoon::Harpoon(Application* app)
{
	this->app = app;

	rect = { 8 * app->windowModule->scale, 168 * app->windowModule->scale, 32 * app->windowModule->scale, 32 * app->windowModule->scale };

	source_rect = { 0, 0, 9, 9 };

	const_rect = new SDL_Rect(source_rect);
}