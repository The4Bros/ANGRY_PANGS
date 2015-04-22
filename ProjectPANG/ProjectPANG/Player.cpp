#include "Player.h"

Player::Player(Application* app, bool player1)
{
	this->app = app;
	
	lives = 3;
	shielded = false;
	state = STILL;
	shoot_key_pressed = false;
	current_weapon = WEAPON_DOUBLE_HARPOON;
	hit_State = HIT_RIGHT_UP;
	source_index = 17;
	stair_update_counter = 0;
	current_stair = NULL;


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

		if (app->sceneModule != NULL) // Scene initalized
		{
			Reset(app->sceneModule->stage_arrangement.player_pos[0], app->sceneModule->stage_arrangement.player_pos[1]);
		}
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
		if (app->sceneModule != NULL) // Scene initalized
		{
			Reset(app->sceneModule->stage_arrangement.player_pos[2], app->sceneModule->stage_arrangement.player_pos[3]);
		}
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
	if (current_stair == NULL)
	{
		if (stair_update_counter > 30)
		{
			if (Check_Collision_Player_Stair())
			{
				stair_update_counter = 0;
				source_index = 15;
				state = ON_STAIR;
			}
		}
		else{ stair_update_counter++; }
	}
	else
	{
		if (rect.y + (16 * app->windowModule->scale) > current_stair->rect.y) // still on stair
		{
			rect.y -= app->playerModule->player_speed;

			if (update_counter > 8) // ticks till update
			{
				if (source_index < 13){ source_index++; }
				else { source_index = 10; }
				update_counter = 0;
			}
		}

		else if (stair_update_counter < 8)
		{
			stair_update_counter++;
			source_index = 16;
		}
		else // no longer on stair
		{
			state = STILL;
			source_index = 17;
			rect.y = current_stair->rect.y - rect.h;
			stair_update_counter = 0;
			current_stair = NULL;
		}
	}

}

void Player::DownTrigger()
{
	if (current_stair == NULL)
	{
		if (stair_update_counter > 30)
		{
			if (rect.y < 168 && Check_Collision_Player_Stair())
			{
				stair_update_counter = 0;
				source_index = 16;
				state = ON_STAIR;
			}
		}
		else{ stair_update_counter++; }
	}
	else
	{
		if (rect.y + rect.h < current_stair->rect.y + current_stair->rect.h) // still on stair
		{
			rect.y += app->playerModule->player_speed;

			if (update_counter > 8) // ticks till update
			{
				if (source_index > 10){ source_index--; }
				else { source_index = 13; }
				update_counter = 0;
			}
		}
		else // no longer on stair
		{
			state = STILL;
			source_index = 17;
			rect.y = current_stair->rect.y - rect.h;
			stair_update_counter = 0;
			current_stair = NULL;
		}
	}
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
				app->entityManagerModule->particles->push_back(new Particles(app, app->entityManagerModule->particles->Count(), 13, rect.x + (10 * app->windowModule->scale), rect.y - (4 * app->windowModule->scale)));
				state = SHOOT_RIGHT;
			}
			else if (state == LEFT || source_index == 19) // leaning right
			{
				source_index = 20;
				update_counter = 0;
				harpoon[1]->Shoot_Harpoon(rect.y, rect.x + (10 * app->windowModule->scale));
				app->entityManagerModule->particles->push_back(new Particles(app, app->entityManagerModule->particles->Count(), 13, rect.x + (6 * app->windowModule->scale), rect.y - (4 * app->windowModule->scale)));
				state = SHOOT_LEFT;
			}

			else // on stairs
			{
				harpoon[1]->Shoot_Harpoon(rect.y, rect.x + (12 * app->windowModule->scale));
				app->entityManagerModule->particles->push_back(new Particles(app, app->entityManagerModule->particles->Count(), 13, rect.x + (8 * app->windowModule->scale), rect.y - (4 * app->windowModule->scale)));
			}
		}

		else if (!harpoon[0]->alive)
		{
			shoot_update_counter = 0;

			if (state == RIGHT || source_index == 17) // leaning left
			{
				source_index = 18;
				update_counter = 0;
				harpoon[0]->Shoot_Harpoon(rect.y, rect.x + (14 * app->windowModule->scale));
				app->entityManagerModule->particles->push_back(new Particles(app, app->entityManagerModule->particles->Count(), 13, rect.x + (10 * app->windowModule->scale), rect.y - (4 * app->windowModule->scale)));
				state = SHOOT_RIGHT;
			}
			else if (state == LEFT || source_index == 19) // leaning right
			{
				source_index = 20;
				update_counter = 0;
				harpoon[0]->Shoot_Harpoon(rect.y, rect.x + (10 * app->windowModule->scale));
				app->entityManagerModule->particles->push_back(new Particles(app, app->entityManagerModule->particles->Count(), 13, rect.x + (6 * app->windowModule->scale), rect.y - (4 * app->windowModule->scale)));
				state = SHOOT_LEFT;
			}

			else // on stairs
			{
				harpoon[0]->Shoot_Harpoon(rect.y, rect.x + (12 * app->windowModule->scale));
				app->entityManagerModule->particles->push_back(new Particles(app, app->entityManagerModule->particles->Count(), 13, rect.x + (8 * app->windowModule->scale), rect.y - (4 * app->windowModule->scale)));
			}
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
				app->entityManagerModule->particles->push_back(new Particles(app, app->entityManagerModule->particles->Count(), 13, rect.x + (10 * app->windowModule->scale), rect.y - (8 * app->windowModule->scale)));
				state = SHOOT_RIGHT;
			}
			else if (state == LEFT || source_index == 19) // leaning right
			{
				source_index = 20;
				update_counter = 0;
				harpoon[0]->Shoot_Harpoon(rect.y, rect.x + (10 * app->windowModule->scale));
				app->entityManagerModule->particles->push_back(new Particles(app, app->entityManagerModule->particles->Count(), 13, rect.x + (6 * app->windowModule->scale), rect.y - (8 * app->windowModule->scale)));
				state = SHOOT_LEFT;
			}

			else // on stairs
			{
				harpoon[0]->Shoot_Harpoon(rect.y, rect.x + (12 * app->windowModule->scale));
				app->entityManagerModule->particles->push_back(new Particles(app, app->entityManagerModule->particles->Count(), 13, rect.x + (8 * app->windowModule->scale), rect.y - (8 * app->windowModule->scale)));
			}
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
		//--------------------------------------------------------------
		break;
	}
}


void Player::Still()
{
	if (state == HIT){ return; }
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
		case ON_STAIR:
			source_index = 15;
			break;
		default:
			break;
		}
	}
}

void Player::Hit(SDL_Rect* killer)
{
	hit_State = HIT_LEFT_UP;
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

		ticks = 0;
		player_gravity = 10;


		alive = false;

		height = rect.y;
		update_counter = 0;
		shoot_update_counter = 0;
		state = HIT;
		app->sceneModule->game_state = PLAYER_KILLED;
		app->sceneModule->update_counter = 0;

		//app->sceneModule->reset_stage();
	}
}


void Player::Update()
{
	// PLAYER HIT___________________________________________________________________________________________________________________
	if (state == HIT)
	{
		if (shoot_update_counter > 30)				//4rth bounce -> player killed(this)
		{
			switch (hit_State)
			{
			case HIT_LEFT_UP:
				//rect.x -= app->windowModule->scale;
				if ((rect.y > 8 * app->windowModule->scale) && player_gravity != 0) // && no collision with bricks
				{
					rect.x -= 2;
					rect.y = rect.y - player_gravity;
					ticks--;
					if (ticks % 8 == 0) player_gravity--;
					if (rect.x < 8 * app->windowModule->scale)hit_State = HIT_RIGHT_UP;
					/*
					height = rect.y;
					update_counter = 0;
					hit_State = HIT_LEFT_DOWN;*/
				}
				else
				{
					hit_State = HIT_LEFT_DOWN;

					player_gravity = 0;
					ticks = 1;
					//rect.y = height - ((6 * app->windowModule->scale) + ((update_counter * update_counter) / 9));
				}
				break;

			case HIT_LEFT_DOWN:
				//rect.x -= app->windowModule->scale;

				if (rect.y + rect.h < 199 * app->windowModule->scale) // && no collision with bricks
				{
					rect.x -= 2;
					rect.y = rect.y + player_gravity;
					ticks--;
					if (ticks % 8 == 0) player_gravity++;
					if (rect.x< 8 * app->windowModule->scale)hit_State = HIT_RIGHT_DOWN;
					/*height = rect.y;
					update_counter = 0;
					hit_State = HIT_LEFT_UP;*/
				}
				else
				{
					hit_State = HIT_LEFT_UP;
					ticks = 1;
					player_gravity=player_gravity-3;
					//rect.y = height + ((6 * app->windowModule->scale) -  ((update_counter * update_counter) / 9));
				}
				break;

			case HIT_RIGHT_UP:
				//rect.x += app->windowModule->scale;
				if ((rect.y > 8 * app->windowModule->scale) && player_gravity != 0) // && no collision with bricks
				{
					rect.x += 2;
					rect.y = rect.y - player_gravity;
					ticks--;
					if (ticks % 8 == 0) player_gravity--;
					if (rect.x - rect.w > 376 * app->windowModule->scale)hit_State = HIT_LEFT_UP;
					//hit_State = HIT_LEFT_UP;
				}
				else
				{
					hit_State = HIT_RIGHT_DOWN;

					player_gravity = 0;
					ticks = 1;
					
					//rect.y = height - ((app->windowModule->scale) *  ((update_counter * update_counter) / 10));
				}
				break;

			case HIT_RIGHT_DOWN:
				//rect.x += app->windowModule->scale;

				if (rect.y + rect.h < 199 * app->windowModule->scale)
				{

					rect.x -= 2;
					rect.y = rect.y + player_gravity;
					ticks--;
					if (ticks % 8 == 0) player_gravity++;
					if (rect.x + rect.w > 376 * app->windowModule->scale)hit_State = HIT_LEFT_DOWN;
					//height = rect.y;
					//hit_State = HIT_LEFT_UP;
				}
				// else if() no collision with bricks
				// { height = rect.y
				else
				{
					hit_State = HIT_RIGHT_UP;
					ticks = 1;
					player_gravity = player_gravity - 3;;
					//rect.y = height + ((app->windowModule->scale) *  ((update_counter * update_counter) / 10));
				}
				break;
			}

			update_counter++;


		}

		else { shoot_update_counter++; }

		return;
	}







	// PLAYER NORMAL___________________________________________________________________________________________________________________
	if (app->sceneModule->game_state == PLAYING)
	{
		// if no floor: make fall
		if (rect.y < 168 && state != ON_STAIR) // not on ground
		{
			if (!Check_Collision_Player_Verticals()) { rect.y += app->windowModule->scale; } // no bricks bellow, fall
		}

		update_counter++;
		if (shoot_update_counter < 10){ shoot_update_counter++; }
		else { shoot_key_pressed = false; shoot_update_counter = 0; }

		if (harpoon[1]->alive){ harpoon[1]->Update(); }
		if (harpoon[0]->alive){ harpoon[0]->Update(); }

		//-------------------------------------------------------
		// shotgun update
		//-------------------------------------------------------
	}





}


void Player::Reset(unsigned int x, unsigned int y)
{
	rect.x = x * app->windowModule->scale;
	rect.y = y * app->windowModule->scale;

	harpoon[0]->alive = false;
	harpoon[1]->alive = false;

	shielded = false;
	current_stair = NULL;
	state = STILL;
	shoot_key_pressed = false;
	current_weapon = WEAPON_DOUBLE_HARPOON;
	hit_State = HIT_RIGHT_UP;
	source_index = 17;
	stair_update_counter = 0;
}



bool Player::Check_Collision_Player_Brick_Horizontal()
{
	SDL_Rect tmp_rect;

	for (unsigned int i = 0; i < app->entityManagerModule->bricks->Count(); i++)
	{
		tmp_rect = (*app->entityManagerModule->bricks->at(i))->rect;

		if (rect.x - app->windowModule->scale < tmp_rect.x + tmp_rect.w
			&& rect.x + rect.w > tmp_rect.x - app->windowModule->scale
			&& rect.y < tmp_rect.y + tmp_rect.h
			&& rect.h + rect.y  > tmp_rect.y + tmp_rect.h)
		{
			return true;
		}
	}
	return false;
}

bool Player::Check_Collision_Player_Verticals()
{
	SDL_Rect tmp_rect;

	for (unsigned int i = 0; i < app->entityManagerModule->bricks->Count(); i++)
	{
		tmp_rect = (*app->entityManagerModule->bricks->at(i))->rect;

		if (rect.x  < tmp_rect.x + tmp_rect.w
			&& rect.x + rect.w > tmp_rect.x
			&& rect.y - app->windowModule->scale < tmp_rect.y + tmp_rect.h
			&& rect.y + rect.h + app->windowModule->scale > tmp_rect.y)
		{
			return true;
		}
	}

	for (unsigned int i = 0; i < app->entityManagerModule->stairs->Count(); i++)
	{
		tmp_rect = (*app->entityManagerModule->stairs->at(i))->rect;

		if (rect.x  < tmp_rect.x + tmp_rect.w
			&& rect.x + rect.w > tmp_rect.x + tmp_rect.w
			&& rect.y - app->windowModule->scale < tmp_rect.y + tmp_rect.h
			&& rect.y + rect.h + app->windowModule->scale > tmp_rect.y)
		{
			return true;
		}
	}
	return false;
}

bool Player::Check_Collision_Player_Stair()
{
	SDL_Rect stair_rect;

	for (unsigned int i = 0; i < app->entityManagerModule->stairs->Count(); i++)
	{
		// get stair rect
		stair_rect = (*app->entityManagerModule->stairs->at(i))->rect;

		if (rect.x >stair_rect.x) // player to the right
		{
			if (rect.x - stair_rect.x <= 4 * app->windowModule->scale) // player close enough to stairs
			{
				if (rect.y + (rect.h / 2) >= stair_rect.y && rect.y + (rect.h / 2) <= stair_rect.y + stair_rect.h) // player close enough to stairs
				{
					current_stair = *app->entityManagerModule->stairs->at(i);
					rect.x = current_stair->rect.x - app->windowModule->scale;
					stair_update_counter = 0;
					update_counter = 0;
					return true;
				}
			}
		}
		else // player to the left
		{
			if (stair_rect.x - rect.x <= 4 * app->windowModule->scale) // player close enough to stairs
			{
				if (rect.y + (rect.h / 2) >= stair_rect.y && rect.y + (rect.h / 2) <= stair_rect.y + stair_rect.h) // player close enough to stairs
				{
					current_stair = *app->entityManagerModule->stairs->at(i);
					rect.x = current_stair->rect.x - app->windowModule->scale;
					stair_update_counter = 0;
					update_counter = 0;
					return true;
				}
			}
		}
	}
	return false;
}