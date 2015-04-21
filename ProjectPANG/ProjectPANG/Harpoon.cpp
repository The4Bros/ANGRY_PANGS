#include "Harpoon.h"


Harpoon::Harpoon(Application* app)
{
	this->app = app;

	update_counter = 0;
	alive = false;

	head_rect = { 0, 0, 9 * app->windowModule->scale, 9 * app->windowModule->scale };
	body_rect = { 0, 0, 7 * app->windowModule->scale, 30 * app->windowModule->scale };

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
	if (Check_Collision_Harpoon_Balloon()){ return; }

	if (source_index < 18) // HARPOON
	{
		if (Check_Collision_Harpoon_Brick())
		{
			alive = false;
		}
		else
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
	}

	else if (source_index < 20) // GRAPPLE
	{
		if (Check_Collision_Harpoon_Brick())
		{
			source_index = 20;
			update_counter = app->sceneModule->time_count->current_time;
		}
		else
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
	app->renderModule->Print(app->texturesModule->harpoons_sprite, app->entityManagerModule->harpoon_source_rect[source_index], &head_rect);

	SDL_Rect tmp;

	if (source_index < 20)
	{
		tmp = { body_rect.x, body_rect.y, body_rect.w, 16 * app->windowModule->scale };

		if (source_index % 2 == 0)
		{
			for (int i = 0; i < body_rect.h / (16 * app->windowModule->scale); i++)
			{
				app->renderModule->Print(app->texturesModule->harpoons_sprite, app->entityManagerModule->harpoon_source_rect[7], &tmp);
				tmp.y += 16 * app->windowModule->scale;
			}
			if (body_rect.h % (16 * app->windowModule->scale) > 0)
			{
				tmp.h = (body_rect.h / app->windowModule->scale) % 16;
				app->renderModule->Print(app->texturesModule->harpoons_sprite, app->entityManagerModule->harpoon_source_rect[((body_rect.h / app->windowModule->scale) % 8) - 1], &tmp);
			}
		}

		else
		{
			for (int i = 0; i < body_rect.h / 16; i++)
			{
				app->renderModule->Print(app->texturesModule->harpoons_sprite, app->entityManagerModule->harpoon_source_rect[7], &tmp);
				tmp.y += 2 * app->windowModule->scale;
			}
			tmp = {};
			app->renderModule->Print(app->texturesModule->harpoons_sprite, app->entityManagerModule->harpoon_source_rect[((body_rect.h / app->windowModule->scale) % 8) + 7], &tmp);
		}
	}

	else
	{
		tmp = { body_rect.x + (3 * app->windowModule->scale), body_rect.y, 3 * app->windowModule->scale, body_rect.h };

		for (int i = 0; tmp.y < body_rect.y + body_rect.h; i++)
		{
			app->renderModule->Print(app->texturesModule->harpoons_sprite, app->entityManagerModule->harpoon_source_rect[source_index + 3], &tmp);
			tmp.y += 2 * app->windowModule->scale;
		}
	}

	
}


bool Harpoon::Check_Collision_Harpoon_Balloon()
{
	for (unsigned int i = 0; i < app->entityManagerModule->balloons->Count(); i++)
	{
		app->entityManagerModule->tmp_balloon = *app->entityManagerModule->balloons->at(i);

		if (app->entityManagerModule->tmp_balloon->rect.x <= head_rect.x + head_rect.w
			&& app->entityManagerModule->tmp_balloon->rect.x + app->entityManagerModule->tmp_balloon->rect.w >= head_rect.x
			&& app->entityManagerModule->tmp_balloon->rect.y <= head_rect.y + body_rect.h
			&& app->entityManagerModule->tmp_balloon->rect.h + app->entityManagerModule->tmp_balloon->rect.y >= head_rect.y)
		{
			//Closest point to harpoon
			int closest_x, closest_y;
			
			if (app->entityManagerModule->tmp_balloon->rect.x + (app->entityManagerModule->tmp_balloon->rect.w / 2) < head_rect.x){ closest_x = head_rect.x; }
			else if (app->entityManagerModule->tmp_balloon->rect.x + (app->entityManagerModule->tmp_balloon->rect.w / 2) > head_rect.x + (head_rect.w / 2)){ closest_x = head_rect.x + (head_rect.w / 2); }
			else{ closest_x = app->entityManagerModule->tmp_balloon->rect.x + (app->entityManagerModule->tmp_balloon->rect.w / 2); }

			if (app->entityManagerModule->tmp_balloon->rect.y + (app->entityManagerModule->tmp_balloon->rect.h / 2) < head_rect.y){ closest_y = head_rect.y; }
			else if (app->entityManagerModule->tmp_balloon->rect.y + (app->entityManagerModule->tmp_balloon->rect.h / 2) > head_rect.y + head_rect.h + body_rect.h){ closest_y = head_rect.y + head_rect.h + body_rect.h; }
			else{ closest_y = app->entityManagerModule->tmp_balloon->rect.y + (app->entityManagerModule->tmp_balloon->rect.h / 2); }

			//Check distance between points
			if (((app->entityManagerModule->tmp_balloon->rect.h * app->entityManagerModule->tmp_balloon->rect.w) / 5)
				> ((closest_x - (app->entityManagerModule->tmp_balloon->rect.x + (app->entityManagerModule->tmp_balloon->rect.w / 2))) * (closest_x - (app->entityManagerModule->tmp_balloon->rect.x + (app->entityManagerModule->tmp_balloon->rect.w / 2))))
				+ ((closest_y - (app->entityManagerModule->tmp_balloon->rect.y + (app->entityManagerModule->tmp_balloon->rect.h / 2))) * (closest_y - (app->entityManagerModule->tmp_balloon->rect.y + (app->entityManagerModule->tmp_balloon->rect.h / 2)))))
			{
				app->entityManagerModule->tmp_balloon->Hit();
				return true;
			}
		}
	}
	return false;
}

bool Harpoon::Check_Collision_Harpoon_Brick()
{
	for (unsigned int i = 0; i < app->entityManagerModule->bricks->Count(); i++)
	{
		app->entityManagerModule->tmp_brick = *app->entityManagerModule->bricks->at(i);

		if (head_rect.x + head_rect.w >= app->entityManagerModule->tmp_brick->rect.x // brick left
		&& app->entityManagerModule->tmp_brick->rect.x + app->entityManagerModule->tmp_brick->rect.w >= head_rect.x // brick right
		&& app->entityManagerModule->tmp_brick->rect.y + app->entityManagerModule->tmp_brick->rect.h >= head_rect.y // brick up
		&& head_rect.y + head_rect.h + body_rect.h >= app->entityManagerModule->tmp_brick->rect.y) // brick down
		{
			app->entityManagerModule->tmp_brick->Hit();
			return true;
		}
	}
	return false;
}


//void Harpoon::Check_Collision_Bullet_Balloon()
/*
{
	//Closest point to bullet
	int closest_x, closest_y;

	//closest_x offset
	if (balloon_rect->x < bullet_rect->x){ closest_x = bullet_rect->x; }
	else if (balloon_rect->x > bullet_rect->x + bullet_rect->w){ closest_x = bullet_rect->x + bullet_rect->w; }
	else{ closest_x = balloon_rect->x; }

	//closest_y offset
	if (balloon_rect->y < bullet_rect->y){ closest_y = bullet_rect->y; }
	else if (balloon_rect->y > bullet_rect->y + bullet_rect->h){ closest_y = bullet_rect->y + bullet_rect->h; }
	else{ closest_y = balloon_rect->y; }

	//Check distance between points
	return (balloon_rect->h * balloon_rect->h) > ((closest_x - balloon_rect->x) * (closest_x - balloon_rect->x)) + ((closest_y - balloon_rect->y) * (closest_y - balloon_rect->y));
}

*/