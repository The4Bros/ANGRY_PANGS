#include "Brick.h"

Brick::Brick(Application* app, unsigned int x, unsigned int y, unsigned int type)
{
	this->app = app;
	this->type = GOLD1;
	rect = { x, y, 31, 7 };
}

void Brick::Print()
{
	unsigned int option = NULL;

	switch (option)
	{
	case GOLD1: 
	{
		//app->renderModule->Print(app->texturesModule->bricks_sprite, app->entityManagerModule->source_brick_rect,  );
		break; 
	}
	case GOLD2:	
	{
		break; 
	}
	case GOLD3:	{ break; }
	case FUCSIA1:	{ break; }
	case FUCSIA2:	{ break; }
	case FUCSIA3:	{ break; }
	case BLUE1:	{ break; }
	case BLUE2:	{ break; }
	case BLUE3:	{ break; }
	case YELLOW1:	{ break; }
	case YELLOW2:	{ break; }
	case YELLOW3:	{ break; }
	case PINK1:	{ break; }
	case PINK2:	{ break; }
	case PINK3:	{ break; }
	case CIAN1:	{ break; }
	case CIAN2:	{ break; }
	case CIAN3:	{ break; }
		
	}
}

void Brick::Update()
{

}

//when a brick breaks + animation destroy brick
void Brick::Hit()
{

}


