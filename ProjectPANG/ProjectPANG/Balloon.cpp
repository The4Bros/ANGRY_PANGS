#include "Balloon.h"


/*	48*40
32*26
16*14
8*7	*/

Balloon::Balloon(Application* app, int x, int y, int type, int max_height)
{
	
	this->app = app;
	this->type = RED_1;
	rect = { x*app->windowModule->scale, y*app->windowModule->scale, 48 * app->windowModule->scale, 40 * app->windowModule->scale };
	this->max_height = max_height;

	state_balloon_H = BALLOON_RIGHT;
	state_balloon_V = BALLOON_DOWN;


	//---

	alive_balloon = true;
	

	switch (type)
	{
	case 1:
		this->type = RED_1;
		rect = { x*app->windowModule->scale, y*app->windowModule->scale, 48 * app->windowModule->scale, 40 * app->windowModule->scale };
		break;
	case 2:
		this->type = RED_2;
		rect = { x*app->windowModule->scale, y*app->windowModule->scale, 32 * app->windowModule->scale, 26 * app->windowModule->scale };
		break;
	case 3:
		this->type = RED_3;
		rect = { x*app->windowModule->scale, y*app->windowModule->scale, 16 * app->windowModule->scale, 14 * app->windowModule->scale };
		break;
	case 4:
		this->type = RED_4;
		rect = { x*app->windowModule->scale, y*app->windowModule->scale, 8 * app->windowModule->scale, 7 * app->windowModule->scale };
		break;
	case 5:
		this->type = BLUE_1;
		rect = { x*app->windowModule->scale, y*app->windowModule->scale, 48 * app->windowModule->scale, 40 * app->windowModule->scale };
		break;
	case 6:
		this->type = BLUE_2;
		rect = { x*app->windowModule->scale, y*app->windowModule->scale, 32 * app->windowModule->scale, 26 * app->windowModule->scale };
		break;
	case 7:
		this->type = BLUE_3;
		rect = { x*app->windowModule->scale, y*app->windowModule->scale, 16 * app->windowModule->scale, 14 * app->windowModule->scale };
		break;
	case 8:
		this->type = BLUE_4;
		rect = { x*app->windowModule->scale, y*app->windowModule->scale, 8 * app->windowModule->scale, 7 * app->windowModule->scale };
		break;
	case 9:
		this->type = GREEN_1;
		rect = { x*app->windowModule->scale, y*app->windowModule->scale, 48 * app->windowModule->scale, 40 * app->windowModule->scale };
		break;
	case 10:
		this->type = GREEN_2;
		rect = { x*app->windowModule->scale, y*app->windowModule->scale, 32 * app->windowModule->scale, 26 * app->windowModule->scale };
		break;
	case 11:
		this->type = GREEN_3;
		rect = { x*app->windowModule->scale, y*app->windowModule->scale, 16 * app->windowModule->scale, 14 * app->windowModule->scale };
		break;
	case 12:
		this->type = GREEN_4;
		rect = { x*app->windowModule->scale, y*app->windowModule->scale, 8 * app->windowModule->scale, 7 * app->windowModule->scale };
		break;


	default:
		break;
	}

	bounce_height = bounce_height_start; // fix this
	
}



void Balloon::Update()
{
	// 8 * app->windowModule->scale;   left coord
	// (376 * app->windowModule->scale) - rect.w;  right coord
	// 168 down floor y coord
	

	
	
//						-- VERTICAL --	

		switch (state_balloon_V)
		{
		case BALLOON_UP:

			if(/* rect.y > 8 * app->windowModule->scale) &&*/ bounce_height > 0)
			{
				rect.y = rect.y - gravity;
				//gravity = gravity - 0.1f;
				gravity_strenght = gravity_strenght--;
				if (gravity_strenght % 10 == 0)
				{
					gravity--;
				}
				bounce_height--;
			
			}
			else
			{
				
				state_balloon_V = BALLOON_DOWN;
				bounce_height = bounce_height_start; // fix this
				gravity = gravity_start;
				gravity_strenght = gravity_start;
			}
			break;

		case BALLOON_DOWN:

			if (rect.y < 167 * app->windowModule->scale)
			{
				rect.y = rect.y + gravity;
				//gravity = gravity ; // timer please
				
				gravity_strenght = gravity_strenght++;
				if (gravity_strenght%10==0)
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

			if (rect.x < 376 * app->windowModule->scale) rect.x += horizontal_speed;
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

}



void Balloon::Reset(unsigned int x, unsigned int y, unsigned int type, unsigned int max_height)
{
	while (alive_balloon)
	{
	
	
	}
	this->type = RED_1;
	rect = { x, y, 16, 16 };
	this->max_height = max_height;
}