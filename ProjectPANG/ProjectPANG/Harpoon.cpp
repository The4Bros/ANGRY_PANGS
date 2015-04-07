#include "Harpoon.h"


Harpoon::Harpoon(Application* app)
{
	this->app = app;

	update_counter = 0;
	alive = false;

	rect = { 8 * app->windowModule->scale, 168 * app->windowModule->scale, 9 * app->windowModule->scale, 32 * app->windowModule->scale };

	source_rect = { 0, 0, 9, 9 };

	const_rect = new SDL_Rect(source_rect);
}

void Harpoon::Shoot_Harpoon(SDL_Rect player_rect)
{
	alive = true;
	rect.x = player_rect.x + 12 * app->windowModule->scale;
	rect.y = player_rect.y;
	rect.h = 32 * app->windowModule->scale;
	source_rect = { 0, 0, 9, 32 };
	const_rect = new SDL_Rect(source_rect);
}

void Harpoon::Shoot_Grapple(SDL_Rect player_rect)
{
	alive = true;
	rect.x = player_rect.x + 9 * app->windowModule->scale;
	rect.y = player_rect.y;
	rect.h = 32 * app->windowModule->scale;
	source_rect = { 18, 0, 9, 32 };
	const_rect = new SDL_Rect(source_rect);
}

void Harpoon::Shoot_Shotgun(SDL_Rect player_rect)
{
	return;
}


void Harpoon::Update()
{
	if (rect.y <= 9 * app->windowModule->scale)
	{
		if (source_rect.x > 9)
		{
			rect.y = 8 * app->windowModule->scale;
			source_rect.x = 36;
		}
		else{ alive = false; }
	}
	else
	{
		if (update_counter > 4)
		{
			update_counter = 0;
			source_rect.x == 0 ? source_rect.x = 9 : source_rect.x = 0;
		}
		else{ update_counter++; }
		
		rect.y -= 2 * app->windowModule->scale;
		rect.h += 2 * app->windowModule->scale;
		source_rect.h += 2;
		const_rect = new SDL_Rect(source_rect);
	}
}

