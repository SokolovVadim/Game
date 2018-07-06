#pragma once


class Player
{

private:

	int				Dir;
	int				PurpleTimer;
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
	bool			IsPurple;

	bool			OnGround;
	sf::Image		Image;
	sf::Texture		Texture;
	sf::Vertex		vertex;


	sf::Vector2f	PosPlayer;
	std::string		File; // directory to load

public:
	float			dx;
	float			dy;

	const float		n_speed = 0.2f;
	sf::Sprite		sprite;

	Player(std::string Str, float x, float y, float w, float h);
	~Player();
	bool			Update(sf::Int64 time, Map & map);
	bool			GetAlive();
	bool			SetPower(sf::Int64 time);
	bool			GetSelect();
	bool			GetMove();
	float			GetCoordX() const;
	float			GetCoordY() const;
	float			GetSpeed() const;
	float			GetPower() const;
	void			SetDir(int dir);
	void			SetSpeed(float speed);
	void			InterractMap(sf::Int64 time, Map & map);
	void			SetHP(std::ostringstream & HeatPoints);
	void			PushScore(std::ostringstream & ScoreString);
	void			GetAir(std::ostringstream & ScoreAir);
	void			PushPower(std::ostringstream & Power_str);
	void			ReducePower(sf::Int64 time);
	void			SetCoord(const float x, const float y);
	void			SetSelect(bool value);
	void			SetMove(bool value);
	void			IncCoord(const float x, const float y);
	void PurpleStyle(sf::Int64 & time);
	unsigned int	GetScore();
};

Player::Player(std::string file, float x, float y, float w, float h) :
	PurpleTimer(0),
	Heatpoints(100),
	Power(10),
	Speed(0),
	Alive(true),
	IsMove(false),
	IsSelect(false),
	OnGround(false),
	Score(0),
	Air(10),
	Width(w),
	Height(h),
	File(file)
{
	Speed = 0;
	Player::Dir = SETDIR;
	Xcoord = XPOS, Ycoord = YPOS;
	Image.loadFromFile("Images/" + File);
	Texture.loadFromImage(Image);
	sprite.setTexture(Texture);
	sprite.setTextureRect(sf::IntRect(int(x), int(y), int(Width), int(Height))); // set lower height!!!!
	sprite.setPosition(XPOS, YPOS);

	fout << "Player constructor was called!" << std::endl;
}





void Player::PurpleStyle(sf::Int64 & time)
{
	//std::cout << "time: " << time << std::endl;
	if (IsPurple) {
		PurpleTimer += int(time);
		if (PurpleTimer > 5000)
		{
			IsPurple = false;
			sprite.setColor(sf::Color::White);
			PurpleTimer = 0;
		}
	}
}

void Player::IncCoord(const float x, const float y)
{
	Xcoord += x;
	Ycoord += y;
}

bool Player::GetMove()
{
	return IsMove;
}

void Player::SetMove(bool value)
{
	IsMove = value;
}

bool Player::GetSelect()
{
	return IsSelect;
}

void Player::SetSelect(bool value)
{
	IsSelect = value;
}

void Player::SetCoord(const float x, const float y)
{
	Xcoord = x;
	Ycoord = y;
}

float Player::GetPower() const
{
	return Power;
}

bool Player::SetPower(sf::Int64 time)
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

void Player::ReducePower(sf::Int64 time)
{
	if (Power <= 10)
		Power += float(time) / 5000;
}

void Player::PushPower(std::ostringstream & Power_str)
{
	Power_str.str(std::string());
	Power_str << int(Player::Power);
}

float Player::GetSpeed()const
{
	return Speed;
}

void Player::SetHP(std::ostringstream & HeatPoints)
{
	HeatPoints.str(std::string());
	HeatPoints << int(Player::Heatpoints);
}



void Player::PushScore(std::ostringstream & ScoreString)
{
	ScoreString.str(std::string());
	ScoreString << Score;
}

void Player::GetAir(std::ostringstream & ScoreAir)
{
	ScoreAir.str(std::string());
	ScoreAir << int(Air);
}

bool Player::GetAlive()
{
	return Player::Alive;
}


Player::~Player()
{
	fout << "Finished HP = " << Heatpoints << std::endl;
	fout << "Player Destructor was called!" << std::endl;
}

void Player::InterractMap(sf::Int64 time, Map & map)
{
	for (int i(int(Ycoord / HGRASS)); i < (Ycoord + Height) / HGRASS; i++)
	{
		for (int j(int(Xcoord / WGRASS)); j < (Xcoord + Width) / WGRASS; j++)
		{

			if ((i >= 0) && (i < HEIGHT) && (j >= 0) && (j < WIDTH))
			{

				char sym = map.GetElemMap(i, j);

				if ((sym == '0') || (sym == 'B') || (sym == 'T'))
				{
					if (dy > 0)
						Ycoord = i*HGRASS - Height;
					if (dy < 0)
						Ycoord = i*HGRASS + Height / 2 + 18;
					if (dx > 0)
						Xcoord = j*WGRASS - Width;
					if (dx < 0)
						Xcoord = j*WGRASS + Width / 2 + 1;

				}
				if (sym == 'R')
				{
					Score++;

					map.SetElemMap(i, j, ' ');
					fout << "Interract with Rubin!" << std::endl;

				}
				if (sym == 'M')
				{
					if (Heatpoints > 5)
						Heatpoints -= 5;
					else
						Heatpoints = 0;
					if (Power < 7)
						Power += 3;
					else
						Power = 10;
					map.SetElemMap(i, j, ' ');
					IsPurple = true;
					PurpleTimer = 0;
					sprite.setColor(sf::Color::Magenta);
				}
				if (sym == 'w')
				{
					if (Air <= 0) {
						Heatpoints -= float(time) / 5000;
						Air = 0;
					}
					else
						Air -= float(time) / 5000;
					//fout << "Water on " << i << " " << j << "time: " << time << std::endl;

				}
				else
				{
					if (Air <= 10)
						Air += float(time) / 5000;
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


unsigned int Player::GetScore()
{
	return Player::Score;
}


float Player::GetCoordX() const {

	return Player::Xcoord;
}


float Player::GetCoordY() const {
	return Player::Ycoord;
}



bool Player::Update(sf::Int64 time, Map & map)
{
	switch (Dir)
	{
	case 0: {
		dx = -Speed, dy = 0;
		break;
	}
	case 1: {
		dx = Speed, dy = 0;
		break;
	}
	case 2: {
		dx = 0, dy = -Speed;
		break;
	}
	case 3: {
		dx = 0, dy = Speed;
		break;
	}
	case 4: {
		dx = Speed, dy = -Speed;
		//dx = 0, dy = 0;
	}
	default: {
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

void Player::SetDir(int dir)
{
	Player::Dir = dir;
}
void Player::SetSpeed(float speed)
{
	Player::Speed = speed;
}