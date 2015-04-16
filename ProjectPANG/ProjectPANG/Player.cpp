#include "Player.h"

Player::Player(Application* app, bool player1)
{
	this->app = app;
	shielded = false;

	state = STILL;
	shoot_key_pressed = false;
	current_weapon = WEAPON_DOUBLE_HARPOON;
	hit_State = HIT_RIGHT_UP;
	source_index = 17;

	harpoon[0] = new Harpoon(app);
	harpoon[1] = new Harpoon(app);

	rect = { 8 * app->windowModule->scale, 168 * app->windowModule->scale, 32 * app->windowModule->scale, 32 * app->windowModule->scale };

	if (player1)
	{
		for (int i = 0; i < 23; i++)
		{
			source_rect[i] = new SDL_Rect({ i * 32, 0, 32, 32 });
		}
		source_rect[23] = new SDL_Rect({ 736, 0, 51, 32 });
		source_rect[24] = new SDL_Rect({ 787, 0, 51, 32 });
	}
	else
	{
		for (int i = 0; i < 23; i++)
		{
			source_rect[i] = new SDL_Rect({ i * 32, 32, 32, 32 });
		}
		source_rect[23] = new SDL_Rect({ 736, 32, 51, 32 });
		source_rect[24] = new SDL_Rect({ 787, 32, 51, 32 });

		// update position
		setPos(app->sceneModule->stage_arrangement.player_pos[2], app->sceneModule->stage_arrangement.player_pos[3]);

	}

}

void Player::LeftTrigger()
{
	if (state == LEFT)
		{
			if (update_counter > 4) // ticks till update
			{
				if (source_index < 9){ source_index++; }
				else { source_index = 5; }
				update_counter = 0;
			}

			if (rect.x > 8 * app->windowModule->scale) //&& no collision with brick
			{
				rect.x -= app->playerModule->player_speed;
			}
		}

	else if (state == SHOOT_LEFT || state == SHOOT_RIGHT) // was shooting
	{
		if (update_counter > 4)
		{
			state = LEFT;
			source_index = 5;
			update_counter = 0;
		}
	}
	else if (state == RIGHT || state == STILL)// change of direction
	{
		state = LEFT;
		source_index = 5;
		update_counter = 0;
	}
}

void Player::RightTrigger()
{
	if (state == RIGHT)
	{
		if (update_counter > 4) // ticks till update
		{
			if (source_index < 4){ source_index++; }
			else { source_index = 0; }
			update_counter = 0;
		}

		if (rect.x < (SCREEN_WIDTH - 40) * app->windowModule->scale) //&& no collision with brick
		{
			rect.x += app->playerModule->player_speed;
		}

	}
	else if (state == SHOOT_LEFT || state == SHOOT_RIGHT) // was shooting
	{
		if (update_counter > 4)
		{
			state = RIGHT;
			source_index = 0;
			update_counter = 0;
		}
	}
	else if (state == LEFT || state == STILL)// change of direction
	{
		state = RIGHT;
		source_index = 0;
		update_counter = 0;
	}
}

void Player::UpTrigger()
{
	SDL_Rect killer = { 400, 0, 0, 0 };
	Hit(&killer);
	return;
}

void Player::DownTrigger()
{
	SDL_Rect killer = { 0, 0, 0, 0 };
	Hit(&killer);
	return;
}


void Player::Shoot()
{
	
	if (shoot_key_pressed || state == HIT) { return; }
	shoot_key_pressed = true;

	switch (current_weapon)
	{
	case WEAPON_DOUBLE_HARPOON:
		if (!harpoon[1]->alive)
		{
			shoot_update_counter = 0;

			if (state == RIGHT || source_index == 17) // leaning left
			{
				source_index = 18;
				update_counter = 0;
				harpoon[1]->Shoot_Harpoon(rect.y, rect.x + (14 * app->windowModule->scale));
				state = SHOOT_RIGHT;
			}
			else if (state == LEFT || source_index == 19) // leaning right
			{
				source_index = 20;
				update_counter = 0;
				harpoon[1]->Shoot_Harpoon(rect.y, rect.x + (10 * app->windowModule->scale));
				state = SHOOT_LEFT;
			}

			else { harpoon[1]->Shoot_Harpoon(rect.y, rect.x + (12 * app->windowModule->scale)); } // on stairs
		}

		else if (!harpoon[0]->alive)
		{
			shoot_update_counter = 0;

			if (state == RIGHT || source_index == 17) // leaning left
			{
				source_index = 18;
				update_counter = 0;
				harpoon[0]->Shoot_Harpoon(rect.y, rect.x + (14 * app->windowModule->scale));
				state = SHOOT_RIGHT;
			}
			else if (state == LEFT || source_index == 19) // leaning right
			{
				source_index = 20;
				update_counter = 0;
				harpoon[0]->Shoot_Harpoon(rect.y, rect.x + (10 * app->windowModule->scale));
				state = SHOOT_LEFT;
			}

			else { harpoon[0]->Shoot_Harpoon(rect.y, rect.x + (12 * app->windowModule->scale)); } // on stairs
		}
		break;

	case WEAPON_HARPOON:
		if (!harpoon[0]->alive)
		{
			shoot_update_counter = 0;

			if (state == RIGHT || source_index == 17) // leaning left
			{
				source_index = 18;
				update_counter = 0;
				harpoon[0]->Shoot_Harpoon(rect.y, rect.x + (14 * app->windowModule->scale));
				state = SHOOT_RIGHT;
			}
			else if (state == LEFT || source_index == 19) // leaning right
			{
				source_index = 20;
				update_counter = 0;
				harpoon[0]->Shoot_Harpoon(rect.y, rect.x + (10 * app->windowModule->scale));
				state = SHOOT_LEFT;
			}

			else { harpoon[0]->Shoot_Harpoon(rect.y, rect.x + (12 * app->windowModule->scale)); } // on stairs
		}
		break;

	case WEAPON_GRAPPLE:
		if (!harpoon[0]->alive)
		{
			shoot_update_counter = 0;

			if (state == RIGHT || source_index == 17) // leaning left
			{
				source_index = 18;
				update_counter = 0;
				harpoon[0]->Shoot_Grapple(rect.y + (2 * app->windowModule->scale), rect.x + (14 * app->windowModule->scale));
				state = SHOOT_RIGHT;
			}
			else if (state == LEFT || source_index == 19) // leaning right
			{
				source_index = 20;
				update_counter = 0;
				harpoon[0]->Shoot_Grapple(rect.y + (2 * app->windowModule->scale), rect.x + (10 * app->windowModule->scale));
				state = SHOOT_LEFT;
			}

			else { harpoon[0]->Shoot_Grapple(rect.y + (2 * app->windowModule->scale), rect.x + (12 * app->windowModule->scale)); } // on stairs
		}
		break;

	case WEAPON_SHOTGUN:
		break;
	}
}


void Player::Still()
{
	if (state == HIT || state == UP || state == DOWN){ return; }
	if (update_counter > 4)
	{
		switch (state)
		{
		case LEFT:
		case SHOOT_LEFT:
			state = STILL;
			source_index = 19;
			break;

		case RIGHT:
		case SHOOT_RIGHT:
			state = STILL;
			source_index = 17;
			break;
		default:
			break;
		}
	}
}

void Player::Hit(SDL_Rect* killer)
{
	if (shielded){ shielded = false; } // kill shield

	else
	{
		if (rect.x + (rect.w / 2) <= killer->x + (killer->w / 2))
		{
			source_index = 21;
			hit_State = HIT_LEFT_UP;
		}
		else
		{
			source_index = 22;
			hit_State = HIT_RIGHT_UP;
		}

		height = rect.y;
		update_counter = 0;
		shoot_update_counter = 0;
		state = HIT;
	}
}


void Player::Update()
{

	if (shoot_update_counter > 30)
	{
		if (state == HIT)
		{
			switch (hit_State)
			{
			case HIT_LEFT_UP:
				rect.x -= app->windowModule->scale;
				if (rect.y < 9 * app->windowModule->scale) // && no collision with bricks
				{
					hit_State = HIT_LEFT_DOWN;
				}
				else
				{
					rect.y = height - ((app->windowModule->scale) * ((update_counter * update_counter) / 10));
				}
				break;

			case HIT_LEFT_DOWN:
				rect.x -= app->windowModule->scale;

				if (rect.y > 167 * app->windowModule->scale) // && no collision with bricks
				{
					hit_State = HIT_LEFT_UP;
				}
				else
				{
					rect.y = height + ((app->windowModule->scale) *  ((update_counter * update_counter) / 10));
				}
				break;

			case HIT_RIGHT_UP:
				rect.x += app->windowModule->scale;
				if (rect.y < 9 * app->windowModule->scale) // && no collision with bricks
				{
					hit_State = HIT_LEFT_UP;
				}
				else
				{
					rect.y = height - ((app->windowModule->scale) *  ((update_counter * update_counter) / 10));
				}
				break;

			case HIT_RIGHT_DOWN:
				rect.x += app->windowModule->scale;
				if (rect.y > 167 * app->windowModule->scale)
				{
					height = rect.y;
					hit_State = HIT_LEFT_UP;
				}
				// else if() no collision with bricks
				// { height = rect.y
				else
				{
					rect.y = height + ((app->windowModule->scale) *  ((update_counter * update_counter) / 10));
				}
				break;
			}

			update_counter++;

			
		}

		else { shoot_update_counter++; }

		return;
	}



	// if no floor: make fall
	if (rect.y < 168 && state != UP && state != DOWN) // not on ground
	{
		/*
		
		if () // collision with brick
		
		else // fall
		{
			rect.y += 3 * app->windowModule->scale;
		}
		
		*/
	}

	update_counter++;
	if (shoot_update_counter < 10){ shoot_update_counter++; }
	else { shoot_key_pressed = false; shoot_update_counter = 0; }

	switch (current_weapon)
	{
	case WEAPON_DOUBLE_HARPOON:
		if (harpoon[1]->alive){ harpoon[1]->Update(); }

	case WEAPON_HARPOON:
		if (harpoon[0]->alive){ harpoon[0]->Update(); }
		break;

	case WEAPON_GRAPPLE:
		if (harpoon[0]->alive){ harpoon[0]->Update(); }
		break;

	case WEAPON_SHOTGUN:
		break;
	}
}


void Player::setPos(unsigned int x, unsigned int y)
{
	rect.x = x * app->windowModule->scale;
	rect.y = y * app->windowModule->scale;
}