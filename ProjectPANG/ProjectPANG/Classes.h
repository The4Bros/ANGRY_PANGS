#pragma once

#include <string.h>
#include <stdio.h>

class Brick
{

};
class Ball
{

};

class Enemy
{

};
class Owl
{

};
class Bird
{

};
class Crab
{

};
class Hermit
{

};

class MainCharacter : public MainObj
{
protected:

	int weapon;
	double score;

	SDL_Surface *buffer[18];


	MainCharacter(int const x, int const y, int const w, int const h)
	{
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
		weapon = 2;
		score = 0;
	}

	void setWeapon(int weapon)
	{
		this->weapon = weapon;
	}
	void setScore(double score)
	{
		this->score = score;
	}
	void addScore(double score)
	{
		this->score += score;
	}

	virtual bool loadImages();

	virtual void resetCharacter(int const x, int const y, int const w, int const h, int const score)
	{
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
		weapon = 2;
		this->score = score;
	}


};
class Player1 : public MainCharacter
{
protected:

	bool loadImages()
	{
		buffer[0] = IMG_Load("player1_1.png");
		buffer[1] = IMG_Load("player1_2.png");
		buffer[2] = IMG_Load("player1_3.png");
		buffer[3] = IMG_Load("player1_4.png");
		buffer[5] = IMG_Load("player1_5.png");
		buffer[6] = IMG_Load("player1_6.png");
		buffer[7] = IMG_Load("player1_7.png");
		buffer[8] = IMG_Load("player1_8.png");
		buffer[9] = IMG_Load("player1_9.png");
		buffer[10] = IMG_Load("player1_10.png");
		buffer[11] = IMG_Load("player1_11.png");
		buffer[12] = IMG_Load("player1_12.png");
		buffer[13] = IMG_Load("player1_13.png");
		buffer[14] = IMG_Load("player1_14.png");
		buffer[15] = IMG_Load("player1_15.png");
		buffer[16] = IMG_Load("player1_16.png");
		buffer[17] = IMG_Load("player1_17.png");

		for (int i = 0; i < 18; i++)
		{
			if (buffer[i] == NULL)
			{
				return false;
			}
		}
		return true;
	}
};
class Player2 : public MainCharacter
{
public:

	bool loadImages()
	{
		buffer[0] = IMG_Load("player2_1.png");
		buffer[1] = IMG_Load("player2_2.png");
		buffer[2] = IMG_Load("player2_3.png");
		buffer[3] = IMG_Load("player2_4.png");
		buffer[5] = IMG_Load("player2_5.png");
		buffer[6] = IMG_Load("player2_6.png");
		buffer[7] = IMG_Load("player2_7.png");
		buffer[8] = IMG_Load("player2_8.png");
		buffer[9] = IMG_Load("player2_9.png");
		buffer[10] = IMG_Load("player2_10.png");
		buffer[11] = IMG_Load("player2_11.png");
		buffer[12] = IMG_Load("player2_12.png");
		buffer[13] = IMG_Load("player2_13.png");
		buffer[14] = IMG_Load("player2_14.png");
		buffer[15] = IMG_Load("player2_15.png");
		buffer[16] = IMG_Load("player2_16.png");
		buffer[17] = IMG_Load("player2_17.png");

		for (int i = 0; i < 18; i++)
		{
			if (buffer[i] == NULL)
			{
				return false;
			}
		}
		return true;
	}

};



class LevelArrangment
{
private:
	int numOfBalls;
	brick
};

class Level
{
private:

	int level;

public:

	Level(int level)
	{
		this->level = level;

		FILE *fichero = fopen("LevelArrangment.txt", "r");
		if (fichero == NULL){ perror("Ha habido un error al abrir el archivo."); }
		else{
			char line[2820];
			for (int i = 0; i<100; i++){
				if (fgets(line, 2820, fichero) != NULL){
					parser(line);
				}
			}
			fclose(fichero);
		}



	}






};

class MainObj
{
protected:

	int x, y, w, h;

	MainObj()
	{
		int x = 0;
		int y = 0;
	}
	MainObj(int const x, int const y, int const w, int const h)
	{
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
	}

	~MainObj()
	{
	}

};






