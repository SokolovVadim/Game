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
	void InterractMap();
	//bool		DrawEngine			(Engine* engine);
	//bool		CollideEngine		(Engine* engine);
	



};

void Engine::InterractMap()
{
	for (int i(Ycoord / HGRASS); i < (Ycoord + Height)/HGRASS; i++)
	{
		for (int j(Xcoord / WGRASS); j < (Xcoord + Width) / WGRASS; j++)
		{
			if ((i >= 0) && (i < HEIGHT) && (j >= 0) && (j < WIDTH))
			{
				if (TileMap[i][j] == '0')
				{
					if (dy > 0)
						Ycoord = i*HGRASS - Height;
					if (dy < 0)
						Ycoord = i*HGRASS + Height/2 + 18;
					if (dx > 0)
						Xcoord = j*WGRASS - Width;
					if (dx < 0)
						Xcoord = j*WGRASS + Width/2 + 1;

				}
					
				
			}
			else
			{
				std::cout << "i = " << i << std::ends << "j = " << j << std::endl;

			}
		}
	}
}



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
	InterractMap();

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