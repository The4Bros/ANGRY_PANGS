#include "ModuleFontManager.h"

ModuleFontManager::ModuleFontManager(Application* app) : Module(app)
{
	sample_text = "hello world";
}
bool ModuleFontManager ::Init()
{
	if (!TTF_WasInit() && TTF_Init() == -1)
	{
		LOG("\nTTF_Init error: %s", TTF_GetError());
		return false;
	}

	TTF_Font* font;

	font = TTF_OpenFont(FONT_FILE, FONT_SIZE);





	return true;
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