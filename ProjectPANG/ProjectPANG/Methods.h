#pragma once



bool colision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2){
	if (x2 + w2 < x1)
	{
		return false;
	}
	if (x2 > x1 + w1)
	{
		return false;
	}
	if (y2 + h2 < y1)
	{
		return false;
	}
	if (y2 > y1 + h1)
	{
		return false;
	}
	return true;
}

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
