#include "Balloon.h"



Balloon::Balloon(Application* app, int x, int y, int type, int max_height)
{
	gravity = 2;
	horizontal_speed = 2;
	gravity_aux = 2;
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



void Balloon::Update()
{



	Check_Collision_Balloon_Players();     //									 COLLISIONS HERE! remove comments !

	//						-- VERTICAL --	

	switch (state_balloon_V)
	{
	case BALLOON_UP:

		if ((rect.y > 8 * app->windowModule->scale) && gravity != 0)
		{
			rect.y = rect.y - gravity;
			gravity_aux = gravity_aux--;

			if (gravity_aux % 8 == 0) gravity--;



		}
		else
		{
			//Hit();
			state_balloon_V = BALLOON_DOWN;

			gravity = 0;
			gravity_aux = 1;
		}
		break;

	case BALLOON_DOWN:

		if (rect.y + rect.h < 199 * app->windowModule->scale)
		{
			rect.y = rect.y + gravity;


			gravity_aux = gravity_aux++;
			if (gravity_aux % 8 == 0)
			{
				gravity++;
			}


		}
		else
		{
			if (type < 3) gravity = 9;
			else if (type < 6) gravity = 8;
			else if (type < 9) gravity = 7;
			else gravity = 6;
			state_balloon_V = BALLOON_UP;
			gravity_aux = 1;
		}
		break;

	default:
		break;
	}

	//						-- HORIZONTAL --

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




	switch (type)
	{
	case 0:
		this->type = RED_2;
		rect.x = rect.x - (rect.w*app->windowModule->scale);
		if (BALLOON_RIGHT)
		{
			BALLOON_LEFT;
		}
		break;
	case 2:
		this->type = BLUE_2;

		this->type = BLUE_2;
		rect.x = rect.x - (rect.w*app->windowModule->scale);
		if (BALLOON_RIGHT)
		{
			BALLOON_LEFT;
		}


		break;
	case 3:
		this->type = GREEN_2;

		break;
	case 4:
		this->type = RED_3;

		break;
	case 5:
		this->type = BLUE_3;

		break;
	case 6:
		this->type = GREEN_3;

		break;
	case 7:
		this->type = RED_4;

		break;
	case 8:
		this->type = BLUE_4;

		break;
	case 9:
		this->type = GREEN_4;

		break;

	default:
		rect = { 0, 0, 0, 0 };

		break;

	}

	app->entityManagerModule->balloons->push_back(new Balloon(app, rect.x + rect.w, rect.y, type, max_height));


}




void Balloon::Reset(unsigned int x, unsigned int y, unsigned int type, unsigned int max_height)
{
	gravity = 2;
	horizontal_speed = 2;
	gravity_aux = 2;
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





void Balloon::Check_Collision_Balloon_Players()
{
	if (rect.x < app->playerModule->player1->rect.x + app->playerModule->player1->rect.w
		&& rect.x + rect.w > app->playerModule->player1->rect.x
		&& rect.y < app->playerModule->player1->rect.y + app->playerModule->player1->rect.h
		&& rect.h + rect.y > app->playerModule->player1->rect.y)
	{
		if (Deep_Check_Collision_Balloon_Player1()){ return; } // no need to check player2 if player1 got hit
	}

	if (app->playerModule->player2 != NULL)
	{
		if (rect.x < app->playerModule->player2->rect.x + app->playerModule->player2->rect.w
			&& rect.x + rect.w > app->playerModule->player2->rect.x
			&& rect.y < app->playerModule->player2->rect.y + app->playerModule->player2->rect.h
			&& rect.h + rect.y > app->playerModule->player2->rect.y)
		{
			Deep_Check_Collision_Balloon_Player2();
		}
	}
}


bool Balloon::Deep_Check_Collision_Balloon_Player1()
{
	//Closest point to ball
	int closest_x, closest_y;

	//closest_x offset
	if (rect.x < app->playerModule->player1->rect.x){ closest_x = app->playerModule->player1->rect.x; } // Player to the right
	else{ closest_x = app->playerModule->player1->rect.x + app->playerModule->player1->rect.w; } // Player to the left

	//closest_y offset
	if (rect.y < app->playerModule->player1->rect.y){ closest_y = app->playerModule->player1->rect.y; } // Player bellow
	else{ closest_y = app->playerModule->player1->rect.y + app->playerModule->player1->rect.h; } // Player above

	//Check distance between points
	if (((rect.h * rect.w) / 4) >((closest_x - (rect.x + (rect.w / 2))) * (closest_x - (rect.x + (rect.w / 2)))) + ((closest_y - (rect.y + (rect.h / 2))) * (closest_y - (rect.y + (rect.h / 2)))))
	{
		app->playerModule->player1->Hit(&rect); // true if player1 got hit
		return true;
	}

	return false;
}

void Balloon::Deep_Check_Collision_Balloon_Player2()
{
	//Closest point to ball
	int closest_x, closest_y;

	//closest_x offset
	if (rect.x + rect.w < app->playerModule->player2->rect.x){ closest_x = app->playerModule->player2->rect.x; }
	else{ closest_x = app->playerModule->player2->rect.x + app->playerModule->player2->rect.w; }

	//closest_y offset
	if (rect.y + rect.h < app->playerModule->player2->rect.y){ closest_y = app->playerModule->player2->rect.y; }
	else{ closest_y = app->playerModule->player2->rect.y + app->playerModule->player2->rect.h; }

	//Check distance between points
	if (((rect.h * rect.w) / 4) > ((closest_x - (rect.x + (rect.w / 2))) * (closest_x - (rect.x + (rect.w / 2)))) + ((closest_y - (rect.y + (rect.h / 2))) * (closest_y - (rect.y + (rect.h / 2)))))
	{
		app->playerModule->player2->Hit(&rect); // true if player2 got hit
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