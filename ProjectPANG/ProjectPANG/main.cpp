
#include "Classes.h"
#include "Methods.h"
#include "Application.h"
#include <exception>
#include <stdio.h>
#include <Windows.h>
#include <iostream>
//#include "SDL2.lib"
#include "SDL.h"


#define LOG(txt) OutputDebugString(txt)

enum main_states
{
	MAIN_CREATION,
	MAIN_START,
	MAIN_UPDATE,
	MAIN_FINISH,
	MAIN_EXIT,
	MAIN_ERROR
};

enum update_status
{
	UPDATE_CONTINUE,
	UPDATE_STOP,
	UPDATE_ERROR
};





int main(int argc, char *argv[])
{
	getchar();

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == -1)
	{

	Application* app = NULL;

	int MAIN_RETURN = EXIT_FAILURE;
	main_states state = MAIN_CREATION;

	while (state != MAIN_EXIT)
	{
		switch (state)
		{
		case MAIN_CREATION:



			state = MAIN_START;
			break;

		case MAIN_START:

			LOG("Creating Application:\n");
			app = new Application();

			if (!app->Init())
			{
				LOG("Application exit with error: ");
				//LOG(SDL_GetError());
				state = MAIN_ERROR;
			}
			else
			{
				state = MAIN_UPDATE;
			}
			break;
			

		case MAIN_UPDATE:
			state = MAIN_EXIT;
			break;

		case MAIN_FINISH:
			break;

		case MAIN_ERROR:
			break;

		}
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


	return 0;
}






	#include "Classes.h"
#include "Methods.h"
#include "Application.h"
#include <exception>
#include <stdio.h>
#include <Windows.h>
#include <iostream>
//#include "SDL2.lib"
#include "SDL.h"


#define LOG(txt) OutputDebugString(txt)

enum main_states
{
	MAIN_CREATION,
	MAIN_START,
	MAIN_UPDATE,
	MAIN_FINISH,
	MAIN_EXIT,
	MAIN_ERROR
};

enum update_status
{
	UPDATE_CONTINUE,
	UPDATE_STOP,
	UPDATE_ERROR
};





int main(int argc, char *argv[])
@@ -11,17 +39,78 @@ int main(int argc, char *argv[])

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == -1)
	{

	Application* app = NULL;

	int MAIN_RETURN = EXIT_FAILURE;
	main_states state = MAIN_CREATION;

	while (state != MAIN_EXIT)
	{
		switch (state)
		{
		case MAIN_CREATION:



			state = MAIN_START;
			break;

		case MAIN_START:

			LOG("Creating Application:\n");
			app = new Application();

			if (!app->Init())
			{
				LOG("Application exit with error: ");
				//LOG(SDL_GetError());
				state = MAIN_ERROR;
			}
			else
			{
				state = MAIN_UPDATE;
			}
			break;
			

		case MAIN_UPDATE:
			state = MAIN_EXIT;
			break;

		case MAIN_FINISH:
			break;

		case MAIN_ERROR:
			break;

		}
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



	/*
	
	try {
		SDL sdl(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS);

@@ -37,6 +126,8 @@ int main(int argc, char *argv[])
		}

		*/


	return 0;
}
