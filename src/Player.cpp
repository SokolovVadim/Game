#include "Player.h"

Player::Player(const std::string file, const std::string name, float x, float y, float w, float h) :
	Entity				(file, name, x, y, w, h),
	Dir					(SETDIR),
	PurpleTimer			(0),
	FireTimer			(0),
	HitTimer			(0.f),
	BulletTimer			(0.0f),
	Score				(0),
	Power				(10),
	IsSelect			(false),
	IsPurple			(false),
	IsOnFire			(false),
	IsHit				(false),
	IsBulletAttacked	(false),
	isDamagedByBullet	(false),
	Air					(10)   /// aaaawful constant!!!!!!
{
	Image.loadFromFile("Images/" + File);
	Texture.loadFromImage(Image);
	setTexture(Texture);
	setTextureRect(sf::IntRect(int(x), int(y), int(Width), int(Height)));
	setPosition(XPOS, YPOS);

	fout << "Player constructor was called!" << std::endl;
}

void Player::underFire(const sf::Int64 & time)
{
	if (IsBulletAttacked) {
		if (BulletTimer > 10)
		{
			IsBulletAttacked = false;
			setColor(sf::Color::White);
			BulletTimer = 0;
		}
		else
		{
			BulletTimer += time*0.012f;
		}
	}
	if (isDamagedByBullet)
	{
		Heatpoints -= BULLET_DAMAGE;
		isDamagedByBullet = false;
	}
}

void Player::setBulletAttacked()
{
	IsBulletAttacked = true;
	isDamagedByBullet = true;
	BulletTimer = 0.0f;
	setColor(sf::Color::Red);
}


bool Player::isBulletAttack(const sf::Vector2f & bullPos, const float distance)
{
	if (pow(Pos.x - bullPos.x, 2) + pow(Pos.y - bullPos.y, 2) < pow(distance, 2))
	{
		return true;
	}
	else
		return false;
}

bool Player::GetTimer() const
{
	if (HitTimer == 0.0f)
		return true;
	else
		return false;
}

const sf::Vector2f & Player::GetPos() const
{
	return Pos;
}

bool Player::GetHit()const
{
	return IsHit;
}

void Player::Hit(sf::Int64 & time, int Y)
{
	if (IsHit) {

		// set attacked!

		HitTimer += 0.012f * time;              // find normal value!!!!!!


		if (HitTimer > 6)  /// maybe equals
		{
			IsHit = false;
			HitTimer = 0;
		}
		setTextureRect(sf::IntRect(HEROX * int(HitTimer), Y, HEROX, HEROY));
	}
}

void Player::SetHit()
{
	IsHit = true;
	HitTimer = 0;
}

void Player::SetRed()
{
	IsOnFire = true;
	FireTimer = 0;
	setColor(sf::Color::Red);
}

void Player::SetPurple()
{
	IsPurple = true;
	PurpleTimer = 0;
	setColor(sf::Color::Magenta);
}

void Player::OnFire(sf::Int64 & time)
{
	if (IsOnFire) {
		FireTimer += int(time);
		Heatpoints -= float(time) / 100;
		if (FireTimer > 3000)
		{
			IsOnFire = false;
			setColor(sf::Color::White);
			FireTimer = 0;
		}
	}
}


void Player::PurpleStyle(sf::Int64 & time)
{
	//std::cout << "time: " << time << std::endl;
	if (IsPurple) {
		PurpleTimer += int(time);
		if (PurpleTimer > 5000)
		{
			IsPurple = false;
			setColor(sf::Color::White);
			PurpleTimer = 0;
		}
	}
}

void Player::IncCoord(const float x, const float y)
{
	Pos.x += x;
	Pos.y += y;
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
	Pos.x = x;
	Pos.y = y;
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

void Player::IncreasePower(sf::Int64 time)
{
	if (Power <= 10)
		Power += float(time) / 5000;
}

void Player::PushPower(std::ostringstream & Power_str)
{
	Power_str.str(std::string());
	Power_str << int(Power);
}

float Player::GetSpeed()const
{
	return Speed;
}

void Player::SetHP(std::ostringstream & HeatPoints)
{
	HeatPoints.str(std::string());
	HeatPoints << int(Heatpoints);
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
	return Alive;
}


Player::~Player()
{
	fout << "Finished HP = " << Heatpoints << std::endl;
	fout << "Player Destructor was called!" << std::endl;

}

void Player::InterractMap(sf::Int64 time, Map & map)
{
	for (int i(int(Pos.y / HGRASS)); i < (Pos.y + Height) / HGRASS; i++)
	{
		for (int j(int(Pos.x / WGRASS)); j < (Pos.x + Width) / WGRASS; j++)
		{

			if ((i >= 0) && (i < HEIGHT) && (j >= 0) && (j < WIDTH))
			{

				char sym = map.GetElemMap(i, j);

				if ((sym == '0') || (sym == 'B') || (sym == 'T'))
				{
					if (dy > 0)
						Pos.y = i*HGRASS - Height;
					if (dy < 0)
						Pos.y = i*HGRASS + Height;
					if (dx > 0)
						Pos.x = j*WGRASS - Width;
					if (dx < 0)
						Pos.x = j*WGRASS + 0.75f * Width;

				}
				if (sym == 'R')
				{
					Score++;

					map.SetElemMap(i, j, ' ');
					fout << "Interract with Rubin!" << std::endl;

				}
				if (sym == 'M')
				{
					if (Heatpoints > 10)
						Heatpoints -= 10;
					else
						Heatpoints = 0;
					if (Power < 7)
						Power += 3;
					else
						Power = 10;
					map.SetElemMap(i, j, ' ');
					SetPurple();
				}
				if (sym == 'L')
				{
					SetRed();
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
	return Score;
}


float Player::GetCoordX() const {

	return Pos.x;
}


float Player::GetCoordY() const {
	return Pos.y;
}


int Player::GetDir() const {
	return Dir;
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


	Pos.x += dx * time;
	Pos.y += dy * time;

	Speed = 0;
	setPosition(Pos.x, Pos.y);
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
	Dir = dir;
}
void Player::SetSpeed(float speed)
{
	Speed = speed;
}