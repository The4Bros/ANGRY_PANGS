#include "ModulePlayer.h"


ModulePlayer::ModulePlayer(Application* app) : Module(app)
{
	player1 = NULL;
	player2 = NULL;
	player_speed = 2 * app->windowModule->scale;
}

bool ModulePlayer::Init()
{
	player1 = new Player(app, true);
	if (player1 == NULL) { return false; }
	return true;
}

update_status ModulePlayer::PreUpdate(){ return UPDATE_CONTINUE; }

update_status ModulePlayer::Update()
{
	// PLAYER 2

	if (player2 != NULL)
	{
		player2->Update();

		if (app->inputModule->key[SDL_SCANCODE_LEFT] == 1){ player2->LeftTrigger(); }
		if (app->inputModule->key[SDL_SCANCODE_RIGHT] == 1){ player2->RightTrigger(); }
		if (app->inputModule->key[SDL_SCANCODE_UP] == 1){ player2->UpTrigger(); }
		if (app->inputModule->key[SDL_SCANCODE_DOWN] == 1){ player2->DownTrigger(); }
		if (app->inputModule->key[SDL_SCANCODE_RCTRL] == 1){ player2->Shoot(); }
		else { player2->shoot_key_pressed = false; }

		if ((app->inputModule->key[SDL_SCANCODE_LEFT] == 0
			&& app->inputModule->key[SDL_SCANCODE_RIGHT] == 0))
		{
			player2->Still();
		}
	}

	else{ if (app->inputModule->key[SDL_SCANCODE_Y] == 1){ player2 = new Player(app, false); } }



	// PLAYER 1
	player1->Update();

	if (app->inputModule->key[SDL_SCANCODE_A] == 1){ player1->LeftTrigger(); }
	if (app->inputModule->key[SDL_SCANCODE_D] == 1){ player1->RightTrigger(); }
	if (app->inputModule->key[SDL_SCANCODE_W] == 1){ player1->UpTrigger(); }
	if (app->inputModule->key[SDL_SCANCODE_S] == 1){ player1->DownTrigger(); }

	if (app->inputModule->key[SDL_SCANCODE_A] == 0
		&& app->inputModule->key[SDL_SCANCODE_D] == 0)
	{
		player1->Still();
	}

	if (app->inputModule->key[SDL_SCANCODE_SPACE] == 1){ player1->Shoot(); }
	else { player1->shoot_key_pressed = false; }

	return UPDATE_CONTINUE;
}

update_status ModulePlayer::PostUpdate(){ return UPDATE_CONTINUE; }

bool ModulePlayer::CleanUp(){ return true; }



