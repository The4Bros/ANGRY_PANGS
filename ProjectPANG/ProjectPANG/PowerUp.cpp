#include "PowerUp.h"

PowerUp::PowerUp(Application* app, int position_in_list, unsigned int type, unsigned int x, unsigned int y) :
app(app),
position_in_list(position_in_list)
{
	source_index = 0;
}






void PowerUp::Update()
{
	if (rect.y < 197 * app->windowModule->scale)
	{
		rect.y += app->windowModule->scale;
		if (Check_Collision_Players())
		{
			Kill();
		}
	}
	else if (Check_Collision_Harpoons() || Check_Collision_Players() || Check_Collision_Bricks())
	{
		Kill();
	}

	switch (source_index)
	{
		// update source index
	}
}





void PowerUp::Print()
{
	//app->renderModule->Print(app->texturesModule->_____, &app->entityManagerModule->powerup_source_rect[source_index], &rect);
}

void PowerUp::Kill()
{
	switch (source_index)
	{

	}
}



bool PowerUp::Check_Collision_Bricks()
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
	if (rect.x < app->playerModule->player1->rect.x + app->playerModule->player1->rect.w - (8 * app->windowModule->scale)
		&& rect.x + rect.w > app->playerModule->player1->rect.x + (8 * app->windowModule->scale)
		&& rect.y < app->playerModule->player1->rect.y + app->playerModule->player1->rect.h - (8 * app->windowModule->scale)
		&& rect.y + rect.h > app->playerModule->player1->rect.y + (8 * app->windowModule->scale))
	{
		return true; // no need to check player2 if player1 got hit
	}

	if (app->playerModule->player2 != NULL)
	{
		if (rect.x < app->playerModule->player2->rect.x + app->playerModule->player2->rect.w - (8 * app->windowModule->scale)
			&& rect.x + rect.w > app->playerModule->player2->rect.x + (8 * app->windowModule->scale)
			&& rect.y < app->playerModule->player2->rect.y + app->playerModule->player2->rect.h - (8 * app->windowModule->scale)
			&& rect.y + rect.h > app->playerModule->player2->rect.y + (8 * app->windowModule->scale))
		{
			return true;
		}
	}
}

bool PowerUp::Check_Collision_Harpoons()
{
	if (rect.x < app->playerModule->player1->rect.x + app->playerModule->player1->rect.w - (8 * app->windowModule->scale)
		&& rect.x + rect.w > app->playerModule->player1->rect.x + (8 * app->windowModule->scale)
		&& rect.y < app->playerModule->player1->rect.y + app->playerModule->player1->rect.h - (8 * app->windowModule->scale)
		&& rect.y + rect.h > app->playerModule->player1->rect.y + (8 * app->windowModule->scale))
	{
		return true; // no need to check player2 if player1 got hit
	}
}