#pragma once

class Engine
{
private:
	int Dir;
	float Xcoord;
	float Ycoord;
	float Heatpoints; 
	float Speed = 0;
	float Width;
	float Height;
	sf::Image image;
	sf::Texture texture;
	sf::Vertex vertex;

	
	sf::Vector2f Posengine;
	std::string File; // directory to load



public:
	float dx;
	float dy;
	
	const float n_speed = 0.2f;
	sf::Sprite sprite;

	Engine(std::string Str, float HP, float x, float y, float w, float h);
	~Engine();
	bool Update(sf::Int64 time);
	float GetCoordX();
	float GetCoordY();
	void SetDir(int dir);
	void SetSpeed(float speed);
	void InterractMap();
};

Engine::~Engine()
{
	std::cout << "Engine Destructor was called!" << std::endl;
}

void Engine::InterractMap()
{
	for (int i(int(Ycoord / HGRASS)); i < (Ycoord + Height)/HGRASS; i++)
	{
		for (int j(int(Xcoord / WGRASS)); j < (Xcoord + Width) / WGRASS; j++)
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
			else {
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




Engine::Engine(std::string file, float HP, float x, float y, float w, float h) :
	Heatpoints	(HP),
	Width		(w),
	Height		(h),
	File		(file)
{
	
	Speed = 0;
	Engine::Dir = SETDIR;
	Xcoord = XPOS, Ycoord = YPOS;
	image.loadFromFile           ("Images/" + File);
	texture.loadFromImage		 (image);
	sprite.setTexture		     (texture);
	sprite.setTextureRect	     (sf::IntRect(int(x), int(y), int(Width), int(Height)));
	sprite.setPosition           (XPOS, YPOS);
	
	std::cout << "Engine constructor was called!" << std::endl;
}


bool Engine::Update(sf::Int64 time)
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
void Engine::SetSpeed(float speed)
{
	Engine::Speed = speed;
}