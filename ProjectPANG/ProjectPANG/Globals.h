
#include <exception>

#include "DoubleNodedStack.h"

#include <Windows.h>
#include <iostream>

#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL/libx86/SDL2.lib" )
#pragma comment( lib, "SDL/libx86/SDL2main.lib" )

#define LOG(txt) OutputDebugString(txt)

enum main_states
{
	MAIN_EXIT,
	MAIN_UPDATE,
	MAIN_SDL_ERROR,
	MAIN_ERROR,
	MAIN_START,
	MAIN_FINISH,
	MAIN_CREATION
};

enum update_status
{
	UPDATE_CONTINUE,
	UPDATE_PAUSE, //PollEvent != SDL_QUIT

	UPDATE_STOP,
	UPDATE_ERROR
};





