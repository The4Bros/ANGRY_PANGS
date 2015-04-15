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

char* ModuleFontManager::NumberToString(int Number){

	sprintf_s(Num_string, 10, "%d", Number);
	return Num_string;
}

void ModuleFontManager::Write_On_Screen(unsigned int value, unsigned int x, unsigned int y, unsigned int size){
	
	
	char tmp[12];
	strcpy_s(tmp, 12, NumberToString(value));

	Write_On_Screen(tmp, x, y, size);


}

void ModuleFontManager::Write_On_Screen( char* string, unsigned int x, unsigned int y, unsigned int size){
	
	
		
		SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, string, color);
		SDL_Texture* Message = SDL_CreateTextureFromSurface(app->renderModule->renderer, surfaceMessage);
		SDL_Rect Message_rect = { x , y,  strlen(string)*size, size };


		//if (string == "a") Message_rect.w += app->windowModule->scale;
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







/*
3.1.1 TTF Linked Version
3.1.2 TTF Init
3.1.3 TTF WasInit
3.1.4 TTF Quit
3.1.5 TTF SetError
3.1.6 TTF GetError
*/