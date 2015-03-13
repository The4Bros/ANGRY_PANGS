



class Application{

private:
	bool init;

public:

	

	Application()
	{
		init = true;
	}

	bool Init()
	{
		return init;
	}




};






class Module
{
	virtual bool Init(){ return true; }
	virtual int Update(){ return 2; }
	virtual bool CleanUp(){ return true; }


};










