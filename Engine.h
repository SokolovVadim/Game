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
	sf::Sprite sprite;

	
	sf::Vector2f Posengine;
	std::string File; // directory to load



public:
	char Dir;
	double dx;
	double dy;
	double Speed;
	double Xcoord;
	double Ycoord;

	Engine(std::string Str, double HP, double speed, double x, double y, double w, double h);
	bool Update(float time);
	bool		DrawEngine			(Engine* engine);
	bool		CollideEngine		(Engine* engine);
	



};

#define SPEED(sign)\
float(time * 0.1 * sign)



Engine::Engine(std::string file, double HP, double speed, double x, double y, double w, double h) :
	Heatpoints(HP),
	Speed (speed),
	Width(w),
	Height(h),
	File(file)
{
	Xcoord = x, Ycoord = y;
	image.loadFromFile("Image/" + File);
	texture.loadFromImage(image);
	sprite.setTexture(texture);
//	sprite.setTextureRect(sf::IntRect(Width, Height, Width, Height));
	
	
	std::cout << "Engine constructor was called!" << std::endl;
}


bool Update(float time, Engine* engine)
{
	switch (engine->Dir)
	{
	case 0:{
		engine->dx = engine->Speed, engine->dy = 0;
		break;
	}
	case 1:	{
		engine->dx = -engine->Speed, engine->dy = 0;
		break;
	}
	case 2:	{
		engine->dx = 0, engine->dy = engine->Speed;
		break;
	}
	case 3:	{
		engine->dx = 0, engine->dy = -engine->Speed;
		break;
	}
	}

	
	engine->Xcoord += engine->dx * time;
	engine->Ycoord += engine->dy * time;

	return true;
}