
#include <cstdlib>
#include <stdlib.h>
#include <iostream>

#include <string.h>
#include <vector>

using namespace std;

struct Stage_Arrangement
{
	int time_limit;
	int player_pos[4];
	vector<int[4]> balloons;
	vector<int[3]> bricks;
	vector<int[4]> enemies;
	vector<int[3]> stairs;

	~Stage_Arrangement(){}
};


void parser(char *line, Stage_Arrangement *stage){
		char *tmp_char;
		int tmp4[4], tmp3[3];
		vector<int>::iterator it;
		
		stage->time_limit = atoi(strtok(line, "%"));
		
		tmp_char = strtok(NULL, "%");
		stage->balloons.clear();
		if (tmp_char != "0")
		{
			for (int i = 0; i < 4; i++)
			{
				tmp4[0] = atoi(strtok(tmp_char, ","));
				tmp4[1] = atoi(strtok(tmp_char, ","));
				tmp4[2] = atoi(strtok(tmp_char, ","));
				tmp4[3] = atoi(tmp_char);
				
				stage->balloons.push_back(tmp4);
			}
		}
		/*
		tmp_char = strtok(NULL, "%");
		stage->bricks.clear();
		if (tmp_char != "0")
		{
			for (int i = 0; i < 4; i++)
			{
				tmp3[0] = atoi(strtok(tmp_char, ","));
				tmp3[1] = atoi(strtok(tmp_char, ","));
				tmp3[2] = atoi(tmp_char);
				
				stage->bricks.push_back(tmp3);
			}
		}
		
		tmp_char = strtok(NULL, "%");
		stage->enemies.clear();
		if (tmp_char != "0")
		{
			for (int i = 0; i < 4; i++)
			{
				tmp4[0] = atoi(strtok(tmp_char, ","));
				tmp4[1] = atoi(strtok(tmp_char, ","));
				tmp4[2] = atoi(strtok(tmp_char, ","));
				tmp4[3] = atoi(strtok(tmp_char, "|"));
				
				stage->enemies.push_back(tmp4);
			}
		}
		
		tmp_char = strtok(NULL, "%");
		stage->stairs.clear();
		if (tmp_char != "0")
		{
			for (int i = 0; i < 4; i++)
			{
				tmp3[0] = atoi(strtok(tmp_char, ","));
				tmp3[1] = atoi(strtok(tmp_char, ","));
				tmp3[2] = atoi(tmp_char);
				
				stage->stairs.push_back(tmp3);
			}
		}*/
	}


void print(Stage_Arrangement* stage)
{
	vector<int[4]>::iterator it4;
	vector<int[3]>::iterator it3;
	
	cout << "time_limit: " << stage->time_limit << endl;
	
	for (int i = 0; i < 4; i++){ cout << "player_pos: " << stage->player_pos[i] << " "; } cout << endl;
	
	int i = 1;
	for (it4 = stage->balloons.begin(); it4 != stage->balloons.end(); it4++)
	{
		cout << "balloon " << i << endl
		<< "\t type: " << *it4[0]
		<< "\t max height: " << *it4[1]
		<< "\t x: " << *it4[2]
		<< "\t y: " << *it4[3] << endl;
		i++;
	}
	cout << endl;
	
	i = 1;
	for (it3 = stage->bricks.begin(); it3 != stage->bricks.end(); it3++)
	{
		cout << "brick " << i << endl
		<< "\t type: " << *it3[0]
		<< "\t x: " << *it3[1]
		<< "\t y: " << *it3[2] << endl;
		i++;
	}
	cout << endl;
	
	i = 1;
	for (it4 = stage->enemies.begin(); it4 != stage->enemies.end(); it4++)
	{
		cout << "enemy " << i << endl
		<< "\t type: " << *it4[0]
		<< "\t spawn time: " << *it4[1]
		<< "\t x: " << *it4[2]
		<< "\t y: " << *it4[3] << endl;
		i++;
	}
	cout << endl;
	
	i = 1;
	for (it3 = stage->stairs.begin(); it3 != stage->stairs.end(); it3++)
	{
		cout << "balloon " << i << endl
		<< "\t size: " << *it3[0]
		<< "\t x: " << *it3[1]
		<< "\t y: " << *it3[2] << endl;
		i++;
	}
	cout << endl;
}



int main()
{
	FILE *fichero = fopen("LevelArrangment.txt", "r");
    if(fichero==NULL){ perror("Ha habido un error al abrir el archivo."); }
    else
	{
		Stage_Arrangement stage;
		char line[100];
		fgets(line, 100, fichero);
		parser(line, &stage);
		
		//for (int i = 0; fgets(line, 100, fichero) != NULL; i++){ userList[i] = parser(line); }
		fclose(fichero);
		
		//print(stage);
	}
	
	system("pause");
	return 0;
	
}
	
	






	
			

