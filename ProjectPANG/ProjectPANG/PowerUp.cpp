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

		if (rect.x < tmp_rect.x + tmp_rect.w 
			&& rect.x + rect.w > tmp_rect.x 
			&& rect.y <  tmp_rect.y + tmp_rect.h
			&& rect.y + rect.h >  tmp_rect.y )
		{
			return true; 
		}
	}
}

void PowerUp::Blink_PowerUp_Sprite() 
{


}

