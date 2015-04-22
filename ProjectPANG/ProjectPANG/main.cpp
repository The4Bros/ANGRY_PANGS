
/*
PANG VIDEOGAME TRIBUTE

AUTHORS:
	SEBASTIAN DELGADO
	JORDI MARTINEZ
	AUSIAS DALMAU
	RUBEN SARDON
*/

#include <stdlib.h>
#include "Globals.h"
#include "Application.h"

enum main_states
{
	MAIN_EXIT,
	MAIN_UPDATE,
	MAIN_ERROR,
	MAIN_START,
	MAIN_FINISH,
	MAIN_CREATION
};


int main(int argc, char *argv[])
{
	Application* app = NULL;
	int main_return = EXIT_SUCCESS;
	main_states state = MAIN_CREATION;
	update_status update_state;

	while (state != MAIN_EXIT)
	{
		switch (state)
		{
		case MAIN_UPDATE:            //------------------UPDATE-----------------
			//LOG("UPDATING:");
			switch (update_state)
			{
			case UPDATE_CONTINUE:
				update_state = app->Update();
				break;
			case UPDATE_ERROR:
				state = MAIN_ERROR;
				break;
			case UPDATE_STOP:
				state = MAIN_FINISH;
				break;
			default:
				if (!app->ChangeTo(update_state)){ state = MAIN_ERROR; }
				update_state = UPDATE_CONTINUE;
				break;
			}

			break;
		
		case MAIN_ERROR:            //------------------ERROR-----------------
			LOG("Application exit with error: %s", SDL_GetError());
			main_return = EXIT_FAILURE;
			state = MAIN_EXIT;
			break;
		
		case MAIN_START:            //------------------START-----------------
			//LOG("Starting Application:");
			if (!app->Init()){ state = MAIN_ERROR; }
			else { state = MAIN_UPDATE; }
			update_state = CHANGE_TO_PLAY; //CHANGE_TO_PLAY;
			break;
		
		case MAIN_FINISH:            //------------------FINISH-----------------
			//LOG("Finishing Application:");
			if (!app->CleanUp()){ state = MAIN_ERROR; }
			else{ state = MAIN_EXIT; }
			delete app;
			SDL_Quit();
			break;
		
		case MAIN_CREATION:          //------------------CREATION-----------------
			//LOG("Creating Application:\n");
			if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS) == -1){ state = MAIN_ERROR; }
			else
			{
				app = new Application();
				state = MAIN_START;
			}
		}
	}
	return main_return;
}
	


/*
SDL_INIT_TIMER - timer subsystem
SDL_INIT_AUDIO - audio subsystem
SDL_INIT_VIDEO - video subsystem
SDL_INIT_JOYSTICK - joystick subsystem
SDL_INIT_HAPTIC - haptic (force feedback) subsystem
SDL_INIT_GAMECONTROLLER - controller subsystem
SDL_INIT_EVENTS - events subsystem
SDL_INIT_EVERYTHING - all of the above subsystems
SDL_INIT_NOPARACHUTE - compatibility; this flag is ignored
*/