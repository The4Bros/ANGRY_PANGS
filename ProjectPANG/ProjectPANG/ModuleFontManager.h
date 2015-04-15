#include "Module.h"
#include "Globals.h"
#include "Application.h"
#include "SDL2_ttf-2.0.12/include/SDL_ttf.h"
#pragma comment( lib, "SDL2_ttf-2.0.12/lib/x86/SDL2_ttf.lib" )



#ifndef __ModuleFontManager_H__
#define __ModuleFontManager_H__


class ModuleFontManager : public Module{
public:
	TTF_Font* font;
	SDL_Color color;
	char Num_string[100];
	ModuleFontManager(Application* app);
	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	void Write_On_Screen(unsigned int value, unsigned int x, unsigned int y, unsigned int size);
	void Write_On_Screen(char* string, unsigned int x, unsigned int y, unsigned int size);


	char* NumberToString(int Number);

};

#endif