#include "Balloon.h"



Balloon::Balloon(Application* app, int x, int y, int type, int max_height)
{
	gravity = 2;
	horizontal_speed = 2;
	ticks = 2;
	position_in_list = 0;

	while (position_in_list < app->entityManagerModule->balloons->Count())
	{
		position_in_list++;
	}


	this->app = app;
	this->max_height = max_height;

	state_balloon_H = BALLOON_RIGHT;
	state_balloon_V = BALLOON_DOWN;


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

			if (ticks % 8 == 0) gravity--;

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
			if (ticks % 8 == 0)
			{
				gravity++;
			}


		}
		else
		{
			state_balloon_V = BALLOON_UP;

			// Jump height for each balloon

			if (type < 3) gravity = 9;
			else if (type < 6) gravity = 8;
			else if (type < 9) gravity = 7;
			else gravity = 6;

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
	app->renderModule->Print(app->texturesModule->balls_sprite, app->entityManagerModule->source_balloon_rect[type], &rect);
}






void Balloon::Hit()
{
	int aux_rect_X = rect.x;
	int aux_rect_Y = rect.y;
	rect.x -= rect.w;

	app->entityManagerModule->balloons->push_back(new Balloon(app, aux_rect_X, aux_rect_Y, type, max_height));

	if (BALLOON_RIGHT)
	{
		BALLOON_LEFT;
	}

	switch (type)
	{

	case 0:

		type = RED_2;


		break;

	case 1:

		type = BLUE_2;


		break;

	case 2:

		type = GREEN_2;

		break;

	case 3:

		type = RED_3;

		break;

	case 4:

		type = BLUE_3;

		break;

	case 5:

		type = GREEN_3;

		break;

	case 6:

		type = RED_4;

		break;

	case 7:

		type = BLUE_4;

		break;

	case 8:

		type = GREEN_4;

		break;

	default:
		rect = { 0, 0, 0, 0 };

		break;

	}





}




void Balloon::Reset(unsigned int x, unsigned int y, unsigned int type, unsigned int max_height)
{
	gravity = 2;
	horizontal_speed = 2;
	ticks = 2;
	position_in_list = 0;

	while (position_in_list < app->entityManagerModule->balloons->Count())
	{
		position_in_list++;
	}


	this->app = app;
	rect = { x*app->windowModule->scale, y*app->windowModule->scale, 48 * app->windowModule->scale, 40 * app->windowModule->scale };
	this->max_height = max_height;

	state_balloon_H = BALLOON_RIGHT;
	state_balloon_V = BALLOON_DOWN;


	//---




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







































void Balloon::Check_Collision_Balloon_Brick_Vertical()
{
	//Closest point to brick
	int closest_x, closest_y;

	//closest_x offset
	if (rect.x < app->playerModule->player1->rect.x){ closest_x = app->playerModule->player1->rect.x; }
	else if (rect.x > app->playerModule->player1->rect.x + app->playerModule->player1->rect.w){ closest_x = app->playerModule->player1->rect.x + app->playerModule->player1->rect.w; }
	else{ closest_x = rect.x; }

	//closest_y offset
	if (rect.y < app->playerModule->player1->rect.y){ closest_y = app->playerModule->player1->rect.y; }
	else if (rect.y > app->playerModule->player1->rect.y + app->playerModule->player1->rect.h){ closest_y = app->playerModule->player1->rect.y + app->playerModule->player1->rect.h; }
	else{ closest_y = rect.y; }

	//Check distance between points
	//return (rect.h * rect.h) > ((closest_x - rect.x) * (closest_x - rect.x)) + ((closest_y - rect.y) * (closest_y - rect.y));
}


void Balloon::Check_Collision_Balloon_Brick_Horizontal()
{
	//Closest point to brick
	int closest_x, closest_y;

	//closest_x offset
	if (rect.x < app->playerModule->player1->rect.x){ closest_x = app->playerModule->player1->rect.x; }
	else if (rect.x > app->playerModule->player1->rect.x + app->playerModule->player1->rect.w){ closest_x = app->playerModule->player1->rect.x + app->playerModule->player1->rect.w; }
	else{ closest_x = rect.x; }

	//closest_y offset
	if (rect.y < app->playerModule->player1->rect.y){ closest_y = app->playerModule->player1->rect.y; }
	else if (rect.y > app->playerModule->player1->rect.y + app->playerModule->player1->rect.h){ closest_y = app->playerModule->player1->rect.y + app->playerModule->player1->rect.h; }
	else{ closest_y = rect.y; }

	//Check distance between points
	//return (rect.h * rect.h) > ((closest_x - rect.x) * (closest_x - rect.x)) + ((closest_y - rect.y) * (closest_y - rect.y));
}