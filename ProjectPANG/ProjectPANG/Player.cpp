#include "Player.h"

Player::Player(Application* app, bool player1)
{
	this->app = app;

	state = STILL;
	alive = true;
	current_weapon = WEAPON_HARPOON;

	harpoon[2] = new Harpoon(app);

	rect = { 8 * app->windowModule->scale, 168 * app->windowModule->scale, 32 * app->windowModule->scale, 32 * app->windowModule->scale };

	player1 ? source_rect = { 544, 0, 32, 32 } : source_rect = { 544, 32, 32, 32 };

	const_rect = new SDL_Rect(source_rect);
}

void Player::LeftTrigger()
{
	if (state == LEFT)
		{
			if (update_counter > 4)
			{
				delete[] const_rect;
				if (source_rect.x < 288){ source_rect.x += 32; }
				else { source_rect.x = 160; }
				const_rect = new SDL_Rect(source_rect);
				update_counter = 0;
			}
			else { update_counter++; }

			if (rect.x > 8 * app->windowModule->scale) //&& no collision with wall
			{
				rect.x -= app->playerModule->player_speed;
			}
			
		}
	else // change of direction
	{
		delete[] const_rect;
		state = LEFT;
		source_rect.x = 160;
		const_rect = new SDL_Rect(source_rect);
		update_counter = 0;
	}
}

void Player::RightTrigger()
{
	if (state == RIGHT)
	{
		if (update_counter > 4)
		{
			delete[] const_rect;
			if (source_rect.x < 128){ source_rect.x += 32; }
			else { source_rect.x = 0; }
			const_rect = new SDL_Rect(source_rect);
			update_counter = 0;
		}
		else { update_counter++; }

		if (rect.x < (SCREEN_WIDTH - 40) * app->windowModule->scale) //&& no collision with wall
		{
			rect.x += app->playerModule->player_speed;
		}

	}
	else // change of direction
	{
		delete[] const_rect;
		state = RIGHT;
		source_rect.x = 0;
		const_rect = new SDL_Rect(source_rect);
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
	switch (current_weapon)
	{
	case WEAPON_DOUBLE_HARPOON:
		if (!harpoon[1]->alive)
		{
			harpoon[1]->Shoot_Harpoon(rect);
			if (state == RIGHT || source_rect.x == 544){ harpoon[1]->rect.x -= 6; }
			else if (state == UP || state == DOWN) { harpoon[1]->rect.x += 5; }
			break;
		}
	case WEAPON_HARPOON:
		if (!harpoon[0]->alive)
		{
			harpoon[0]->Shoot_Harpoon(rect);
			if (state == RIGHT || source_rect.x == 544){ harpoon[1]->rect.x -= 6; }
			else if (state == UP || state == DOWN) { harpoon[1]->rect.x += 5; }
		}
		break;
	case WEAPON_GRAPPLE:
		if (!harpoon[0]->alive)
		{
			harpoon[0]->Shoot_Grapple(rect);
			if (state == RIGHT || source_rect.x == 544){}
			else if (state == UP || state == DOWN) {}
		}
		break;
	case WEAPON_SHOTGUN:
		break;
	}

	if (state == RIGHT || source_rect.x == 544){ source_rect.x = 640; }
	else if (state == LEFT || source_rect.x == 608){ source_rect.x = 576; }

	state = SHOOT;
	update_counter = 0;
	delete[] const_rect;
	const_rect = new SDL_Rect(source_rect);
}


void Player::Still()
{
	if (state == SHOOT)
	{
		if (update_counter > 2)
		{
			if (source_rect.x = 576){ source_rect.x = 544; state = RIGHT; }
			else { source_rect.x = 608; state = LEFT;  }

			update_counter = 0;
		}
		else
		{
			update_counter++;
		}
	}
	else
	{
		if (state == RIGHT){ source_rect.x = 544; }
		else{ source_rect.x = 608; }

		state = STILL;

		delete[] const_rect;
		const_rect = new SDL_Rect(source_rect);
	}
	
}

void Player::Update()
{
	switch (current_weapon)
	{
	case WEAPON_DOUBLE_HARPOON:
		if (harpoon[1]->alive)
		{
			harpoon[1]->Update();
		}
	case WEAPON_HARPOON:
		if (harpoon[0]->alive)
		{
			harpoon[0]->Update();
		}
		break;
	case WEAPON_GRAPPLE:
		if (harpoon[0]->alive)
		{
			harpoon[0]->Update();
		}
		break;
	case WEAPON_SHOTGUN:
		break;
	}
}


void Player::setPos(unsigned int x, unsigned int y)
{
	rect.x = x;
	rect.y = y;
}