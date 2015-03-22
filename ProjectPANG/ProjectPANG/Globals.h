#pragma once
#include <stdio.h>
#include <Windows.h>
#include <iostream>

#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL/libx86/SDL2.lib" )
#pragma comment( lib, "SDL/libx86/SDL2main.lib" )

#include "SDL_image/include/SDL_image.h"
#pragma comment( lib, "SDL_image/libx86/SDL2_image.lib" )


#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);

void log(const char file[], int line, const char* format, ...);

enum update_status
{
	UPDATE_CONTINUE,
	UPDATE_PAUSE, //PollEvent != SDL_QUIT
	UPDATE_STOP,
	UPDATE_ERROR
};

// Configuration -----------
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define FULLSCREEN false
#define RESIZABLE false
#define VSYNC true
#define WINDOW_TITLE "PANG"
#define SPRITE_Character_FILE "..\ProjectPANG\GameResources\images\Character.png"

