#pragma once


class Player
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


	bool			OnGround;
	sf::Image		Image;
	sf::Texture		Texture;
	sf::Vertex		vertex;


	sf::Vector2f	PosPlayer;
	std::string		File; // directory to load

	enum STATUS
	{
		LEFT,
		RIGHT,
		UP,
		DOWN,
		SHIFT,
		JUMP,
		STAY
	};

	STATUS Status;

public:
	float			dx;
	float			dy;

	const float		n_speed = 0.2f;
	const float		j_speed = -0.4f;
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
	void			SetHP(std::ostringstream & HeatPoints);
	void			PushScore(std::ostringstream & ScoreString);
	void			GetAir(std::ostringstream & ScoreAir);
	void			PushPower(std::ostringstream & Power_str);
	void			ReducePower(sf::Int64 time);
	void			SetCoord(const float x, const float y);
	void			SetSelect(bool value);
	void			SetMove(bool value);
	void			IncCoord(const float x, const float y);
	unsigned int	GetScore();
	void ActionSwitch(/*double & CurFrame,*/ sf::Int64 & time/*, sf::RenderWindow & window, MyView & View*/);
	void ChooseAction(Player::STATUS dir/*, double & CurFrame*/, sf::Int64 time/*, int X, int Y*/);
	void CheckCollision(Map & map, float dx_, float dy_);
};

Player::Player(std::string file, float x, float y, float w, float h) :
	Heatpoints			(100),
	Power				(10),
	Speed				(0),
	Alive				(true),
	IsMove				(false),
	IsSelect			(false),
	OnGround			(false),
	Score				(0),
	Air					(10),
	Width				(w),
	Height				(h),
	File				(file),
	Status				(STAY)
{
	Speed = 0;
	Player::Dir = SETDIR;
	Xcoord = XPOS, Ycoord = YPOS;
	Image.loadFromFile("Images/" + File);
	Texture.loadFromImage(Image);
	sprite.setTexture(Texture);
	sprite.setTextureRect(sf::IntRect(int(x), int(y), int(Width), int(Height))); // set lower height!!!!
	sprite.setPosition(XPOS, YPOS);

	sprite.setOrigin(w / 2, h / 2);   // new

	fout << "Player constructor was called!" << std::endl;
}



//for (int i(int(Ycoord / HGRASS)); i < (Ycoord + Height) / HGRASS; i++)
//{
//	for (int j(int(Xcoord / WGRASS)); j < (Xcoord + Width) / WGRASS; j++)
//	{
//
//		if ((i >= 0) && (i < HEIGHT) && (j >= 0) && (j < WIDTH))
//		{


void Player::CheckCollision(Map & map, float dx_, float dy_)
{
	for(int i(int(Ycoord/HGRASS)); i < int(Ycoord  + Height)/HGRASS; i++)
		for (int j(int(Xcoord / WGRASS)); j < (int(Xcoord + Width)/WGRASS); j++)
		{
			if (map.GetElemMap(i, j) == '0')
			{
				if (dy_ > 0)
				{
					Ycoord = i * HGRASS - Height;
					dy = 0;
					OnGround = true;
				}
				if (dy_ < 0)
				{
					Ycoord = i * HGRASS + Height;
					dy = 0;
				}
				if (dx_ > 0)
				{
					Xcoord = j * WGRASS - Width;
					dx = 0;
				}
				if (dx_ < 0)
				{
					Xcoord = j * WGRASS + Width;
					dx = 0;
				}
			}
		}
}

void Player::ChooseAction(Player::STATUS dir/*, double & CurFrame*/, sf::Int64 time/*, int X, int Y*/)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		if (SetPower(time))
			SetSpeed(n_speed * 2);
		else
			SetSpeed(n_speed);
	}
	else
	{
		SetSpeed(n_speed);
		ReducePower(time);
	}
	Status = dir;

}

void Player::ActionSwitch(/*double & CurFrame,*/ sf::Int64 & time/*, sf::RenderWindow & window,
	MyView & View*/)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		ChooseAction( LEFT/*, CurFrame*/, time/*, HEROX * int(CurFrame), HEROY*/);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		ChooseAction( RIGHT/*, CurFrame*/, time/*, HEROX * int(CurFrame), 3 * HEROY*/);
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && (OnGround)) {
		//ChooseAction( UP, CurFrame, time, 93 * int(CurFrame), 0);
		Status = JUMP;
		Speed = j_speed;
		OnGround = false;

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		ChooseAction( DOWN/*, CurFrame*/, time/*, 93 * int(CurFrame), 2 * HEROY*/);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		//window.close();
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
	ActionSwitch(time);
	switch (Status)
	{
	case RIGHT:
	{
		dx = Speed;
		break;
	}
	case LEFT:
	{
		dx = -Speed;
		break;
	}
	case UP:
	{
		break; // empty before adding new states
	}
	case DOWN:
	{
		break;
	}
	default: {
		dx = 0; dy = 0;
		//std::cout << "No switch choose" << std::endl;
	}
	}


	Xcoord += dx * time;
	CheckCollision(map, dx, 0);
	Ycoord += dy * time;
	CheckCollision(map, dy, 0);

	if(!IsMove)
		Speed = 0;
	sprite.setPosition(Xcoord + Width/2, Ycoord + Height/2);

	if (Heatpoints <= 0)
	{
		Alive = false;
		Heatpoints = 0;
	}

	if (!OnGround)
		dy += 0.0015f * time;


	return true;
}

void Player::SetDir(int dir)
{
	Dir = dir;
}
void Player::SetSpeed(float speed)
{
	Speed = speed;
}