#include "Bullet.h"

Bullet::Bullet(Application* app) :
app(app),
update_counter(0),
alive(false)
{
	rects[0] = { 0, 0, 0, 0 };
	rects[1] = { 0, 0, 0, 0 };
	rects[2] = { 0, 0, 0, 0 };
}

void Bullet::Update()
{
	if (rects[0].y <= 8 * app->windowModule->scale || CheckCollisionBricks())
	{
		// create particles
		app->entityManagerModule->particles.push_back(new Particles(app, app->entityManagerModule->particles.Count(), 30, rects[0].x, rects[0].y));
		alive = false;
	}
	else if (CheckCollisionBalloons())
	{
		alive = false;
	}
	else
	{
		rects[0].y -= 2;
		rects[1].y -= 2;
	}
}

void Bullet::Print()
{
	app->renderModule->Print(app->texturesModule->particles_sprite, &app->entityManagerModule->shotgun_source_rect[source_index], &rects[0]);
	app->renderModule->Print(app->texturesModule->particles_sprite, &app->entityManagerModule->shotgun_source_rect[source_index], &rects[1]);
}

void Bullet::Spawn(unsigned int x, unsigned int y)
{
	update_counter = 0;
	alive = true;

	rects[0] = { 0, 0, 0, 0 };
	rects[1] = { 0, 0, 0, 0 };
	rects[2] = { 0, 0, 0, 0 };
}

bool Bullet::CheckCollisionBricks()
{
	SDL_Rect tmp_rect;

	for (unsigned int i = 0; i < app->entityManagerModule->bricks.Count(); i++)
	{
		tmp_rect = (*app->entityManagerModule->bricks.at(i))->rect;

		if (rects[2].x + rects[2].w >= tmp_rect.x // brick left
			&& tmp_rect.x + tmp_rect.w >= rects[2].x // brick right
			&& tmp_rect.y + tmp_rect.h >= rects[2].y // brick up
			&& rects[2].y + rects[2].h >= tmp_rect.y) // brick down
		{
			(*app->entityManagerModule->bricks.at(i))->Hit();
			return true;
		}
	}
	return false;
}

bool Bullet::CheckCollisionBalloons()
{
	SDL_Rect tmp_rect;

	for (unsigned int i = 0; i < app->entityManagerModule->balloons.Count(); i++)
	{
		tmp_rect = (*app->entityManagerModule->balloons.at(i))->rect;

		if (rects[2].x + rects[2].w >= tmp_rect.x // brick left
			&& tmp_rect.x + tmp_rect.w >= rects[2].x // brick right
			&& tmp_rect.y + tmp_rect.h >= rects[2].y // brick up
			&& rects[2].y + rects[2].h >= tmp_rect.y) // brick down
		{
			//Closest point to harpoon
			int closest_x, closest_y;

			if (tmp_rect.x + (tmp_rect.w / 2) < rects[2].x){ closest_x = rects[2].x; }
			else if (tmp_rect.x + (tmp_rect.w / 2) > rects[2].x + (rects[2].w / 2)){ closest_x = rects[2].x + (rects[2].w / 2); }
			else{ closest_x = tmp_rect.x + (tmp_rect.w / 2); }

			if (tmp_rect.y + (tmp_rect.h / 2) < rects[2].y){ closest_y = rects[2].y; }
			else if (tmp_rect.y + (tmp_rect.h / 2) > rects[2].y + rects[2].h){ closest_y = rects[2].y + rects[2].h; }
			else{ closest_y = tmp_rect.y + (tmp_rect.h / 2); }

			//Check distance between points
			if (((tmp_rect.h * tmp_rect.w) / 5)
	> ((closest_x - (tmp_rect.x + (tmp_rect.w / 2))) * (closest_x - (tmp_rect.x + (tmp_rect.w / 2))))
	+ ((closest_y - (tmp_rect.y + (tmp_rect.h / 2))) * (closest_y - (tmp_rect.y + (tmp_rect.h / 2)))))
			{
				(*app->entityManagerModule->balloons.at(i))->Hit();
				return true;
			}
		}
	}
	return false;
}


