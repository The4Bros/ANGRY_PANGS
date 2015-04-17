# include "Particles.h"

Particles::Particles(Application* app, unsigned int type,  int x,  int y)
{
	this->app = app;

	switch (type)
	{
	case ENEMY_HIT:
		rect = { x, y, 29, 26 };
		quantity = 5;
		for (int i = 0; i < quantity; i++)
		{
			source_rect[i] = new SDL_Rect({ i * 29, 0, 29, 26 });
		}
		break;

	case PLAYER_SHOOT:
		rect = { x, y, 29, 26 }; //----------------------------------------------------
		quantity = 3;
		for (int i = 0; i < quantity; i++)
		{
			source_rect[i] = new SDL_Rect({ i * 45, 26, 45, 47 });
		}
		break;

	case BALL_SIZE_1:
		rect = { x, y, 29, 26 }; //----------------------------------------------------
		quantity = 3;
		for (int i = 0; i < quantity; i++)
		{
			source_rect[i] = new SDL_Rect({ i * 45, 26, 45, 47 });
		}
		break;

	case BALL_SIZE_2:
		rect = { x, y, 29, 26 };
		quantity = 5;
		for (int i = 0; i < quantity; i++)
		{
			source_rect[i] = new SDL_Rect({ i * 16, 124, 16, 16 });
		}
		break;

	case BALL_SIZE_3:
		rect = { x, y, 29, 26 };
		quantity = 4;
		for (int i = 0; i < quantity; i++)
		{
			source_rect[i] = new SDL_Rect({ i * 32, 92, 32, 32 });
		}
		break;

	case BALL_SIZE_4:
		rect = { x, y, 29, 26 };
		quantity = 3;
		for (int i = 0; i < quantity; i++)
		{
			source_rect[i] = new SDL_Rect({ i * 45, 26, 45, 47 });
		}
		break;
	}

}


void Particles::Update()
{


}