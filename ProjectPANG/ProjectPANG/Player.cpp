#include "Player.h"

Player::Player(Application* app, bool player1)
{
	this->app = app;

	state = STILL;

	character_rect = { 8 * app->windowModule->scale, 168 * app->windowModule->scale, 32 * app->windowModule->scale, 32 * app->windowModule->scale };

	character_const_source_rect = { 544, 0, 32, 32 };
	if (!player1) { character_const_source_rect.y = 32; }

	character_const_rect = new SDL_Rect(character_const_source_rect);
}

void Player::LeftTrigger() //
{
	if (state == LEFT)
		{
			if (update_counter > 4)
			{
				delete[] character_const_rect;
				if (character_const_source_rect.x < 288){ character_const_source_rect.x += 32; }
				else { character_const_source_rect.x = 160; }
				character_const_rect = new SDL_Rect(character_const_source_rect);
				update_counter = 0;
			}
			else { update_counter++; }

			if (character_rect.x > 8 * app->windowModule->scale) //&& no collision with wall
			{
				character_rect.x -= app->playerModule->player_speed;
			}
			
		}
	else // change of direction
	{
		delete[] character_const_rect;
		state = LEFT;
		character_const_source_rect.x = 160;
		character_const_rect = new SDL_Rect(character_const_source_rect);
		update_counter = 0;
	}
}


void Player::RightTrigger()
{
	if (state == RIGHT)
	{
		if (update_counter > 4)
		{
			delete[] character_const_rect;
			if (character_const_source_rect.x < 128){ character_const_source_rect.x += 32; }
			else { character_const_source_rect.x = 0; }
			character_const_rect = new SDL_Rect(character_const_source_rect);
			update_counter = 0;
		}
		else { update_counter++; }

		if (character_rect.x < (SCREEN_WIDTH - 40) * app->windowModule->scale) //&& no collision with wall
		{
			character_rect.x += app->playerModule->player_speed;
		}

	}
	else // change of direction
	{
		delete[] character_const_rect;
		state = RIGHT;
		character_const_source_rect.x = 0;
		character_const_rect = new SDL_Rect(character_const_source_rect);
		update_counter = 0;
	}
}


void Player::UpTrigger()
{
	return;
}


void Player::DownTrigger()
{
	return;
}


void Player::Shoot()
{
	return;
}


void Player::Still()
{
	if (state == STILL){ return; }
	if (state == RIGHT)
	{
		character_const_source_rect.x = 544;
	}
	else
	{
		character_const_source_rect.x = 608;
	}
	state = STILL;
	delete[] character_const_rect;
	character_const_rect = new SDL_Rect(character_const_source_rect);
}