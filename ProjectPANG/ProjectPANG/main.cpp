
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


/*
SDL_Surface picture = IMG_Load("picture.png");
SDL_SetColorKey(picture, SDL_SRCCOLORKEY, SDL_MapRGB(picture->format, 0, 0, 255));

SDL_Window* window = SDL_CreateWindow("name", x, y, w, h, SDL_WINDOW_SHOWN);
SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDER_ACCELERATED);
SDL_Texture* image = IMG_LoadTexture(renderer, "image.png");

SDL_Rect rect; rect.x=20; rect.y=30; rect.w=600; rect.h=400;

SDL_RenderCopy(renderer, image, const SDL_Rect *srcrect, rect);

*/

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
	update_status update_state = UPDATE_CONTINUE;

	while (state != MAIN_EXIT)
	{
		switch (state)
		{
		case MAIN_UPDATE:            //------------------UPDATE-----------------
			update_state = app->PreUpdate();
			switch (update_state)
			{
			case UPDATE_CONTINUE:
				break;
			case UPDATE_PAUSE:
				break;
			case UPDATE_ERROR:
				state = MAIN_ERROR;
				break;
			case UPDATE_STOP:
				state = MAIN_FINISH;
			}
			break;
			update_state = app->Update();
			switch (update_state)
			{
			case UPDATE_CONTINUE:
				break;
			case UPDATE_PAUSE:
				break;
			case UPDATE_ERROR:
				state = MAIN_ERROR;
				break;
			case UPDATE_STOP:
				state = MAIN_FINISH;
			}
			break;
			update_state = app->PostUpdate();
			switch (update_state)
			{
			case UPDATE_CONTINUE:
				break;
			case UPDATE_PAUSE:
				break;
			case UPDATE_ERROR:
				state = MAIN_ERROR;
				break;
			case UPDATE_STOP:
				state = MAIN_FINISH;
			}
			break;
		
		case MAIN_ERROR:            //------------------ERROR-----------------
			LOG("\nApplication exit with error: %s", SDL_GetError());
			main_return = EXIT_FAILURE;
			state = MAIN_EXIT;
			break;
		
		case MAIN_START:            //------------------START-----------------
			LOG("\nStarting Application:");
			if (!app->Init()){ state = MAIN_ERROR; }
			else { state = MAIN_UPDATE; }
			break;
		
		case MAIN_FINISH:            //------------------FINISH-----------------
			LOG("\nFinishing Application:");
			if (!app->CleanUp()){ state = MAIN_ERROR; }
			else{ state = MAIN_EXIT; }
			delete app;
			SDL_Quit();
			break;
		
		case MAIN_CREATION:          //------------------CREATION-----------------
			LOG("\nCreating Application:\n");
			//Uint32 flags for init:
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
			if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS) == -1){ state = MAIN_ERROR; }
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

	LOG("Initializing SDL:\n");
	if (SDL_Init(SDL_INIT_VIDEO) != 0){
>>>>>>> origin/master
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return -1;
	}



	// game code eventually goes here


	LOG("Exiting SDL:\n");

	SDL_Quit();



	
	try {
		SDL sdl(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS);




	}
	
	catch (const InitError& err) {
			std::cerr
				<< "Error while initializing SDL:  "
				<< err.what() << std::endl;
		}

		*/






