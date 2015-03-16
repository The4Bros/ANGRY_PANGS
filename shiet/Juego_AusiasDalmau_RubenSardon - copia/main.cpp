/*///////////////////////////////////////////////////
	ALIEN VS ROBOTS
		POR: RUBÉN SARDÓN Y AUSIÀS DALMAU
///////////////////////////////////////////////////*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "metodos.h"
//#include "imagenes.h"
using namespace std;

int main(int argc, char* argv[]){
 	bool quit=false; bool menuB=true;
 	//INITIALIZE SDL SYSTEMS
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)==-1){cout<<"Unexpected Error:\n"<<SDL_GetError(); return -1;}
	
 	//MAIN LOOP
	 while(!quit){
 	
	//GLOBAL VARIABLES
	SDL_Event event;
	bool end=false; int i=0; int i2=0; int killCount=0; int roundKillCount=0; int roundNum=0; int damage=25;
 	int ancho = 1080; int alto = 600; // TAMAÑO PANTALLA
 	
 	//LOAD MAIN CHARACTER
 	
 	int counterChar=0; int speedChar=10;
 	Personaje main;
 	main.x=500;main.y=280;main.direction=4;main.position=1;main.alive=true;main.life=300;
	
	//LOAD ENEMIES
	vector<Personaje> enemigos; int directionAnt=1; addEnemies(&enemigos);
	
	//LOAD PROJECTILES
	int counterPro=0; 
	int velProjectil=12; vector<Projectil> vectorProjectiles; addProjectiles(&vectorProjectiles);
	
	
	//LOAD IMAGES
	SDL_Surface *screen, *fondo, icon;
	screen = SDL_SetVideoMode(ancho, alto, 16, SDL_SWSURFACE); if (screen == NULL){cout<<"Error: \n"<< SDL_GetError(); return -1;}
	fondo = IMG_Load("fondo2.png"); if (fondo == NULL){cout<<"Error en IMG_Load= \n"<< SDL_GetError();return -1;}
	icon = IMG_Load("icon.png"); if (icon == NULL){cout<<"Error en IMG_Load= \n"<< SDL_GetError();return -1;}
	
	//MANAGE WINDOW PROPERTIES
	SDL_WM_SetCaption("PANG ", NULL);
	SDL_WM_SetIcon(icon, NULL);
	
	//LOAD AUDIO
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1){cout<<"Error en Mix_OpenAudio: \n"<< Mix_GetError(); return -1;}
	Mix_Music *cancionMenu;
	
	cancionMenu = Mix_LoadMUS("acker-gs.mid");
	if (!cancionMenu){cout<<"Error en Mix_LoadMUS: \n"<< Mix_GetError(); return -1;}
	if(Mix_PlayMusic(cancionMenu, -1) == -1){cout<<"Error en Mix_PlayMusic: "<<Mix_GetError(); return -1;}
    
    srand(time(NULL));
    
while (!end){
		//HANDLE EVENTS
    	
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT){end=true; quit=true;}
        
        //clean screen
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format,0,0,0)); 
        imprimir(screen, fondo, 0, 50);
        
        // KEY STATES
		Uint8 *key = SDL_GetKeyState(NULL);
    	if (key[SDLK_LEFT] && main.x > 0){main.x-=speedChar; main.direction=1;}
		if (key[SDLK_RIGHT] && (main.x + 80) < ancho){ main.x+=speedChar; main.direction=2;}
		//if (key[SDLK_UP] && main.y > 50){ main.y-=speedChar; main.direction=3;}
		//if (key[SDLK_DOWN] && (main.y + 80) < alto){main.y+=speedChar; main.direction=4;}
		if (key[SDLK_SPACE] && counterPro>=6){counterPro=0;
			for(i=0; i<vectorProjectiles.size(); i++){
				if (!vectorProjectiles.at(i).alive){
					vectorProjectiles.at(i).alive=true;
					vectorProjectiles.at(i).direction=main.direction;
					vectorProjectiles.at(i).x=main.x;
					vectorProjectiles.at(i).y=main.y;
					switch(vectorProjectiles.at(i).direction){
						case 1:vectorProjectiles.at(i).y+=48; break;
						case 2:vectorProjectiles.at(i).x+=70; vectorProjectiles.at(i).y+=38; break;
						case 3:vectorProjectiles.at(i).x+=38; break;
						case 4:vectorProjectiles.at(i).x+=38; vectorProjectiles.at(i).y+=60; break;} break;}}}
		counterPro++;
	
	// UPDATE AND PRINT ENEMIES
	for(i=0; i<enemigos.size(); i++){
        if (enemigos.at(i).life<=0){enemigos.at(i).alive=false; enemigos.at(i).counter2=0; enemigos.at(i).life=80; enemigos.at(i).direction=0; enemigos.at(i).y=0; killCount++;}
        if (enemigos.at(i).alive){
        	if(main.y>enemigos.at(i).y && enemigos.at(i).y+enemigos.at(i).speed<alto){
				enemigos.at(i).y+=enemigos.at(i).speed;
				enemigos.at(i).direction=4;}
			else if(main.y<enemigos.at(i).y && enemigos.at(i).y-enemigos.at(i).speed>50){
				enemigos.at(i).y-=enemigos.at(i).speed;
				enemigos.at(i).direction=3;}
			if(main.x>enemigos.at(i).x && enemigos.at(i).x+enemigos.at(i).speed<ancho){
				enemigos.at(i).x+=enemigos.at(i).speed;
				enemigos.at(i).direction=2;}
			else if(main.x<enemigos.at(i).x && enemigos.at(i).x-enemigos.at(i).speed>0){
				enemigos.at(i).x-=enemigos.at(i).speed;
				enemigos.at(i).direction=1;}
			if(colision(main.x,main.y, 80, 80, enemigos.at(i).x,enemigos.at(i).y)){main.life-=2;}
			enemigos.at(i).counter1++;
			switch(enemigos.at(i).direction){
				case 0: imprimir(screen, pixel, enemigos.at(i).x, enemigos.at(i).y); enemigos.at(i).counter1=0; break;
				case 1: switch(enemigos.at(i).position){
					case 1: imprimir(screen, enemigo1Izquierda1, enemigos.at(i).x, enemigos.at(i).y); if(enemigos.at(i).counter1>=15){enemigos.at(i).position=2; enemigos.at(i).counter1=0;} break;
					case 2: imprimir(screen, enemigo1Izquierda2, enemigos.at(i).x, enemigos.at(i).y); if(enemigos.at(i).counter1>=15){enemigos.at(i).position=3; enemigos.at(i).counter1=0;} break;
					case 3: imprimir(screen, enemigo1Izquierda3, enemigos.at(i).x, enemigos.at(i).y); if(enemigos.at(i).counter1>=15){enemigos.at(i).position=4; enemigos.at(i).counter1=0;} break;
					case 4: imprimir(screen, enemigo1Izquierda4, enemigos.at(i).x, enemigos.at(i).y); if(enemigos.at(i).counter1>=15){enemigos.at(i).position=1; enemigos.at(i).counter1=0;} break;} break;
				case 2: switch(enemigos.at(i).position){
					case 1: imprimir(screen, enemigo1Derecha1, enemigos.at(i).x, enemigos.at(i).y); if(enemigos.at(i).counter1>=15){enemigos.at(i).position=2; enemigos.at(i).counter1=0;} break;
					case 2: imprimir(screen, enemigo1Derecha2, enemigos.at(i).x, enemigos.at(i).y); if(enemigos.at(i).counter1>=15){enemigos.at(i).position=3; enemigos.at(i).counter1=0;} break;
					case 3: imprimir(screen, enemigo1Derecha3, enemigos.at(i).x, enemigos.at(i).y); if(enemigos.at(i).counter1>=15){enemigos.at(i).position=4; enemigos.at(i).counter1=0;} break;
					case 4: imprimir(screen, enemigo1Derecha4, enemigos.at(i).x, enemigos.at(i).y); if(enemigos.at(i).counter1>=15){enemigos.at(i).position=1; enemigos.at(i).counter1=0;} break;} break;
				case 3: switch(enemigos.at(i).position){
					case 1:  imprimir(screen, enemigo1Arriba1, enemigos.at(i).x, enemigos.at(i).y); if(enemigos.at(i).counter1>=15){enemigos.at(i).position=2; enemigos.at(i).counter1=0;} break;
					case 2: imprimir(screen, enemigo1Arriba2, enemigos.at(i).x, enemigos.at(i).y); if(enemigos.at(i).counter1>=15){enemigos.at(i).position=3; enemigos.at(i).counter1=0;} break;
					case 3: imprimir(screen, enemigo1Arriba3, enemigos.at(i).x, enemigos.at(i).y); if(enemigos.at(i).counter1>=15){enemigos.at(i).position=4; enemigos.at(i).counter1=0;} break;
					case 4: imprimir(screen, enemigo1Arriba4, enemigos.at(i).x, enemigos.at(i).y); if(enemigos.at(i).counter1>=15){enemigos.at(i).position=1; enemigos.at(i).counter1=0;} break;} break;
				case 4: switch(enemigos.at(i).position){
					case 1: imprimir(screen, enemigo1Abajo1, enemigos.at(i).x, enemigos.at(i).y); if(enemigos.at(i).counter1>=15){enemigos.at(i).position=2; enemigos.at(i).counter1=0;} break;
					case 2: imprimir(screen, enemigo1Abajo2, enemigos.at(i).x, enemigos.at(i).y); if(enemigos.at(i).counter1>=15){enemigos.at(i).position=3; enemigos.at(i).counter1=0;} break;
					case 3: imprimir(screen, enemigo1Abajo3, enemigos.at(i).x, enemigos.at(i).y); if(enemigos.at(i).counter1>=15){enemigos.at(i).position=4; enemigos.at(i).counter1=0;} break;
					case 4: imprimir(screen, enemigo1Abajo4, enemigos.at(i).x, enemigos.at(i).y); if(enemigos.at(i).counter1>=15){enemigos.at(i).position=1; enemigos.at(i).counter1=0;} break;}break;}
			
			SDL_Rect lifeEnemy = {enemigos.at(i).x, enemigos.at(i).y-2, enemigos.at(i).life, 5};
			SDL_FillRect(screen, &lifeEnemy, SDL_MapRGB(screen->format, 255, 0, 0));}
		
        else if(enemigos.at(i).counter2>=100){spawnEnemy(&enemigos.at(i), 80, 80, alto, ancho);}
		else{enemigos.at(i).counter2+=1;}}
		
        //UPDATE AND PRINT PROJECTILES
		for(i=0; i<vectorProjectiles.size(); i++){if (vectorProjectiles.at(i).alive){switch(vectorProjectiles.at(i).direction){
			case 1: imprimir(screen, proyectilIzquierda, vectorProjectiles.at(i).x, vectorProjectiles.at(i).y);
			if(vectorProjectiles.at(i).x > velProjectil){vectorProjectiles.at(i).x -= velProjectil;
				for(i2=0; i2<enemigos.size(); i2++){if(enemigos.at(i2).alive){
					if(colision(vectorProjectiles.at(i).x, vectorProjectiles.at(i).y, proyectilIzquierda->w, proyectilIzquierda->h, enemigos.at(i2).x, enemigos.at(i2).y)){
						vectorProjectiles.at(i).alive=false; enemigos.at(i2).life-=damage;}}}}
				else{vectorProjectiles.at(i).alive=false;} break;
			case 2: imprimir(screen, proyectilDerecha, vectorProjectiles.at(i).x, vectorProjectiles.at(i).y);
			if(vectorProjectiles.at(i).x < ancho-velProjectil){vectorProjectiles.at(i).x += velProjectil;
				for(i2=0; i2<enemigos.size(); i2++){if(enemigos.at(i2).alive){
					if(colision(vectorProjectiles.at(i).x, vectorProjectiles.at(i).y, proyectilDerecha->w, proyectilDerecha->h, enemigos.at(i2).x, enemigos.at(i2).y)){
						vectorProjectiles.at(i).alive=false; enemigos.at(i2).life-=damage;}}}}
				else{vectorProjectiles.at(i).alive=false;}break;
			case 3: imprimir(screen, proyectilArriba, vectorProjectiles.at(i).x, vectorProjectiles.at(i).y);
			if(vectorProjectiles.at(i).y > velProjectil){vectorProjectiles.at(i).y -= velProjectil;
				for(i2=0; i2<enemigos.size(); i2++){if(enemigos.at(i2).alive){
					if(colision(vectorProjectiles.at(i).x, vectorProjectiles.at(i).y, proyectilArriba->w, proyectilArriba->h, enemigos.at(i2).x, enemigos.at(i2).y)){
						vectorProjectiles.at(i).alive=false; enemigos.at(i2).life-=damage;}}}}
				else{vectorProjectiles.at(i).alive=false;}break;
			case 4: imprimir(screen, proyectilAbajo, vectorProjectiles.at(i).x, vectorProjectiles.at(i).y);
			if(vectorProjectiles.at(i).y < alto-velProjectil){vectorProjectiles.at(i).y += velProjectil;
				for(i2=0; i2<enemigos.size(); i2++){if(enemigos.at(i2).alive){
					if(colision(vectorProjectiles.at(i).x, vectorProjectiles.at(i).y, proyectilAbajo->w, proyectilAbajo->h, enemigos.at(i2).x, enemigos.at(i2).y)){
						vectorProjectiles.at(i).alive=false; enemigos.at(i2).life-=damage;}}}}
				else{vectorProjectiles.at(i).alive=false;} break;}}}
		
		
		//UPDATE AND PRINT CHARACTER
		
		 switch(main.direction){
        	case 1:if(counterChar>=10){counterChar=0;switch(main.position){
           		case 1: buffer=personajePrincipalIzquierda1; main.position=2; break;
				case 2: buffer=personajePrincipalIzquierda2; main.position=3; break;
           		case 3: buffer=personajePrincipalIzquierda3; main.position=1; break;}}
           		else{counterChar++;} break;
			case 2:if(counterChar>=10){counterChar=0;switch(main.position){
           		case 1: buffer=personajePrincipalDerecha1; main.position=2; break;
           		case 2: buffer=personajePrincipalDerecha2; main.position=3; break;
           		case 3: buffer=personajePrincipalDerecha3; main.position=1; break;}}
           		else{counterChar++;} break;
        	case 3: buffer=personajePrincipalArriba1; break;
        	case 4:if(counterChar>=10){counterChar=0;switch(main.position){
           		case 1: buffer=personajePrincipalAbajo1; main.position=2; break;
           		case 2: buffer=personajePrincipalAbajo2; main.position=3; break;
           		case 3: buffer=personajePrincipalAbajo3; main.position=1; break;}}
           		else{counterChar++;} break;}
		
        imprimir(screen, buffer, main.x, main.y);
        
        //PRINT LIFE PERSONAJE
        SDL_Rect lifeMain = {ancho-30-main.life, 15, main.life, 20};
		SDL_FillRect(screen, &lifeMain, SDL_MapRGB(screen->format, 255, 0, 0));
		
		//KILL PERSONAJE IF NO LIFE LEFT
        if(main.life<=0){main.alive=false; end=true;}
        
        // UPDATE SCREEN
        SDL_Flip(screen);}
    
    //GAMEOVER MENU
	aux=gameover;
	if(!quit){
		menuB=true;
		imprimir(screen, gameover, 0, 0);
		SDL_Flip(screen); SDL_Delay(2000);}
	while(menuB && !quit){
		if(Mix_PlayMusic(cancionMenu, -1) == -1){Mix_PlayMusic(cancionMenu, -1);}
		SDL_PollEvent(&event);
    	if (event.type == SDL_QUIT){end=true; quit=true; menuB=false;}
		Uint8 *key = SDL_GetKeyState(NULL);
		if(aux==gameover){
			if (key[SDLK_SPACE] ){menuB=false;}
			if (key[SDLK_ESCAPE] ){aux=sure;}}
		else{
			if (key[SDLK_SPACE] ){aux=gameover;}
			if (key[SDLK_ESCAPE] ){end=true; quit=true; menuB=false;}}
		imprimir(screen, aux, 0, 0);
		SDL_Flip(screen); SDL_Delay(150);}
		
		} Mix_CloseAudio(); SDL_Quit(); return 0;}
