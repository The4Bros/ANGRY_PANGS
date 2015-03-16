
#include "Classes.h"
#include "Methods.h"
#include <exception>
#include <iostream>


int main(int argc, char *argv[])
{
	getchar();

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == -1)
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return -1;
	}

	// game code eventually goes here

	SDL_Quit();



	/*
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






