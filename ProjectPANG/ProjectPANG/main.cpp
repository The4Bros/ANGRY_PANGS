
#include "MainObj.h"
#include <stdio.h>


int main(int argc, char* argv[])
{
	CoorXY<float>* coorXY = new CoorXY<float>(0, 0);
	MainObj<float>* mainObj = new MainObj<float>(3.0, 4.0);

	//float const f = mainObj->getPos().DistanceTo(*coorXY);
	//printf("%.f", f);

	printf("%.00f", mainObj->getPos().DistanceTo(*coorXY));

	getchar();
	return 0;
}






