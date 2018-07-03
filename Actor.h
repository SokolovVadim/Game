#pragma once

class Actor
{

private:

	int				Dir;
	unsigned int	Score;

	float			Heatpoints;
	float			Power;
	float			Xcoord;
	float			Ycoord;

	float			Speed;
	float			Width;
	float			Height;
	float			Air;

	bool			Alive;
	bool			IsMove;
	bool			IsSelect;

	sf::Image		Image;
	sf::Texture		Texture;
	sf::Vertex		vertex;

	
	sf::Vector2f	PosActor;
	std::string		File; // directory to load

public:
	float			dx;
	float			dy;
	
	const float		n_speed = 0.2f;
	sf::Sprite		sprite;

	Actor							(std::string Str, unsigned int HP, float x, float y, float w, float h);
	~Actor();
	bool			Update			(sf::Int64 time, Map & map);
	bool			GetAlive		();
	bool			SetPower		(sf::Int64 time);
	bool			GetSelect		();
	bool			GetMove			();
	float			GetCoordX		() const;
	float			GetCoordY		() const;
	float			GetSpeed		() const;
	float			GetPower		() const;
	void			SetDir			(int dir);
	void			SetSpeed		(float speed);
	void			InterractMap	(sf::Int64 time, Map & map);
	void			SetHP			(std::ostringstream & HeatPoints);
	void			PushScore		(std::ostringstream & ScoreString);
	void			GetAir			(std::ostringstream & ScoreAir);
	void			PushPower		(std::ostringstream & Power_str);
	void			ReducePower		(sf::Int64 time);
	void			SetCoord		(const float x, const float y);
	void			SetSelect		(bool value);
	void			SetMove			(bool value);
	void			IncCoord		(const float x, const float y);
	unsigned int	GetScore		();
};


void Actor::IncCoord(const float x, const float y)
{
	Xcoord += x;
	Ycoord += y;
}

bool Actor::GetMove()
{
	return IsMove;
}

void Actor::SetMove(bool value)
{
	IsMove = value;
}

bool Actor::GetSelect()
{
	return IsSelect;
}

void Actor::SetSelect(bool value)
{
	IsSelect = value;
}

void Actor::SetCoord(const float x, const float y)
{
	Xcoord = x;
	Ycoord = y;
}

float Actor::GetPower() const
{
	return Power;
}

bool Actor::SetPower(sf::Int64 time)
{
	bool power_flag(true);
	if (Power <= 0) {
		Power = 0;
		power_flag = false;
	}
	else
		Power -= float(time) / 1000;
	return power_flag;
}

void Actor::ReducePower(sf::Int64 time)
{
	if (Power <= 10)
		Power += float(time) / 5000;
}

void Actor::PushPower(std::ostringstream & Power_str)
{
	Power_str.str(std::string());
	Power_str << int(Actor::Power);
}

float Actor::GetSpeed()const
{
	return Speed;
}

void Actor::SetHP(std::ostringstream & HeatPoints)
{
	HeatPoints.str(std::string());
	HeatPoints << int(Actor::Heatpoints);
}



void Actor::PushScore(std::ostringstream & ScoreString)
{
	ScoreString.str(std::string());
	ScoreString << Score;
}

void Actor::GetAir(std::ostringstream & ScoreAir)
{
	ScoreAir.str(std::string());
	ScoreAir << int(Air);
}

bool Actor::GetAlive()
{
	return Actor::Alive;
}


Actor::~Actor()
{
	fout << "Finished HP = " << Heatpoints << std::endl;
	fout << "Actor Destructor was called!" << std::endl;
}

void Actor::InterractMap(sf::Int64 time, Map & map)
{
	for (int i(int(Ycoord / HGRASS)); i < (Ycoord + Height)/HGRASS; i++)
	{
		for (int j(int(Xcoord / WGRASS)); j < (Xcoord + Width) / WGRASS; j++)
		{
		
			if ((i >= 0) && (i < HEIGHT) && (j >= 0) && (j < WIDTH))
			{

				char sym = map.GetElemMap(i, j);

				if ((sym == '0') || (sym == 'B'))
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
				if (sym == 'R')
				{
					Score++;

					map.SetElemMap(i, j, ' ');
					fout << "Interract with Rubin!" << std::endl;
					
				}
				if (sym == 'w')
				{
					if (Air <= 0) {
						Heatpoints -= float(time) / 5000;
						Air = 0;
					}else
						Air -= float(time) / 5000;
					//fout << "Water on " << i << " " << j << "time: " << time << std::endl;
					
				}
				else
				{
					if (Air <= 10)
						Air += float(time)/5000;
				}
				if (sym == 'H')
				{
					if (Heatpoints <= 90)
						Heatpoints += 10;
					else
						Heatpoints = 100;
					map.SetElemMap(i, j, ' ');
					fout << "Take HP bonus. Now HP = " << Heatpoints << std::endl;
				}
				if (sym == 'D')
				{
					if (Heatpoints >= 30)
						Heatpoints -= 30;
					else
					{
						Heatpoints = 0;
						Alive = false;
					}
					map.SetElemMap(i, j, ' ');

					fout << "Bourjua! Now HP = " << Heatpoints << std::endl;
				}

			}
			else {
				//std::cout << "i = " << i << std::ends << "j = " << j << std::endl;
			}
		}
	}
}


unsigned int Actor::GetScore()
{
	return Actor::Score;
}


float Actor::GetCoordX() const {

	return Actor::Xcoord;
}


float Actor::GetCoordY() const {
	return Actor::Ycoord;
}




Actor::Actor(std::string file, unsigned int HP, float x, float y, float w, float h) :
	Heatpoints	(100),
	Power		(10),
	Speed		(0),
	Alive       (true),
	IsMove		(false),
	IsSelect	(false),
	Score       (0),
	Air         (10),
	Width		(w),
	Height		(h),
	File		(file)
{
	Speed = 0;
	Actor::Dir = SETDIR;
	Xcoord = XPOS, Ycoord = YPOS;
	Image.loadFromFile           ("Images/" + File);
	Texture.loadFromImage		 (Image);
	sprite.setTexture		     (Texture);
	sprite.setTextureRect	     (sf::IntRect(int(x), int(y), int(Width), int(Height)));
	sprite.setPosition           (XPOS, YPOS);
	
	fout << "Actor constructor was called!" << std::endl;
}


bool Actor::Update(sf::Int64 time, Map & map)
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
	case 4: {
		dx = Speed, dy = -Speed;
		//dx = 0, dy = 0;
	}
	default:{
		dx = 0; dy = 0;
		//std::cout << "No switch choose" << std::endl;
	}
	}

	
	Xcoord += dx * time;
	Ycoord += dy * time;

	Speed = 0;
	sprite.setPosition(Xcoord, Ycoord);
	InterractMap(time, map);

	if (Heatpoints <= 0)
	{
		Alive = false;
		Heatpoints = 0;
	}

	return true;
}

void Actor::SetDir(int dir)
{
	Actor::Dir = dir;
}
void Actor::SetSpeed(float speed)
{
	Actor::Speed = speed;
}
