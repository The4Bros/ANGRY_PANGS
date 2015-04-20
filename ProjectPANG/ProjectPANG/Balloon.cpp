#include "Balloon.h"


/*	48*40
32*26
16*14
8*7	*/

Balloon::Balloon(Application* app, int x, int y, int type, int max_height)
{
	
	this->app = app;
	rect = { x*app->windowModule->scale, y*app->windowModule->scale, 48 * app->windowModule->scale, 40 * app->windowModule->scale };
	this->max_height = max_height;

	state_balloon_H = BALLOON_RIGHT;
	state_balloon_V = BALLOON_DOWN;

	bounce_height = max_height*app->windowModule->scale;
	bounce_height_start = bounce_height;


	//---

	alive_balloon = true;
	

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

		if (/* rect.y > 8 * app->windowModule->scale) &&*/ gravity != 0)
		{
			rect.y = rect.y - gravity;
			//gravity = gravity - 0.1f;
			gravity_strenght = gravity_strenght--;
			if (gravity_strenght % 8 == 0)
			{
				gravity--;
			}
			bounce_height--;

		}
		else
		{
			Hit();
			state_balloon_V = BALLOON_DOWN;
			bounce_height = bounce_height_start; // fix this
			gravity = 0;
			gravity_strenght = gravity_start;
		}
		break;

	case BALLOON_DOWN:

		if (rect.y + rect.h < 199 * app->windowModule->scale)
		{
			rect.y = rect.y + gravity;
			//gravity = gravity ; // timer please

			gravity_strenght = gravity_strenght++;
			if (gravity_strenght % 8 == 0)
			{
				gravity++;
			}


		}
		else
		{
			state_balloon_V = BALLOON_UP;
			bounce_height = bounce_height_start; // fix this
			//gravity = gravity_start;
			gravity_strenght = gravity_start;
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
	int aux_type;
	int aux_max_height;
	SDL_Rect aux_rect;

	/*
	switch (type)
	{
	case RED_1:
		this->type = RED_1;
		rect.h
		rect = { x*app->windowModule->scale, y*app->windowModule->scale, 48 * app->windowModule->scale, 40 * app->windowModule->scale };
		app->entityManagerModule->balloons->push_back(new Balloon(rect.x, rect.y, type + 3, max_height));
		//app->entityManagerModule->particles->push_back(new Particles(...));
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





	 default:
		rect = {0, 0, 0, 0};


	}
	*/







	if (type <= 9)
	{
		aux_rect = rect;

		aux_rect.x = rect.x - 10;
		aux_rect.y = rect.y - 10;

		aux_type = type + 4;

		aux_max_height = max_height; // change to lower height value of the type

		//tmp_Balloon_hit = new Balloon(app, aux_rect.x, aux_rect.y, aux_type, aux_max_height);

		
		//app->renderModule->Print(app->texturesModule->balls_sprite, app->entityManagerModule->source_balloon_rect[type], &rect);

		aux_rect.x = rect.x + 10;
		aux_rect.y = rect.y - 10;

		//tmp_Balloon_hit2 = new Balloon(app, aux_rect.x, aux_rect.y, aux_type, aux_max_height);

		//app->renderModule->Print(app->texturesModule->balls_sprite, app->entityManagerModule->source_balloon_rect[type], &rect);
		
	
		//tmp_Balloon_hit->Update();
		//tmp_Balloon_hit2->Update();
		
	}
	else
	{
		// delete current balloon
	}
	
}



void Balloon::Reset(unsigned int x, unsigned int y, unsigned int type, unsigned int max_height)
{
	rect = { x*app->windowModule->scale, y*app->windowModule->scale, 48 * app->windowModule->scale, 40 * app->windowModule->scale };
	this->max_height = max_height;



	state_balloon_H = BALLOON_RIGHT;
	state_balloon_V = BALLOON_DOWN;

	alive_balloon = true;


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


	bounce_height = bounce_height_start; // fix this
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