#include "Module.h"
#include "Globals.h"
#include "Application.h"
#include "SDL2_ttf-2.0.12/include/SDL_ttf.h"
#pragma comment( lib, "SDL2_ttf-2.0.12/lib/x86/SDL2_ttf.lib" )



#ifndef __ModuleFontManager_H__
#define __ModuleFontManager_H__


class ModuleFontManager : public Module{
private:

	TTF_Font* font;
	SDL_Color white_color;

	
	SDL_Rect Message_rect;

public:

	ModuleFontManager(Application* app);
	ModuleFontManager(const ModuleFontManager& fontManager);
	bool Init();
	bool CleanUp();

	void Write_On_Screen(unsigned int value, unsigned int x, unsigned int y, unsigned int size);
	void Write_On_Screen(char* string, unsigned int x, unsigned int y, unsigned int size);

	char* NumberToString(int Number);

};

#endif