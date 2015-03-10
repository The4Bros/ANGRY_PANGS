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

void addEnemies(vector<Personaje> *enemigos){
	Personaje enemigo1; enemigo1.x=0; enemigo1.y=0; enemigo1.direction=1; enemigo1.position=1; enemigo1.alive=false; enemigo1.life=80; enemigo1.speed=0; enemigos->push_back(enemigo1);
	Personaje enemigo2; enemigo2.x=0; enemigo2.y=0; enemigo2.direction=1; enemigo2.position=1; enemigo2.alive=false; enemigo2.life=80; enemigo2.speed=0; enemigos->push_back(enemigo2);
	Personaje enemigo3; enemigo3.x=0; enemigo3.y=0; enemigo3.direction=1; enemigo3.position=1; enemigo3.alive=false; enemigo3.life=80; enemigo3.speed=0; enemigos->push_back(enemigo3);
	Personaje enemigo4; enemigo4.x=0; enemigo1.y=0; enemigo4.direction=1; enemigo4.position=1; enemigo4.alive=false; enemigo4.life=80; enemigo4.speed=0; enemigos->push_back(enemigo4);
	Personaje enemigo5; enemigo5.x=0; enemigo5.y=0; enemigo5.direction=1; enemigo5.position=1; enemigo5.alive=false; enemigo5.life=80; enemigo5.speed=0; enemigos->push_back(enemigo5);}

void addProjectiles(vector<Projectil> *vectorProjectiles){
	Projectil projectil1; projectil1.alive=false; vectorProjectiles->push_back(projectil1);
	Projectil projectil2; projectil2.alive=false; vectorProjectiles->push_back(projectil2);
	Projectil projectil3; projectil3.alive=false; vectorProjectiles->push_back(projectil3);
	Projectil projectil4; projectil4.alive=false; vectorProjectiles->push_back(projectil4);
	Projectil projectil5; projectil5.alive=false; vectorProjectiles->push_back(projectil5);
	Projectil projectil6; projectil6.alive=false; vectorProjectiles->push_back(projectil6);
	Projectil projectil7; projectil7.alive=false; vectorProjectiles->push_back(projectil7);
	Projectil projectil8; projectil8.alive=false; vectorProjectiles->push_back(projectil8);
	Projectil projectil9; projectil9.alive=false; vectorProjectiles->push_back(projectil9);
	Projectil projectil10; projectil10.alive=false; vectorProjectiles->push_back(projectil10);
	Projectil projectil11; projectil11.alive=false; vectorProjectiles->push_back(projectil11);
	Projectil projectil12; projectil12.alive=false; vectorProjectiles->push_back(projectil12);
	Projectil projectil13; projectil13.alive=false; vectorProjectiles->push_back(projectil13);
	Projectil projectil14; projectil14.alive=false; vectorProjectiles->push_back(projectil14);
	Projectil projectil15; projectil15.alive=false; vectorProjectiles->push_back(projectil15);
	Projectil projectil16; projectil16.alive=false; vectorProjectiles->push_back(projectil16);
	Projectil projectil17; projectil17.alive=false; vectorProjectiles->push_back(projectil17);
	Projectil projectil18; projectil18.alive=false; vectorProjectiles->push_back(projectil18);
	Projectil projectil19; projectil19.alive=false; vectorProjectiles->push_back(projectil19);
	Projectil projectil20; projectil20.alive=false; vectorProjectiles->push_back(projectil20);}

void imprimir(SDL_Surface *screen, SDL_Surface *ima, int x, int y){
	 SDL_Rect rect = {x, y, 0, 0};
	 SDL_BlitSurface(ima, NULL, screen, &rect);}

bool colision(int x1, int y1, int w1, int h1, int x2, int y2){
 if(x2 + 80 < x1) {return false;}
 if(x2> x1 + w1) {return false;}
 if(y2 + 80 < y1) {return false;}
 if(y2 > y1 + h1) {return false;}
 return true;}

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
