#include "PowerUp.h"

PowerUp::PowerUp(Application* app, int position_in_list, unsigned int type, unsigned int x, unsigned int y)
//app(app),
//position_in_list(position_in_list)
{
	this->app = app; 
	this->position_in_list = position_in_list;
	rect.x = x;
	rect.y = y;
	source_index = type;
	Print();
	power_up_initial_time = app->sceneModule->time_count->current_time;

}






void PowerUp::Update()														 // jordi
{
	if (rect.y < 197 * app->windowModule->scale || !Check_Collision_Bricks())
	{
		rect.y += app->windowModule->scale;
		if (Check_Collision_Players())
		{
			Kill();
		}
	}
	else if (Check_Collision_Players())
	{
		Kill();
	}

	switch (source_index)
	{
		// update source index
	}

	if (power_up_max_time - power_up_initial_time <= 0)     ;    //blink 
}





void PowerUp::Print() // consultar ruben
{
	app->renderModule->Print(app->texturesModule->powerUp_sprite, &app->entityManagerModule->powerup_source_rect[source_index], &rect);
}

void PowerUp::Kill()
{

	for (unsigned int i = position_in_list + 1; i < app->entityManagerModule->powerups.Count(); i++)
	{
		(*app->entityManagerModule->powerups.at(i))->position_in_list--;
	}
	app->entityManagerModule->powerups.Delete_Element_At(position_in_list);
}



bool PowerUp::Check_Collision_Bricks() // cambiar player por bricks ---------> AUSIAS
{
	SDL_Rect tmp_rect;

	for (unsigned int i = 0; i < app->entityManagerModule->bricks.Count(); i++)
	{
		tmp_rect = (*app->entityManagerModule->bricks.at(i))->rect;

		if (rect.x < app->playerModule->player1->rect.x + app->playerModule->player1->rect.w - (8 * app->windowModule->scale)
			&& rect.x + rect.w > app->playerModule->player1->rect.x + (8 * app->windowModule->scale)
			&& rect.y < app->playerModule->player1->rect.y + app->playerModule->player1->rect.h - (8 * app->windowModule->scale)
			&& rect.y + rect.h > app->playerModule->player1->rect.y + (8 * app->windowModule->scale))
		{
			return true; // no need to check player2 if player1 got hit
		}
	}
}




bool PowerUp::Check_Collision_Players()
{
					// -------------------------- COLLISIONS -----------------------------

	if (rect.x < app->playerModule->player1->rect.x + app->playerModule->player1->rect.w - (8 * app->windowModule->scale)
		&& rect.x + rect.w > app->playerModule->player1->rect.x + (8 * app->windowModule->scale)
		&& rect.y < app->playerModule->player1->rect.y + app->playerModule->player1->rect.h - (8 * app->windowModule->scale)
		&& rect.y + rect.h > app->playerModule->player1->rect.y + (8 * app->windowModule->scale))
	{
		CurrentPowerUP();
		return true; // no need to check player2 if player1 got hit
	}

	if (app->playerModule->player2 != NULL)
	{
		if (rect.x < app->playerModule->player2->rect.x + app->playerModule->player2->rect.w - (8 * app->windowModule->scale)
			&& rect.x + rect.w > app->playerModule->player2->rect.x + (8 * app->windowModule->scale)
			&& rect.y < app->playerModule->player2->rect.y + app->playerModule->player2->rect.h - (8 * app->windowModule->scale)
			&& rect.y + rect.h > app->playerModule->player2->rect.y + (8 * app->windowModule->scale))
		{
			CurrentPowerUP();
			return true;
		}
	}

					// -------------------------- COLLISIONS -----------------------------
// --------------------------- Add powerUp to the player ---------------------------- done
}

bool PowerUp::Check_Collision_Harpoons() // if type > 15 -->> fruit-->> kill     JORDI
{
	if (rect.x < app->playerModule->player1->rect.x + app->playerModule->player1->rect.w - (8 * app->windowModule->scale)
		&& rect.x + rect.w > app->playerModule->player1->rect.x + (8 * app->windowModule->scale)
		&& rect.y < app->playerModule->player1->rect.y + app->playerModule->player1->rect.h - (8 * app->windowModule->scale)
		&& rect.y + rect.h > app->playerModule->player1->rect.y + (8 * app->windowModule->scale))
	{
		return true; // no need to check player2 if player1 got hit
	}
}

void PowerUp::Blink_PowerUp_Sprite() 
{


}

void PowerUp::CurrentPowerUP()
{
	switch (source_index)
	{
	case 0:
		app->playerModule->player1->current_weapon = WEAPON_DOUBLE_HARPOON;
		break;
	case 1:
		app->playerModule->player1->current_weapon = WEAPON_GRAPPLE;
		break;
	case 2:
		app->playerModule->player1->current_weapon = WEAPON_DOUBLE_HARPOON;
		break;
	case 3:
		app->entityManagerModule->Dynamite();
		break;
	case 4:
		app->playerModule->player1->shielded = true;
		break;
	case 5:
		app->entityManagerModule->SlowTime();
		break;
	case 6:
		app->entityManagerModule->StopTime();
		break;
	}
}