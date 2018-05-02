#pragma once

class Engine
{
private:
	int Dir;
	float Xcoord;
	float Ycoord;
	double Heatpoints; 
	double Speed = 0;
	
	//double Xcoord;
	//double Ycoord;
	double Width;
	double Height;
	sf::Image image;
	sf::Texture texture;
	//sf::Sprite sprite;

	
	sf::Vector2f Posengine;
	std::string File; // directory to load



public:
	double dx;
	double dy;
	
	const double n_speed = 0.2;
	sf::Sprite sprite;

	Engine(std::string Str, double HP, float x, float y, double w, double h);
	~Engine()
	{
		std::cout << "Engine Destructor was called!" << std::endl;
	}
	bool Update(float time);
	float GetCoordX();
	float GetCoordY();
	void SetDir(int dir);
	void SetSpeed(double speed);
	//bool		DrawEngine			(Engine* engine);
	//bool		CollideEngine		(Engine* engine);
	



};



float Engine::GetCoordX()
{
	return Engine::Xcoord;
}


float Engine::GetCoordY()
{
	return Engine::Ycoord;
}




Engine::Engine(std::string file, double HP, float x, float y, double w, double h) :
	Heatpoints(HP),
	Width(w),
	Height(h),
	File(file)
{
	Speed = 0;
	Engine::Dir = SETDIR;
	Xcoord = XPOS, Ycoord = YPOS;
	image.loadFromFile           ("Images/" + File);
	texture.loadFromImage		 (image);
	sprite.setTexture		     (texture);
	sprite.setTextureRect	     (sf::IntRect(x, y, Width, Height));
	sprite.setPosition           (XPOS, YPOS);
	
	std::cout << "Engine constructor was called!" << std::endl;
}


bool Engine::Update(float time)
{
	switch (Dir)
	{
	case 0:{
		dx = -Speed, dy = 0;
		break;
	}
	case 1:	{
		dx = Speed, dy = 0;
		break;
	}
	case 2:	{
		dx = 0, dy = -Speed;
		break;
	}
	case 3:	{
		dx = 0, dy = Speed;
		break;
	}
	default:{
		dx = 0; dy = 0;
		std::cout << "No switch choose" << std::endl;
	}
	}

	
	Xcoord += dx * time;
	Ycoord += dy * time;

	Speed = 0;
	sprite.setPosition(Xcoord, Ycoord);

	return true;
}

void Engine::SetDir(int dir)
{
	Engine::Dir = dir;
}
void Engine::SetSpeed(double speed)
{
	Engine::Speed = speed;
}