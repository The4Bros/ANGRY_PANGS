#ifndef Colisiones
#define Colisiones
#include <iostream>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
using namespace std;







struct Personaje{int x; int y; int direction; int position; int life; bool alive; int counter1; int counter2; int speed;};
struct Projectil{int x; int y; bool alive; int direction;};

void imprimir(SDL_Surface *screen, SDL_Surface *ima, int x, int y){
	 SDL_Rect rect = {x, y, 0, 0};
	 SDL_BlitSurface(ima, NULL, screen, &rect);}

bool colision(int x1, int y1, int w1, int h1, int x2, int y2){
 if(x2 + 80 < x1) {return false;}
 if(x2> x1 + w1) {return false;}
 if(y2 + 80 < y1) {return false;}
 if(y2 > y1 + h1) {return false;}
 return true;}
 
 bool colisionHarpoonBall(int x1, int y1, int r, int x2, int y2, int w2){
	if (x2 + w2 < x1)  // objeto 2 a la izquiera
	{
		return false;
	}
	if (x2 > x1 + 2 * r) // objeto 2 a la derecha
	{
		return false;
	}
	if (y2 > y1 + 2 * r) // objeto 2 debajo
	{
		return false;
	}
	if (y2 < y1 + r) // objeto 2 encima
	{
		return true;
	}    
	if (x2 > x1 + r) // comprobacion si el objeto 2 colisiona con el cuadrante IV
	{
		if (r*r >= (x2 - x1 - x1)*(x2 - x1 - x1) + (y2 - y1 - r)*(y2 - y1 - r))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	if (x2 > x1 + r) // comprobacion si el objeto 2 colisiona con el cuadrante III
	{
		if (r*r >= (x2 + w2 - x1 - r)*(x2 + w2 - x1 - r) + (y2 - y1 - r)*(y2 - y1 - r))
		{
			return true;
		}
	}
	return false;
}






void updateProjectiles(Projectil *projectil, SDL_Surface *bufferProjectil, SDL_Surface *screen, Personaje *enemigo, SDL_Surface *bufferEnemy){
	if(projectil->alive){
	if(colision(projectil->x, projectil->y, bufferProjectil->w, bufferProjectil->h, enemigo->x, enemigo->y)){
		projectil->alive=false; enemigo->life-=20;}
	imprimir(screen, bufferProjectil, projectil->x, projectil->y);}}


void spawnEnemy(Personaje *enemigo, int w, int h, int alto, int ancho){
	enemigo->alive=true;
	enemigo->direction=rand()%4+1;
	enemigo->life=80;
	switch(enemigo->direction){
		case 1: enemigo->x=ancho-w; enemigo->y=rand()%(alto-50)+50; break;
		case 2: enemigo->x=0; enemigo->y=(rand()%(alto-50))+50; break;
		case 3: enemigo->x=rand()%(ancho-w); enemigo->y=alto-h; break;
		case 4: enemigo->x=rand()%(ancho-w); enemigo->y=50; break;}}

#endif
