#include "Globals.h"
#include"Application.h"

#ifndef __Harpoon_H__
#define __Harpoon_H__

class Harpoon
{
public:
	Application* app;
	SDL_Rect rect;
	SDL_Rect source_rect;
	const SDL_Rect* const_rect;

	unsigned int update_counter;
	bool alive;

	Harpoon(Application* app);
	~Harpoon(){}

};
#endif