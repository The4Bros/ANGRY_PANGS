#include "Harpoon.h"


Harpoon::Harpoon(Application* app)
{
	this->app = app;

	update_counter = 0;
	alive = false;

	head_rect = { 0, 0, 9 * app->windowModule->scale, 9 * app->windowModule->scale };
	body_rect = { 0, 0, 7 * app->windowModule->scale, 30 * app->windowModule->scale };

	// BODIES
	for (int i = 0; i < 8; i++)
	{
		source_rect[i + 8] = new SDL_Rect({ 0, 0, 7, (i + 1) * 2 });
		source_rect[i] = new SDL_Rect({ 7, 0, 7, (i + 1) * 2});
	}

	// HEADS
	source_rect[16] = new SDL_Rect({ 14,  0, 9, 9 });
	source_rect[17] = new SDL_Rect({ 22, 0, 9, 9 });

	// GRAPPLE HEADS
	source_rect[18] = new SDL_Rect({ 14,  9, 9, 6 });
	source_rect[19] = new SDL_Rect({ 22, 9, 9, 6 });

	// GRAPPLED HEADS
	source_rect[20] = new SDL_Rect({ 31, 0, 9, 4 });
	source_rect[21] = new SDL_Rect({ 31, 4, 9, 4 });
	source_rect[22] = new SDL_Rect({ 31, 8, 9, 4 });

	// GRAPPLED BODIES
	source_rect[23] = new SDL_Rect({ 31, 13, 3, 2 });
	source_rect[24] = new SDL_Rect({ 34, 13, 3, 2 });
	source_rect[25] = new SDL_Rect({ 37, 13, 3, 2 });


}

void Harpoon::Shoot_Harpoon(unsigned int y, unsigned int x)
{
	alive = true;
	head_rect.x = x;
	head_rect.y = y;
	head_rect.h = 9 * app->windowModule->scale;
	body_rect.x = x + 1;
	body_rect.y = y + (9 * app->windowModule->scale);
	body_rect.h = 21 * app->windowModule->scale;
	source_index = 16;
}

void Harpoon::Shoot_Grapple(unsigned int y, unsigned int x)
{
	alive = true;
	head_rect.x = x;
	head_rect.y = y;
	head_rect.h = 6 * app->windowModule->scale;
	body_rect.x = x + 1;
	body_rect.y = y + (6 * app->windowModule->scale);
	body_rect.h = 21 * app->windowModule->scale;
	source_index = 18;
}


void Harpoon::Update()
{
	if (source_index < 18) // HARPOON
	{
		if (head_rect.y > 8 * app->windowModule->scale)
		{
			head_rect.y -= 2 * app->windowModule->scale;
			body_rect.y -= 2 * app->windowModule->scale;
			body_rect.h += 2 * app->windowModule->scale;

			if (update_counter > 4)
			{
				update_counter = 0;
				//source_index == 16 ? source_index = 17 : source_index = 16; *******************************************************
			}
			else{ update_counter++; }
		}
		else{ alive = false; }
	}

	else if (source_index < 20) // GRAPPLE
	{
		if (head_rect.y > 8 * app->windowModule->scale)
		{
			head_rect.y -= 2 * app->windowModule->scale;
			body_rect.y -= 2 * app->windowModule->scale;
			body_rect.h += 2 * app->windowModule->scale;

			if (update_counter > 4)
			{
				update_counter = 0;
				//source_index == 18 ? source_index = 19 : source_index = 18; ************************************************************
			}
			else{ update_counter++; }
		}
		else{ source_index = 20; update_counter = app->sceneModule->time_count->current_time; }
	}

	else if (app->sceneModule->time_count->current_time <= update_counter - 5) // GRAPPLED
	{
		if (source_index < 23)
		{
			update_counter = app->sceneModule->time_count->current_time;
			source_index++;
		}
		else{ alive = false; }
	}
}

void Harpoon::Print()
{
	app->renderModule->Print(app->texturesModule->harpoons_sprite, source_rect[source_index], &head_rect);

	SDL_Rect tmp;

	if (source_index < 20)
	{
		tmp = { body_rect.x, body_rect.y, body_rect.w, 16 * app->windowModule->scale };

		if (source_index % 2 == 0)
		{
			for (int i = 0; i < body_rect.h / (16 * app->windowModule->scale); i++)
			{
				app->renderModule->Print(app->texturesModule->harpoons_sprite, source_rect[7], &tmp);
				tmp.y += 16 * app->windowModule->scale;
			}
			if (body_rect.h % (16 * app->windowModule->scale) > 0)
			{
				tmp.h = (body_rect.h / app->windowModule->scale) % 16;
				app->renderModule->Print(app->texturesModule->harpoons_sprite, source_rect[((body_rect.h / app->windowModule->scale) % 8) - 1], &tmp);
			}
		}

		else
		{
			for (int i = 0; i < body_rect.h / 16; i++)
			{
				app->renderModule->Print(app->texturesModule->harpoons_sprite, source_rect[7], &tmp);
				tmp.y += 2 * app->windowModule->scale;
			}
			tmp = {};
			app->renderModule->Print(app->texturesModule->harpoons_sprite, source_rect[((body_rect.h / app->windowModule->scale) % 8) + 7], &tmp);
		}
	}

	else
	{
		tmp = { body_rect.x + (3 * app->windowModule->scale), body_rect.y, 3 * app->windowModule->scale, body_rect.h };

		for (int i = 0; tmp.y < body_rect.y + body_rect.h; i++)
		{
			app->renderModule->Print(app->texturesModule->harpoons_sprite, source_rect[source_index + 3], &tmp);
			tmp.y += 2 * app->windowModule->scale;
		}
	}

	
}