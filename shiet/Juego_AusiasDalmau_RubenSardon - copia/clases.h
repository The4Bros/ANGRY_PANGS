class MainObj
{
private:
	
	int x, y, w, h;

public:
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

	void setX(int const x)
	{
		this->x = x;
	}
	void setY(int const y)
	{
		this->y = y;
	}
	void setW(int const x)
	{
		this->w = w;
	}
	void setH(int const y)
	{
		this->h = h;
	}

	int getX()
	{
		return x;
	}
	int getY()
	{
		return y;
	}
	int getW()
	{
		return w;
	}
	int getH()
	{
		return h;
	}

};

class Character : public MainObj
{
private:

	//SDL_Surface *buffer = 
public:





};




























































