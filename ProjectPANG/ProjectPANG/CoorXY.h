
#include <math.h>

template<class TYPE>

class CoorXY
{
public:

	TYPE x, y;

	CoorXY()
	{
		x = 0;
		y = 0;
	}
	CoorXY(const TYPE x, const TYPE y)
	{
		this->x = x;
		this->y = y;
	}

	CoorXY<TYPE>& operator = (const CoorXY<TYPE>& punto)
	{
		TYPE x = punto.x;
		TYPE y = punto.y;
		return *this;
	}

	CoorXY& operator - (const CoorXY& punto)
	{
		return *(new CoorXY(x - punto.x, y - punto.y));
	}

	CoorXY& operator + (const CoorXY& punto)
	{
		return *(new CoorXY(x + punto.x, y + punto.y));
	}

	CoorXY& operator += (const CoorXY& punto)
	{
		x += punto.x;
		y += punto.y;
		return *this;
	}

	CoorXY& operator -= (const CoorXY& punto)
	{
		x -= punto.x;
		y -= punto.y;
		return *this;
	}

	bool operator == (const CoorXY& punto)
	{
		return (x == punto.x && y == punto.y);
	}

	bool operator != (const CoorXY& punto)
	{
		return (x != punto.x || y != punto.y);
	}

	TYPE DistanceTo(const CoorXY& punto)
	{
		/*
		TYPE tmpx = punto.x;
		TYPE tmpy = punto.y;

		TYPE tmpx1 = x;
		TYPE tmpy1 = y;

		return sqrt(((tmpx1 - tmpx)*(tmpx1 - tmpx)) + ((tmpy1 - tmpy)*(tmpy1 - tmpy)));
		*/

		return sqrt(((x - punto.x)*(x - punto.x)) + ((y - punto.y)*(y - punto.y)));

	}

};

