# include "Particles.h"

Particles::Particles(Application* app, unsigned int type, int x, int y)
{
	this->app = app;
	rect = { x, y, 48 * app->windowModule->scale, 40 * app->windowModule->scale };
	update_counter = 0;
	quantity = 4;
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
			// delete particle
		}
	}
	else{ update_counter++; }
}

void Particles::Print()
{
	app->renderModule->Print(app->texturesModule->particles_sprite, app->entityManagerModule->particles_source_rect[source_index], &rect);
}
