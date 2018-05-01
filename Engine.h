#pragma once
//#include "Game.h"

class Engine
{
private:

	double Heatpoints; 
	//double Speed;
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
	int Dir;
	double dx;
	double dy;
	double Speed =0;
	double Xcoord;
	double Ycoord;
	sf::Sprite sprite;

	Engine(std::string Str, double HP, double x, double y, double w, double h);
	~Engine()
	{
		std::cout << "Engine Destructor was called!" << std::endl;
	}
	bool Update(float time);
	//bool		DrawEngine			(Engine* engine);
	//bool		CollideEngine		(Engine* engine);
	



};

#define SPEED(sign)\
float(time * 0.1 * sign)



Engine::Engine(std::string file, double HP, double x, double y, double w, double h) :
	Heatpoints(HP),
	Width(w),
	Height(h),
	File(file)
{
	Speed = 0;
	Dir = SETDIR;
	Xcoord = x, Ycoord = y;
	image.loadFromFile("Images/" + File);
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(x, y, Width, Height));
	sprite.setPosition(XPOS, YPOS);
	
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