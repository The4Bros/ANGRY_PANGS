#include "Balloon.h"

//direction odd-> left
//direction pair->
// 0 -> start right
// 1 -> start left
// 2 -> new right
// 3 -> new left

Balloon::Balloon(Application* app, int x, int y, int type, int direction) :
		app(app),
		alive(true),
		ticks(1)
{
	if (direction < 2){ state_balloon_V = BALLOON_DOWN; gravity = 0; }
	else
	{
		state_balloon_V = BALLOON_UP;
		gravity = 0.8f * app->windowModule->scale_f * app->entityManagerModule->balloon_speed;

	}

	if (direction % 2 == 0){ state_balloon_H = BALLOON_RIGHT; }
	else{ state_balloon_H = BALLOON_LEFT; }


	switch (type)
	{
	case 0:
		this->type = RED_1;
		rect = { x*app->windowModule->scale, y*app->windowModule->scale, 48 * app->windowModule->scale, 40 * app->windowModule->scale };
		break;
	case 1:
		this->type = BLUE_1;
		rect = { x*app->windowModule->scale, y*app->windowModule->scale, 48 * app->windowModule->scale, 40 * app->windowModule->scale };
		break;
	case 2:
		this->type = GREEN_1;
		rect = { x*app->windowModule->scale, y*app->windowModule->scale, 48 * app->windowModule->scale, 40 * app->windowModule->scale };
		break;
	case 3:
		this->type = RED_2;
		rect = { x*app->windowModule->scale, y*app->windowModule->scale, 32 * app->windowModule->scale, 26 * app->windowModule->scale };
		break;
	case 4:
		this->type = BLUE_2;
		rect = { x*app->windowModule->scale, y*app->windowModule->scale, 32 * app->windowModule->scale, 26 * app->windowModule->scale };
		break;
	case 5:
		this->type = GREEN_2;
		rect = { x*app->windowModule->scale, y*app->windowModule->scale, 32 * app->windowModule->scale, 26 * app->windowModule->scale };
		break;
	case 6:
		this->type = RED_3;
		rect = { x*app->windowModule->scale, y*app->windowModule->scale, 16 * app->windowModule->scale, 14 * app->windowModule->scale };
		break;
	case 7:
		this->type = BLUE_3;
		rect = { x*app->windowModule->scale, y*app->windowModule->scale, 16 * app->windowModule->scale, 14 * app->windowModule->scale };
		break;
	case 8:
		this->type = GREEN_3;
		rect = { x*app->windowModule->scale, y*app->windowModule->scale, 16 * app->windowModule->scale, 14 * app->windowModule->scale };
		break;
	case 9:
		this->type = RED_4;
		rect = { x*app->windowModule->scale, y*app->windowModule->scale, 8 * app->windowModule->scale, 7 * app->windowModule->scale };
		break;
	case 10:
		this->type = BLUE_4;
		rect = { x*app->windowModule->scale, y*app->windowModule->scale, 8 * app->windowModule->scale, 7 * app->windowModule->scale };
		break;
	case 11:
		this->type = GREEN_4;
		rect = { x*app->windowModule->scale, y*app->windowModule->scale, 8 * app->windowModule->scale, 7 * app->windowModule->scale };
		break;
	}

	position_X = (float) rect.x;
	position_Y = (float) rect.y;


}

void Balloon::Update()
{
	if (type < RED_3){ Size1_Check_Collision_Balloon_Players(); }
	else{ Size4_Check_Collision_Balloon_Players(); }
	Check_Collision_Balloon_Bricks();
	//														-- VERTICAL --	

	switch (state_balloon_V)
	{
	case BALLOON_UP:

		if ((rect.y > 8 * app->windowModule->scale) && gravity >= 0)
		{
			position_Y -= gravity;

			ticks--;
			gravity -= 0.035f * app->windowModule->scale_f * app->entityManagerModule->balloon_speed;

		}
		else
		{
			state_balloon_V = BALLOON_DOWN;

			gravity = 0;
			ticks = 1;
		}
		break;

	case BALLOON_DOWN:

		if (rect.y + rect.h < 199 * app->windowModule->scale)
		{
			position_Y += gravity;
			
			ticks++;
			gravity += 0.035f * app->windowModule->scale_f * app->entityManagerModule->balloon_speed;

		}
		else
		{
			state_balloon_V = BALLOON_UP;

			if (type < 3) gravity = 2.17f * app->windowModule->scale_f * app->entityManagerModule->balloon_speed;
			else if (type < 6) gravity = 1.84f * app->windowModule->scale_f * app->entityManagerModule->balloon_speed;
			else if (type < 9) gravity = 1.5f * app->windowModule->scale_f * app->entityManagerModule->balloon_speed;
			else gravity = 1.12f * app->windowModule->scale_f * app->entityManagerModule->balloon_speed;

			ticks = 1;
		}
		break;

	default:
		break;
	}

	//														-- HORIZONTAL --

	switch (state_balloon_H)
	{
	case BALLOON_LEFT:

		if (rect.x > 8 * app->windowModule->scale) { position_X -= 0.5f * app->windowModule->scale_f * app->entityManagerModule->balloon_speed; }
		else state_balloon_H = BALLOON_RIGHT;
		break;

	case BALLOON_RIGHT:

		if (rect.x + rect.w < 376 * app->windowModule->scale) { position_X += 0.5f * (app->windowModule->scale_f * app->entityManagerModule->balloon_speed); }
		else state_balloon_H = BALLOON_LEFT;
		break;

	default:
		break;
	}


	rect.y = (int) (position_Y + 0.5);
	rect.x = (int) (position_X + 0.5);


}



void Balloon::Print()
{
	app->renderModule->Print(app->texturesModule->balls_sprite, &app->entityManagerModule->source_balloon_rect[int(type)], &rect);
}






void Balloon::Hit()
{
	app->entityManagerModule->particles.push(new Particles(app, int(type), rect.x, rect.y));

	if (type < 9)
	{
		Reduce_Balloon_Size();
		rect.x -= rect.w / 4;
		if (state_balloon_H == BALLOON_RIGHT) state_balloon_H = BALLOON_LEFT;

		app->entityManagerModule->balloons.push(new Balloon(app, (rect.x + (rect.w / 2)) / app->windowModule->scale, rect.y / app->windowModule->scale, int(type), 2));

		Restart_Movement_Balloons_hit();
	}
	else { alive = false; }
}

void Balloon::Restart_Movement_Balloons_hit()
{
	state_balloon_V = BALLOON_UP;
	ticks = 1;

	if (state_balloon_V == BALLOON_DOWN){ gravity = 0; }
	else
	{
		gravity = 0.8f * app->windowModule->scale_f * app->entityManagerModule->balloon_speed;
	}
}

void Balloon::Reduce_Balloon_Size()
{
	switch (type)
	{
	case  0:
		type = RED_2;
		rect.w = 32 * app->windowModule->scale;
		rect.h = 26 * app->windowModule->scale;
		break;
	case  1:
		type = BLUE_2;
		rect.w = 32 * app->windowModule->scale;
		rect.h = 26 * app->windowModule->scale;
		break;
	case  2:
		type = GREEN_2;
		rect.w = 32 * app->windowModule->scale;
		rect.h = 26 * app->windowModule->scale;
		break;
	case  3:
		type = RED_3;
		rect.w = 16 * app->windowModule->scale;
		rect.h = 14 * app->windowModule->scale;
		break;
	case  4:
		type = BLUE_3;
		rect.w = 16 * app->windowModule->scale;
		rect.h = 14 * app->windowModule->scale;
		break;
	case  5:
		type = GREEN_3;
		rect.w = 16 * app->windowModule->scale;
		rect.h = 14 * app->windowModule->scale;
		break;
	case  6:
		type = RED_4;
		rect.w = 8 * app->windowModule->scale;
		rect.h = 7 * app->windowModule->scale;
		break;
	case  7:
		type = BLUE_4;
		rect.w = 8 * app->windowModule->scale;
		rect.h = 7 * app->windowModule->scale;
		break;
	case  8:
		type = GREEN_4;
		rect.w = 8 * app->windowModule->scale;
		rect.h = 7 * app->windowModule->scale;
		break;
	}
}





void Balloon::Size1_Check_Collision_Balloon_Players()
{
	//Closest point to ball
	int closest_x, closest_y;

	//closest_x offset
	if (rect.x + (rect.w / 2) < app->playerModule->player1->rect.x + (app->playerModule->player1->rect.w / 2)){ closest_x = app->playerModule->player1->rect.x; } // Player to the right
	else{ closest_x = app->playerModule->player1->rect.x + app->playerModule->player1->rect.w; } // Player to the left

	//closest_y offset
	if (rect.y + (rect.h / 2) < app->playerModule->player1->rect.y){ closest_y = app->playerModule->player1->rect.y; } // Player bellow
	else{ closest_y = app->playerModule->player1->rect.y + app->playerModule->player1->rect.h; } // Player above

	//Check distance between points
	if (((rect.h * rect.w) / 8) >((closest_x - (rect.x + (rect.w / 2))) * (closest_x - (rect.x + (rect.w / 2)))) + ((closest_y - (rect.y + (rect.h / 2))) * (closest_y - (rect.y + (rect.h / 2)))))
	{
		app->playerModule->player1->Hit(&rect); // true if player1 got hit
		return; // no need to check player2 if player1 got hit
	}

	if (app->playerModule->player2 != NULL)
	{
		//Closest point to ball
		int closest_x, closest_y;

		//closest_x offset
		if (rect.x + (rect.w / 2) < app->playerModule->player2->rect.x + (app->playerModule->player2->rect.w / 2)){ closest_x = app->playerModule->player2->rect.x; } // Player to the right
		else{ closest_x = app->playerModule->player2->rect.x + app->playerModule->player2->rect.w; } // Player to the left

		//closest_y offset
		if (rect.y + (rect.h / 2) < app->playerModule->player1->rect.y){ closest_y = app->playerModule->player2->rect.y; } // Player bellow
		else{ closest_y = app->playerModule->player2->rect.y + app->playerModule->player2->rect.h; } // Player above

		//Check distance between points
		if (((rect.h * rect.w) / 8) >((closest_x - (rect.x + (rect.w / 2))) * (closest_x - (rect.x + (rect.w / 2)))) + ((closest_y - (rect.y + (rect.h / 2))) * (closest_y - (rect.y + (rect.h / 2)))))
		{
			app->playerModule->player2->Hit(&rect); // true if player2 got hit
		}
	}
}

void Balloon::Size4_Check_Collision_Balloon_Players()
{
	if (rect.x < app->playerModule->player1->rect.x + app->playerModule->player1->rect.w - (8 * app->windowModule->scale)
		&& rect.x + rect.w > app->playerModule->player1->rect.x + (8 * app->windowModule->scale)
		&& rect.y < app->playerModule->player1->rect.y + app->playerModule->player1->rect.h - (8 * app->windowModule->scale)
		&& rect.y + rect.h > app->playerModule->player1->rect.y + (8 * app->windowModule->scale))
	{
		app->playerModule->player1->Hit(&rect); // true if player1 got hit
		return; // no need to check player2 if player1 got hit
	}

	if (app->playerModule->player2 != NULL)
	{
		if (rect.x < app->playerModule->player2->rect.x + app->playerModule->player2->rect.w - (8 * app->windowModule->scale)
			&& rect.x + rect.w > app->playerModule->player2->rect.x + (8 * app->windowModule->scale)
			&& rect.y < app->playerModule->player2->rect.y + app->playerModule->player2->rect.h - (8 * app->windowModule->scale)
			&& rect.y + rect.h > app->playerModule->player2->rect.y + (8 * app->windowModule->scale))
		{
			app->playerModule->player2->Hit(&rect); // true if player2 got hit
		}
	}
}


void Balloon::Check_Collision_Balloon_Bricks()
{
	SDL_Rect tmp_rect;

	DoubleNode<Brick*>* tmp_brick = app->entityManagerModule->bricks.getStart();
	for (; tmp_brick != NULL; tmp_brick = tmp_brick->next)
	{
		tmp_rect = tmp_brick->data->rect;

		//Closest point to brick
		int closest_x, closest_y;

		//closest_x offset
		if (rect.x < tmp_rect.x){ closest_x = tmp_rect.x; }
		else if (rect.x > tmp_rect.x + tmp_rect.w){ closest_x = tmp_rect.x + tmp_rect.w; }
		else{ closest_x = rect.x; }

		//closest_y offset
		if (rect.y < tmp_rect.y){ closest_y = tmp_rect.y; }
		else if (rect.y > tmp_rect.y + tmp_rect.h){ closest_y = tmp_rect.y + tmp_rect.h; }
		else{ closest_y = rect.y; }

		//Check distance between points
		if ((rect.h * rect.h) > ((closest_x - rect.x) * (closest_x - rect.x)) + ((closest_y - rect.y) * (closest_y - rect.y)))
		{
			if (tmp_rect.x + (tmp_rect.w / 2) > rect.x + (rect.w / 2)) // brick to the right
			{
				if (tmp_rect.y + (tmp_rect.h / 2) < rect.y + (rect.h / 2)) // brick above
				{
					if (rect.y + (rect.h / 2) - tmp_rect.y + (tmp_rect.h / 2) > tmp_rect.x + (tmp_rect.w / 2) - rect.x + (rect.w / 2))
					{
						//horizontal collision -> balloon moves left---------------------------
						state_balloon_H = BALLOON_LEFT;
					}
					else
					{
						//vertical collision -> balloon moves down -----------------------------
						state_balloon_V = BALLOON_DOWN;

						gravity = 12;
						ticks = 1;

					}
				}
				else // brick bellow
				{
					if (tmp_rect.y + (tmp_rect.h / 2) - rect.y + (rect.h / 2) > tmp_rect.x + (tmp_rect.w / 2) - rect.x + (rect.w / 2))
					{
						//horizontal collision -> balloon moves left-----------------------------
						state_balloon_H = BALLOON_LEFT;
					}
					else
					{
						//vertical collision -> balloon moves up -----------------------------
						state_balloon_V = BALLOON_UP;

						if (type < 3) gravity = 6;
						else if (type < 6) gravity = 5;
						else if (type < 9) gravity = 4;
						else gravity = 2;

						ticks = 1;
					}
				}
			}
			else // brick to the left
			{
				if (tmp_rect.y + (tmp_rect.h / 2) < rect.y + (rect.h / 2)) // brick above
				{
					if (rect.y + (rect.h / 2) - tmp_rect.y + (tmp_rect.h / 2) > rect.x + (rect.w / 2) - tmp_rect.x + (tmp_rect.w / 2))
					{
						//horizontal collision -> balloon moves right-----------------------------
						state_balloon_H = BALLOON_RIGHT;
					}
					else
					{
						//vertical collision -> balloon moves down -----------------------------
						state_balloon_V = BALLOON_DOWN;

						gravity = 3;
						ticks = 1;
					}
				}
				else // brick bellow
				{
					if (tmp_rect.y + (tmp_rect.h / 2) - rect.y + (rect.h / 2) > rect.x + (rect.w / 2) - tmp_rect.x + (tmp_rect.w / 2))
					{
						//horizontal collision -> balloon moves right-----------------------------
						state_balloon_H = BALLOON_RIGHT;
					}
					else
					{
						//vertical collision -> balloon moves up -----------------------------
						state_balloon_V = BALLOON_UP;

						if (type < 3) gravity = 6;
						else if (type < 6) gravity = 5;
						else if (type < 9) gravity = 4;
						else gravity = 2;

						ticks = 1;
					}
				}
			}
			return;
		}
	}
}