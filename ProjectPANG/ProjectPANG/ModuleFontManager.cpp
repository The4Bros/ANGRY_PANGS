
#include "ModuleFontManager.h"

ModuleFontManager::ModuleFontManager(Application* app) : Module(app)
{
	color[0] = { 255, 255, 255 };
	color[1] = { 255, 223, 0 };
}

bool ModuleFontManager::Init()
{
	if (!TTF_WasInit()){ if (TTF_Init() == -1){ return false; } }
	
	font = TTF_OpenFont("font/PANGTYPO.TTF", 12);

	return true;
}

void ModuleFontManager::Write_On_Screen(unsigned int value, unsigned int x, unsigned int y, unsigned int size, Text_Color text_color)
{
	// convert number to string
	char tmp[20];

	//strcpy_s(tmp, 20, NumberToString(value));

	sprintf_s(tmp, 20, "%d", value);



	// call Write on Screen with new string
	Write_On_Screen(tmp, x, y, size, text_color);
}

void ModuleFontManager::Write_On_Screen(char* string, unsigned int x, unsigned int y, unsigned int size, Text_Color text_color)
{
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, string, color[int(text_color)]);

	SDL_Texture* Message = SDL_CreateTextureFromSurface(app->renderModule->renderer, surfaceMessage);

	Message_rect = { x , y,  strlen(string)*size, size };

	app->renderModule->Print(Message, NULL, &Message_rect);
}

bool ModuleFontManager::CleanUp()
{
	if (TTF_WasInit()){ TTF_Quit(); }
	return true;
}

