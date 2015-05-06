
#include "ModuleFontManager.h"

ModuleFontManager::ModuleFontManager(Application* app) : Module(app) {}

ModuleFontManager::ModuleFontManager(const ModuleFontManager& fontManager) : Module(fontManager.app) {}

bool ModuleFontManager::Init()
{
	if (!TTF_WasInit()){ if (TTF_Init() == -1){ return false; } }

	white_color = { 255, 255, 255 };
	yellow_color = { 255, 223, 0 };
	font = TTF_OpenFont("font/PANGTYPO.TTF", 12);

	return true;
}

char* ModuleFontManager::NumberToString(int Number)
{
	char Num_string[20];

	sprintf_s(Num_string, 20, "%d", Number);

	return Num_string;
}

void ModuleFontManager::Write_On_Screen(unsigned int value, unsigned int x, unsigned int y, unsigned int size,int color)
{
	char tmp[20];

	strcpy_s(tmp, 20, NumberToString(value));

	Write_On_Screen(tmp, x, y, size,color);
}

void ModuleFontManager::Write_On_Screen( char* string, unsigned int x, unsigned int y, unsigned int size,int color)
{
	SDL_Surface* surfaceMessage;
	if (color == 0){ surfaceMessage = TTF_RenderText_Solid(font, string, white_color); }
	else{  surfaceMessage = TTF_RenderText_Solid(font, string, yellow_color); }
	
	SDL_Texture* Message = SDL_CreateTextureFromSurface(app->renderModule->renderer, surfaceMessage);
	Message_rect = { x , y,  strlen(string)*size, size };
	app->renderModule->Print(Message, NULL, &Message_rect);
}

bool ModuleFontManager::CleanUp()
{
	if (TTF_WasInit()){ TTF_Quit(); }
	return true;
}

