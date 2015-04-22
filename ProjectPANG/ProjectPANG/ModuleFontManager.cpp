#include "ModuleFontManager.h"
ModuleFontManager::ModuleFontManager(Application* app) : Module(app)
{
}
bool ModuleFontManager ::Init()
{
	if (!TTF_WasInit())
	{
		if (TTF_Init() == -1)
			{
				return false;
			}
	}

	color = { 255, 255, 255 };
	font = TTF_OpenFont("font/PANGTYPO.TTF", 12);

	return true;
}

char* ModuleFontManager::NumberToString(int Number)
{
	sprintf_s(Num_string, 10, "%d", Number);
	return Num_string;
}

void ModuleFontManager::Write_On_Screen(unsigned int value, unsigned int x, unsigned int y, unsigned int size)
{
	char tmp[12];
	strcpy_s(tmp, 12, NumberToString(value));

	Write_On_Screen(tmp, x, y, size);
}

void ModuleFontManager::Write_On_Screen( char* string, unsigned int x, unsigned int y, unsigned int size)
{
	surfaceMessage = TTF_RenderText_Solid(font, string, color);
	Message = SDL_CreateTextureFromSurface(app->renderModule->renderer, surfaceMessage);
	Message_rect = { x , y,  strlen(string)*size, size };

	app->renderModule->Print(Message, NULL, &Message_rect);
}


update_status ModuleFontManager::PreUpdate(){ return UPDATE_CONTINUE; }
update_status ModuleFontManager::Update(){ return UPDATE_CONTINUE; }
update_status ModuleFontManager::PostUpdate(){ return UPDATE_CONTINUE; }
bool ModuleFontManager::CleanUp()
{
	TTF_Quit();
	return true;
}

