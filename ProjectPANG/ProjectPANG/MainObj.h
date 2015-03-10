#pragma once

#include "CoorXY.h"

template<class TYPE>

class MainObj
{
private:
	
	CoorXY<TYPE> position;

public:
	MainObj()
	{
		CoorXY<int>* position = new CoorXY<int>();
	}

	MainObj<TYPE>(const TYPE x, const TYPE y)
	{
		CoorXY<TYPE>* position = new CoorXY<TYPE>(x, y);
	}

	~MainObj()
	{
	}

	CoorXY<TYPE> getPos()
	{
		return position;
	}


};
