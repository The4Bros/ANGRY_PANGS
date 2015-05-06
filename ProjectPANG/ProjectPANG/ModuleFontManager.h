#include "Module.h"
#include "Globals.h"
#include "Application.h"
#include "SDL2_ttf-2.0.12/include/SDL_ttf.h"
#pragma comment( lib, "SDL2_ttf-2.0.12/lib/x86/SDL2_ttf.lib" )



#ifndef __ModuleFontManager_H__
#define __ModuleFontManager_H__

enum Text_Color
{
	WHITE,
	YELLOW
};


class ModuleFontManager : public Module{
private:

	TTF_Font* font;
	SDL_Color color[2];
	
	SDL_Rect Message_rect;

public:

	ModuleFontManager(Application* app);
	bool Init();
	bool CleanUp();

	void Write_On_Screen(unsigned int value, unsigned int x, unsigned int y, unsigned int size, Text_Color text_color);
	void Write_On_Screen(char* string, unsigned int x, unsigned int y, unsigned int size, Text_Color text_color);
};

#endif