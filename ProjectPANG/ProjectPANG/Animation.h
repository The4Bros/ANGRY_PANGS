
#include "Globals.h"

#ifndef __ModuleInput_H__
#define __ModuleInput_H__

#include "Queue.h"

class Animation
{
public:
	float speed;
	DymanicArray<SDL_Rect> frames;

private:
	float current_frame;

public:
	Animation() : frames(5), speed(1.0f), current_frame(0)
	{}

	SDL_Rect& GetCurrentFrame()
	{
		current_frame += speed;
		if (current_frame >= frames.Count())
			current_frame = 0;

		return frames[(int)current_frame];
	}
};

#endif