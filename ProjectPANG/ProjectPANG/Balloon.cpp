#include "Balloon.h"
//direction odd-> left
//direction pair->
//0 -> start right
// 1 -> start left
// 2 -> new right
// 3 -> new left

Balloon::Balloon(Application* app, int position_in_list, int x, int y, int type, int direction)
{
	gravity = 2;
	horizontal_speed = 2;
	ticks = 2;

	this->app = app;
	this->position_in_list = position_in_list;

	

	Restart_Movement_Balloons_hit();
	if (direction == 0)
	{
		state_balloon_H = BALLOON_RIGHT;
		state_balloon_V = BALLOON_DOWN;
	}
	if(direction == 1)
	{
		state_balloon_H = BALLOON_LEFT;
		state_balloon_V = BALLOON_DOWN;
	}
	if (direction == 2)
	{
		state_balloon_H = BALLOON_RIGHT;
	
	}
	if (direction == 3)
	{
		state_balloon_H = BALLOON_LEFT;
	
	}
	//---




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




}



void Balloon::Update()
{


	if (type < RED_3){ Size1_Check_Collision_Balloon_Players(); }
	else{ Size4_Check_Collision_Balloon_Players(); }

	//														-- VERTICAL --	

	switch (state_balloon_V)
	{
	case BALLOON_UP:

		if ((rect.y > 8 * app->windowModule->scale) && gravity != 0)
		{
			rect.y = rect.y - gravity;
			ticks--;

			if (ticks % 5 == 0) gravity--;

		}
		else
		{
			//Hit();
			state_balloon_V = BALLOON_DOWN;

			gravity = 0;
			ticks = 1;
		}
		break;

	case BALLOON_DOWN:

		if (rect.y + rect.h < 199 * app->windowModule->scale)
		{
			rect.y = rect.y + gravity;

			ticks++;
			if (ticks % 5 == 0)
			{
				gravity++;
			}


		}
		else
		{
			state_balloon_V = BALLOON_UP;

			// Jump height for each balloon

			if (type < 3) gravity = 12;
			else if (type < 6) gravity = 11;
			else if (type < 9) gravity = 9;
			else gravity = 7;

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

		if (rect.x > 8 * app->windowModule->scale) rect.x -= horizontal_speed;
		else state_balloon_H = BALLOON_RIGHT;

		break;
	case BALLOON_RIGHT:

		if (rect.x + rect.w < 376 * app->windowModule->scale) rect.x += horizontal_speed;
		else state_balloon_H = BALLOON_LEFT;

		break;
	default:
		break;
	}

}



void Balloon::Print()
{
	app->renderModule->Print(app->texturesModule->balls_sprite, app->entityManagerModule->source_balloon_rect[int(type)], &rect);
}






void Balloon::Hit()
{
	app->entityManagerModule->particles->push_back(new Particles(app, app->entityManagerModule->particles->Count(), int(type), rect.x, rect.y));

	if (type < 9)
	{
		Reduce_Balloon_Size();
		rect.x -= rect.w / 4;
		if (state_balloon_H == BALLOON_RIGHT) state_balloon_H = BALLOON_LEFT;
		app->entityManagerModule->balloons->push_back(new Balloon(app, app->entityManagerModule->balloons->Count(), ((rect.x + (rect.w / 2)) / app->windowModule->scale), (rect.y / app->windowModule->scale), int(type), 2));
	}
	else
	{
		for (int i = position_in_list + 1; i < app->entityManagerModule->balloons->Count(); i++)
		{
			(*app->entityManagerModule->balloons->at(i))->position_in_list--;
		}
		app->entityManagerModule->balloons->Delete_Element_At(position_in_list);
	}
	Restart_Movement_Balloons_hit();
}
void Balloon::Restart_Movement_Balloons_hit()
{
	
	state_balloon_V = BALLOON_UP;
	gravity = 1;
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




void Balloon::Reset(int position_in_list, int x, int y, int type, int direction)
{
	gravity = 2;
	horizontal_speed = 2;
	ticks = 2;
	this->position_in_list = position_in_list;

	this->app = app;
	rect = { x*app->windowModule->scale, y*app->windowModule->scale, 48 * app->windowModule->scale, 40 * app->windowModule->scale };

	state_balloon_H = BALLOON_RIGHT;
	state_balloon_V = BALLOON_DOWN;

	switch (type)
	{
	case 0:
		this->type = RED_1;
		rect = { x*app->windowModule->scale, y*app->windowModule->scale, 48 * app->windowModule->scale, 40 * app->windowModule->scale };
		break;
	case 2:
		this->type = BLUE_1;
		rect = { x*app->windowModule->scale, y*app->windowModule->scale, 48 * app->windowModule->scale, 40 * app->windowModule->scale };
		break;
	case 3:
		this->type = GREEN_1;
		rect = { x*app->windowModule->scale, y*app->windowModule->scale, 48 * app->windowModule->scale, 40 * app->windowModule->scale };
		break;
	case 4:
		this->type = RED_2;
		rect = { x*app->windowModule->scale, y*app->windowModule->scale, 32 * app->windowModule->scale, 26 * app->windowModule->scale };
		break;
	case 5:
		this->type = BLUE_2;
		rect = { x*app->windowModule->scale, y*app->windowModule->scale, 32 * app->windowModule->scale, 26 * app->windowModule->scale };
		break;
	case 6:
		this->type = GREEN_2;
		rect = { x*app->windowModule->scale, y*app->windowModule->scale, 32 * app->windowModule->scale, 26 * app->windowModule->scale };
		break;
	case 7:
		this->type = RED_3;
		rect = { x*app->windowModule->scale, y*app->windowModule->scale, 16 * app->windowModule->scale, 14 * app->windowModule->scale };
		break;
	case 8:
		this->type = BLUE_3;
		rect = { x*app->windowModule->scale, y*app->windowModule->scale, 16 * app->windowModule->scale, 14 * app->windowModule->scale };
		break;
	case 9:
		this->type = GREEN_3;
		rect = { x*app->windowModule->scale, y*app->windowModule->scale, 16 * app->windowModule->scale, 14 * app->windowModule->scale };
		break;
	case 10:
		this->type = RED_4;
		rect = { x*app->windowModule->scale, y*app->windowModule->scale, 8 * app->windowModule->scale, 7 * app->windowModule->scale };
		break;
	case 11:
		this->type = BLUE_4;
		rect = { x*app->windowModule->scale, y*app->windowModule->scale, 8 * app->windowModule->scale, 7 * app->windowModule->scale };
		break;
	case 12:
		this->type = GREEN_4;
		rect = { x*app->windowModule->scale, y*app->windowModule->scale, 8 * app->windowModule->scale, 7 * app->windowModule->scale };
		break;
	}
}





void Balloon::Size1_Check_Collision_Balloon_Players()
{
	if (rect.x < app->playerModule->player1->rect.x + app->playerModule->player1->rect.w
		&& rect.x + rect.w > app->playerModule->player1->rect.x
		&& rect.y < app->playerModule->player1->rect.y + app->playerModule->player1->rect.h
		&& rect.h + rect.y > app->playerModule->player1->rect.y)
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
	}

	if (app->playerModule->player2 != NULL)
	{
		if (rect.x < app->playerModule->player2->rect.x + app->playerModule->player2->rect.w
			&& rect.x + rect.w > app->playerModule->player2->rect.x
			&& rect.y < app->playerModule->player2->rect.y + app->playerModule->player2->rect.h
			&& rect.h + rect.y > app->playerModule->player2->rect.y)
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
}

void Balloon::Size4_Check_Collision_Balloon_Players()
{
	if (rect.x < app->playerModule->player1->rect.x + (app->playerModule->player1->rect.w / 4)
		&& rect.x + rect.w > app->playerModule->player1->rect.x + (3 * app->playerModule->player1->rect.w / 4)
		&& rect.y < app->playerModule->player1->rect.y + (app->playerModule->player1->rect.h / 4)
		&& rect.h + rect.y > app->playerModule->player1->rect.y + (3 * app->playerModule->player1->rect.h / 4))
	{
		app->playerModule->player1->Hit(&rect); // true if player1 got hit
		return; // no need to check player2 if player1 got hit
	}

	if (app->playerModule->player2 != NULL)
	{
		if (rect.x < app->playerModule->player2->rect.x + (app->playerModule->player2->rect.w / 4)
			&& rect.x + rect.w > app->playerModule->player2->rect.x + (3 * app->playerModule->player2->rect.w / 4)
			&& rect.y < app->playerModule->player2->rect.y + (app->playerModule->player2->rect.h / 4)
			&& rect.h + rect.y > app->playerModule->player2->rect.y + (3 * app->playerModule->player2->rect.h / 4))
		{
			app->playerModule->player2->Hit(&rect); // true if player2 got hit
		}
	}
}








void Balloon::Check_Collision_Balloon_Bricks()
{
	SDL_Rect tmp_rect;

	for (unsigned int i = 0; i < app->entityManagerModule->bricks->Count(); i++)
	{
		tmp_rect = (*app->entityManagerModule->bricks->at(i))->rect;

		if (rect.x  < tmp_rect.x + tmp_rect.w
			&& rect.x + rect.w > tmp_rect.x
			&& rect.y < tmp_rect.y + tmp_rect.h
			&& rect.y + rect.h > tmp_rect.y)
		{
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
						}
						else
						{
							//vertical collision -> balloon moves down -----------------------------
						}
					}
					else // brick bellow
					{
						if (tmp_rect.y + (tmp_rect.h / 2) - rect.y + (rect.h / 2) > tmp_rect.x + (tmp_rect.w / 2) - rect.x + (rect.w / 2))
						{
							//horizontal collision -> balloon moves left-----------------------------
						}
						else
						{
							//vertical collision -> balloon moves up -----------------------------
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
						}
						else
						{
							//vertical collision -> balloon moves down -----------------------------
						}
					}
					else // brick bellow
					{
						if (tmp_rect.y + (tmp_rect.h / 2) - rect.y + (rect.h / 2) > rect.x + (rect.w / 2) - tmp_rect.x + (tmp_rect.w / 2))
						{
							//horizontal collision -> balloon moves right-----------------------------
						}
						else
						{
							//vertical collision -> balloon moves up -----------------------------
						}
					}
				}

				return;
			}
		}
	}
}