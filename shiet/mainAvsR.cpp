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
	SDL_Surface *screen, *buffer, *fondo, *pixel,*proyectilArriba, *proyectilAbajo, *proyectilIzquierda, *proyectilDerecha, *icon, *aux;
	screen = SDL_SetVideoMode(ancho, alto, 16, SDL_SWSURFACE); if (screen == NULL){cout<<"Error: \n"<< SDL_GetError(); return -1;}
	fondo = IMG_Load("fondo2.png"); if (fondo == NULL){cout<<"Error en IMG_Load= \n"<< SDL_GetError();return -1;}
	pixel = IMG_Load("pixel.png"); if (pixel == NULL){cout<<"Error en IMG_Load= \n"<< SDL_GetError();return -1;}
	icon = IMG_Load("icon.png"); if (icon == NULL){cout<<"Error en IMG_Load= \n"<< SDL_GetError();return -1;}
	proyectilArriba = IMG_Load("proyectilArriba.png"); if (proyectilArriba == NULL){cout<<"Error en IMG_Load= \n"<< SDL_GetError();return -1;}
	proyectilAbajo = IMG_Load("proyectilAbajo.png"); if (proyectilAbajo == NULL){cout<<"Error en IMG_Load= \n"<< SDL_GetError();return -1;}
	proyectilIzquierda = IMG_Load("proyectilIzquierda.png"); if (proyectilIzquierda == NULL){cout<<"Error en IMG_Load= \n"<< SDL_GetError();return -1;}
	proyectilDerecha = IMG_Load("proyectilDerecha.png"); if (proyectilDerecha == NULL){cout<<"Error en IMG_Load= \n"<< SDL_GetError();return -1;}
	
	SDL_Surface *menu, *gameover, *howto, *sure;
	menu = IMG_Load("menu.png"); if (fondo == NULL){cout<<"Error en IMG_Load= \n"<< SDL_GetError();return -1;}
	gameover = IMG_Load("gameover.png"); if (gameover == NULL){cout<<"Error en IMG_Load= \n"<< SDL_GetError();return -1;}
	howto = IMG_Load("howto2.png"); if (howto == NULL){cout<<"Error en IMG_Load= \n"<< SDL_GetError();return -1;}
	sure = IMG_Load("sure.png"); if (sure == NULL){cout<<"Error en IMG_Load= \n"<< SDL_GetError();return -1;}
	
	vector<SDL_Surface*> number;
	SDL_Surface *n0, *n1, *n2, *n3, *n4, *n5, *n6, *n7, *n8, *n9, *round, *roundCount;
	n0 = IMG_Load("0.png"); if (n0 == NULL){cout<<"Error en IMG_Load= \n"<< SDL_GetError();return -1;} number.push_back(n0);
	n1 = IMG_Load("1.png"); if (n1 == NULL){cout<<"Error en IMG_Load= \n"<< SDL_GetError();return -1;} number.push_back(n1);
	n2 = IMG_Load("2.png"); if (n2 == NULL){cout<<"Error en IMG_Load= \n"<< SDL_GetError();return -1;} number.push_back(n2);
	n3 = IMG_Load("3.png"); if (n3 == NULL){cout<<"Error en IMG_Load= \n"<< SDL_GetError();return -1;} number.push_back(n3);
	n4 = IMG_Load("4.png"); if (n4 == NULL){cout<<"Error en IMG_Load= \n"<< SDL_GetError();return -1;} number.push_back(n4);
	n5 = IMG_Load("5.png"); if (n5 == NULL){cout<<"Error en IMG_Load= \n"<< SDL_GetError();return -1;} number.push_back(n5);
	n6 = IMG_Load("6.png"); if (n6 == NULL){cout<<"Error en IMG_Load= \n"<< SDL_GetError();return -1;} number.push_back(n6);
	n7 = IMG_Load("7.png"); if (n7 == NULL){cout<<"Error en IMG_Load= \n"<< SDL_GetError();return -1;} number.push_back(n7);
	n8 = IMG_Load("8.png"); if (n8 == NULL){cout<<"Error en IMG_Load= \n"<< SDL_GetError();return -1;} number.push_back(n8);
	n9 = IMG_Load("9.png"); if (n9 == NULL){cout<<"Error en IMG_Load= \n"<< SDL_GetError();return -1;} number.push_back(n9);
	round = IMG_Load("round.png"); if (round == NULL){cout<<"Error en IMG_Load= \n"<< SDL_GetError();return -1;} 
	SDL_Surface *personajePrincipalArriba1, *personajePrincipalAbajo1,  *personajePrincipalAbajo2,  *personajePrincipalAbajo3;
	personajePrincipalArriba1 = IMG_Load("personajePrincipalArriba1.png"); if (personajePrincipalArriba1 == NULL){cout<<"Error en IMG_Load= \n"<< SDL_GetError();return -1;}
	personajePrincipalAbajo1=IMG_Load("personajePrincipalAbajo1.png"); if (personajePrincipalAbajo1 == NULL){cout<<"Error en IMG_Load= \n"<< SDL_GetError();return -1;}
	personajePrincipalAbajo2=IMG_Load("personajePrincipalAbajo2.png"); if (personajePrincipalAbajo2 == NULL){cout<<"Error en IMG_Load= \n"<< SDL_GetError();return -1;}
	personajePrincipalAbajo3=IMG_Load("personajePrincipalAbajo3.png"); if (personajePrincipalAbajo3 == NULL){cout<<"Error en IMG_Load= \n"<< SDL_GetError();return -1;}
	SDL_Surface *personajePrincipalIzquierda1,  *personajePrincipalIzquierda2,  *personajePrincipalIzquierda3;
	personajePrincipalIzquierda1=IMG_Load("personajePrincipalIzquierda1.png"); if (personajePrincipalIzquierda1 == NULL){cout<<"Error en IMG_Load= \n"<< SDL_GetError();return -1;}
	personajePrincipalIzquierda2=IMG_Load("personajePrincipalIzquierda2.png"); if (personajePrincipalIzquierda2 == NULL){cout<<"Error en IMG_Load= \n"<< SDL_GetError();return -1;}
	personajePrincipalIzquierda3=IMG_Load("personajePrincipalIzquierda3.png"); if (personajePrincipalIzquierda3 == NULL){cout<<"Error en IMG_Load= \n"<< SDL_GetError();return -1;}
	SDL_Surface *personajePrincipalDerecha1,  *personajePrincipalDerecha2,  *personajePrincipalDerecha3;
	personajePrincipalDerecha1=IMG_Load("personajePrincipalDerecha1.png"); if (personajePrincipalDerecha1 == NULL){cout<<"Error en IMG_Load= \n"<< SDL_GetError();return -1;}
	personajePrincipalDerecha2=IMG_Load("personajePrincipalDerecha2.png"); if (personajePrincipalDerecha2 == NULL){cout<<"Error en IMG_Load= \n"<< SDL_GetError();return -1;}
	personajePrincipalDerecha3=IMG_Load("personajePrincipalDerecha3.png"); if (personajePrincipalDerecha3 == NULL){cout<<"Error en IMG_Load= \n"<< SDL_GetError();return -1;}
	
	SDL_Surface *enemigo1Arriba1,  *enemigo1Arriba2,  *enemigo1Arriba3,  *enemigo1Arriba4;
	enemigo1Arriba1 = IMG_Load("enemigo1Arriba1.png"); if (enemigo1Arriba1 == NULL){cout<<"Error en IMG_Load= \n"<< SDL_GetError();return -1;}
	enemigo1Arriba2 = IMG_Load("enemigo1Arriba2.png"); if (enemigo1Arriba2 == NULL){cout<<"Error en IMG_Load= \n"<< SDL_GetError();return -1;}
	enemigo1Arriba3 = IMG_Load("enemigo1Arriba3.png"); if (enemigo1Arriba3 == NULL){cout<<"Error en IMG_Load= \n"<< SDL_GetError();return -1;}
	enemigo1Arriba4 = IMG_Load("enemigo1Arriba4.png"); if (enemigo1Arriba4 == NULL){cout<<"Error en IMG_Load= \n"<< SDL_GetError();return -1;}
	SDL_Surface *enemigo1Abajo1,  *enemigo1Abajo2,  *enemigo1Abajo3,  *enemigo1Abajo4;
	enemigo1Abajo1 = IMG_Load("enemigo1Abajo1.png"); if (enemigo1Abajo1 == NULL){cout<<"Error en IMG_Load= \n"<< SDL_GetError();return -1;}
	enemigo1Abajo2 = IMG_Load("enemigo1Abajo2.png"); if (enemigo1Abajo2 == NULL){cout<<"Error en IMG_Load= \n"<< SDL_GetError();return -1;}
	enemigo1Abajo3 = IMG_Load("enemigo1Abajo3.png"); if (enemigo1Abajo3 == NULL){cout<<"Error en IMG_Load= \n"<< SDL_GetError();return -1;}
	enemigo1Abajo4 = IMG_Load("enemigo1Abajo4.png"); if (enemigo1Abajo4 == NULL){cout<<"Error en IMG_Load= \n"<< SDL_GetError();return -1;}
	SDL_Surface *enemigo1Izquierda1,  *enemigo1Izquierda2,  *enemigo1Izquierda3,  *enemigo1Izquierda4;
	enemigo1Izquierda1 = IMG_Load("enemigo1Izquierda1.png"); if (enemigo1Izquierda1 == NULL){cout<<"Error en IMG_Load= \n"<< SDL_GetError();return -1;}
	enemigo1Izquierda2 = IMG_Load("enemigo1Izquierda2.png"); if (enemigo1Izquierda2 == NULL){cout<<"Error en IMG_Load= \n"<< SDL_GetError();return -1;}
	enemigo1Izquierda3 = IMG_Load("enemigo1Izquierda3.png"); if (enemigo1Izquierda3 == NULL){cout<<"Error en IMG_Load= \n"<< SDL_GetError();return -1;}
	enemigo1Izquierda4 = IMG_Load("enemigo1Izquierda4.png"); if (enemigo1Izquierda4 == NULL){cout<<"Error en IMG_Load= \n"<< SDL_GetError();return -1;}
	SDL_Surface *enemigo1Derecha1,  *enemigo1Derecha2,  *enemigo1Derecha3,  *enemigo1Derecha4;
	enemigo1Derecha1 = IMG_Load("enemigo1Derecha1.png"); if (enemigo1Derecha1 == NULL){cout<<"Error en IMG_Load= \n"<< SDL_GetError();return -1;}
	enemigo1Derecha2 = IMG_Load("enemigo1Derecha2.png"); if (enemigo1Derecha2 == NULL){cout<<"Error en IMG_Load= \n"<< SDL_GetError();return -1;}
	enemigo1Derecha3 = IMG_Load("enemigo1Derecha3.png"); if (enemigo1Derecha3 == NULL){cout<<"Error en IMG_Load= \n"<< SDL_GetError();return -1;}
	enemigo1Derecha4 = IMG_Load("enemigo1Derecha4.png"); if (enemigo1Derecha4 == NULL){cout<<"Error en IMG_Load= \n"<< SDL_GetError();return -1;}
	
	//MANAGE WINDOW PROPERTIES
	SDL_WM_SetCaption("Alien vs Robots ", NULL);
	SDL_WM_SetIcon(icon, NULL);
	
	//LOAD AUDIO
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1){cout<<"Error en Mix_OpenAudio: \n"<< Mix_GetError(); return -1;}
	Mix_Music *cancionMenu;
	
	cancionMenu = Mix_LoadMUS("acker-gs.mid");
	if (!cancionMenu){cout<<"Error en Mix_LoadMUS: \n"<< Mix_GetError(); return -1;}
	if(Mix_PlayMusic(cancionMenu, -1) == -1){cout<<"Error en Mix_PlayMusic: "<<Mix_GetError(); return -1;}
    
    
while (!end){
	// MENU
	aux=menu;
	int positionM=1;
		while(menuB && !quit){
			int counterMenu=0;
			SDL_PollEvent(&event);
        	if (event.type == SDL_QUIT){end=true; quit=true; menuB=false;}
			Uint8 *key = SDL_GetKeyState(NULL);
			if(aux==menu){
			if (key[SDLK_UP]){
				switch(positionM){
					case 1: break;
					case 2: positionM--; break;
					case 3: positionM--; break;}}
			if (key[SDLK_DOWN] ){
				switch(positionM){
					case 1: positionM++; break;
					case 2: positionM++; break;
					case 3: break;}}
			if (key[SDLK_SPACE] ){
				switch(positionM){
					case 1: menuB=false; break;
					case 2: aux=howto; positionM=4; SDL_Delay(2000); break;
					case 3: aux=sure; positionM=4; break;}}}
			else if(aux==howto){if (key[SDLK_SPACE] ){aux=menu; positionM=1;}}
			else{
				if (key[SDLK_SPACE] ){aux=menu; positionM=1;}
				if (key[SDLK_ESCAPE] ){end=true; quit=true; menuB=false;}}
			
			imprimir(screen, aux, 0, 0);
			switch(positionM){
					case 1: imprimir(screen, personajePrincipalDerecha1, 810, 260); break;
					case 2: imprimir(screen, personajePrincipalDerecha1, 570, 370); break;
					case 3: imprimir(screen, personajePrincipalDerecha1, 370, 490); break;
					case 4: imprimir(screen, personajePrincipalDerecha1, 1130, 600); break;}
			
			SDL_Flip(screen); SDL_Delay(100);}
		
	// NEXT ROUND
	if(killCount>=roundKillCount && !quit){
		for(i=0; i<enemigos.size(); i++){enemigos.at(i).life=0; if(roundNum<5){enemigos.at(i).speed+=1;}}
		if (damage>5){damage-=5;}
		roundKillCount+=10; killCount=0;
		roundNum++;
		switch(roundNum){
			case 1: roundCount=n1; break;
			case 2: roundCount=n2; break;
			case 3: roundCount=n3; break;
			case 4: roundCount=n4; break;
			case 5: roundCount=n5; break;
			case 6: roundCount=n6; break;
			case 7: roundCount=n7; break;
			case 8: roundCount=n8; break;
			case 9: roundCount=n9; break;}
		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format,0,0,0));
		imprimir(screen, personajePrincipalAbajo1, 500, 280);
		imprimir(screen, roundCount, 450, 310);
		imprimir(screen, round, 310, 300);
		
		SDL_Flip(screen); SDL_Delay(3000);}
		
		//HANDLE EVENTS
    	srand(time(NULL));
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT){end=true; quit=true;}
        
        //clean screen
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format,0,0,0)); 
        imprimir(screen, fondo, 0, 50);
        
        // KEY STATES
		Uint8 *key = SDL_GetKeyState(NULL);
    	if (key[SDLK_LEFT] && main.x > 0){main.x-=speedChar; main.direction=1;}
		if (key[SDLK_RIGHT] && (main.x + 80) < ancho){ main.x+=speedChar; main.direction=2;}
		if (key[SDLK_UP] && main.y > 50){ main.y-=speedChar; main.direction=3;}
		if (key[SDLK_DOWN] && (main.y + 80) < alto){main.y+=speedChar; main.direction=4;}
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
