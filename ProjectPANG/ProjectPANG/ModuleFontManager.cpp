#include "ModuleFontManager.h"

ModuleFontManager::ModuleFontManager(Application* app) : Module(app)
{
	sample_text = "hello world";
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
	//font = TTF_OpenFont("font/PANGTYPO___.TTF", 12);
	//TTF_SetFontStyle(font, TTF_STYLE_NORMAL);
	//SDL_Surface *TTF_RenderText_Solid(TTF_Font *font, const char *text, SDL_Color fg);

	
	

	return true;
}


void ModuleFontManager::Write_On_Screen(unsigned int value, unsigned int x, unsigned int y, unsigned int size){





}
/*
void ModuleFontManager::Write_On_Screen(char* string, unsigned int x, unsigned int y, unsigned int size){

	SDL_Surface *text = TTF_RenderText_Solid(font, string, color);
	SDL_Texture* SDL_CreateTextureFromSurface(SDL_Renderer* renderer, SDL_Surface*  text);
	SDL_Rect* textrect;
	textrect->x = x;
	textrect->y = y;
	switch (size){
	case 1: 
		textrect->h = 8;
		textrect->w = 8;
		break;

	case 2: 
		textrect->h = 16;
		textrect->w = 16;
		break;
	}

	//Print(SDL_CreateTextureFromSurface,textrect, textrect);


}
*/

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