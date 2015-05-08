# include "Particles.h"

/*
0 - 11 balloon
12 enemy hit
13 shoot
14 - 29 brick
*/


Particles::Particles(Application* app, unsigned int type, int x, int y) :
		app(app),
		alive(false),
		update_counter(0)
{
	if (type < 12){ app->audioModule->PlayFx(BALLOON_POP); }

	if (type == 12){ quantity = 4; } // enemy hit
	else { quantity = 3; }

	switch (type)
	{
	case 0:
		source_index = 0;
		rect = { x, y, 48 * app->windowModule->scale, 40 * app->windowModule->scale };
		break;
	case 1:
		source_index = 4;
		rect = { x, y, 48 * app->windowModule->scale, 40 * app->windowModule->scale };
		break;
	case 2:
		source_index = 8;
		rect = { x, y, 48 * app->windowModule->scale, 40 * app->windowModule->scale };
		break;
	case 3:
		source_index = 12;
		rect = { x, y - app->windowModule->scale, 32 * app->windowModule->scale, 29 * app->windowModule->scale };
		break;
	case 4:
		source_index = 16;
		rect = { x, y - app->windowModule->scale, 32 * app->windowModule->scale, 29 * app->windowModule->scale };
		break;
	case 5:
		source_index = 20;
		rect = { x, y - app->windowModule->scale, 32 * app->windowModule->scale, 29 * app->windowModule->scale };
		break;
	case 6:
		source_index = 24;
		rect = { x, y - app->windowModule->scale, 16 * app->windowModule->scale, 16 * app->windowModule->scale };
		break;
	case 7:
		source_index = 28;
		rect = { x, y - app->windowModule->scale, 16 * app->windowModule->scale, 16 * app->windowModule->scale };
		break;
	case 8:
		source_index = 32;
		rect = { x, y - app->windowModule->scale, 16 * app->windowModule->scale, 16 * app->windowModule->scale };
		break;
	case 9:
		source_index = 36;
		rect = { x, y - app->windowModule->scale, 8 * app->windowModule->scale, 7 * app->windowModule->scale };
		break;
	case 10:
		source_index = 40;
		rect = { x, y - app->windowModule->scale, 8 * app->windowModule->scale, 7 * app->windowModule->scale };
		break;
	case 11:
		source_index = 44;
		rect = { x, y - app->windowModule->scale, 8 * app->windowModule->scale, 7 * app->windowModule->scale };
		break;
	case 12:
		source_index = 48;
		rect = { x, y - app->windowModule->scale, 28 * app->windowModule->scale, 26 * app->windowModule->scale };
		break;
	case 13:
		source_index = 53;
		rect = { x, y - app->windowModule->scale, 15 * app->windowModule->scale, 15 * app->windowModule->scale };
		break;
		//breakeables bricks
	case 14:
		source_index = 57;
	}
}

void Particles::Update()
{
	if (update_counter >2)
	{
		if (quantity > 0)
		{
			source_index++;
			update_counter = 0;
			quantity--;
		}
		else
		{
			alive = false;
		}
	}
	else{ update_counter++; }
}

void Particles::Print()
{
	if (source_index < 57)
	{
		app->renderModule->Print(app->texturesModule->particles_sprite, &app->entityManagerModule->particles_source_rect[source_index], &rect);
	}
	else
	{
		app->renderModule->Print(app->texturesModule->bricks_sprite, &app->entityManagerModule->particles_source_rect[source_index], &rect);
	}
}
