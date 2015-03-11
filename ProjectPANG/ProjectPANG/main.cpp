
#include "Classes.h"
#include "Methods.h"
#include <exception>
#include <stdio.h>
#include <iostream>
#include "SDL.h"


int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
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






