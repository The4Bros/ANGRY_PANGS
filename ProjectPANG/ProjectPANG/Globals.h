#pragma once

#include <stdio.h>
#include <Windows.h>

#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL/libx86/SDL2.lib" )
#pragma comment( lib, "SDL/libx86/SDL2main.lib" )

#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);

void log(const char file[], int line, const char* format, ...);

enum update_status
{
	UPDATE_CONTINUE,
	UPDATE_PAUSE, //PollEvent != SDL_QUIT
	UPDATE_STOP,
	UPDATE_ERROR
};

enum current_weapon
{
	WEAPON_DOUBLE_HARPOON,
	WEAPON_HARPOON,
	WEAPON_GRAPPLE,
	WEAPON_SHOTGUN
};


enum power_Up
{
	POWERUP_TIME_STOP,
	POWERUP_TIME_SLOW,
	POWERUP_FOOD,
	POWERUP_SHIELD,
	POWERUP_LIFE,
	POWERUP_DYNAMITE,
	POWERUP_DOUBLE_HARPOON,
	POWERUP_GRAPPLE,
	POWERUP_SHOTGUN
};

// Configuration -----------

#define ACCELERATED true
#define VSYNC true

#define SHOWN true
#define FULLSCREEN false
#define RESIZABLE false
#define WINDOW_TITLE "PANG"
#define SCREEN_WIDTH 768
#define SCREEN_HEIGHT 480

#define BACKGROUND_HEIGHT 414

#define FPS 60

#define FONT_FILE "font/ARCAC___.TTF"
#define FONT_SIZE 16

#define SPRITE_Character_FILE "..\ProjectPANG\GameResources\images\Character.png"

