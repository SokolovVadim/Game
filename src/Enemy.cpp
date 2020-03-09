
#include "Enemy.h"

//-----------------------------------------------------------------------

Enemy::Enemy() :
	Entity				("Enemy.png", "Enemy", 0.0f, 0.0f, 0.0f, 0.0f),
	direction			(0u),
	bulletTimer			(0.0f),
	dirTimer			(0.0f),
	isDamageDisplay		(false),
	attackedTimer		(0),
	enemy_next			(nullptr),
	attack				(new Attacked)
{}

//-----------------------------------------------------------------------

Enemy::Enemy(const std::string file, std::string name_,
	float x, float y, float w, float h, float startTimer) :
	Entity				(file, name_, x, y, w, h),
	direction			(0u),
	bulletTimer			(0.0f),
	dirTimer			(startTimer),
	isDamageDisplay		(false),
	attackedTimer		(0),
	enemy_next			(nullptr),
	attack				(new Attacked)
{
	setOrigin(w / 2, h / 2);
	if (name_ == "Archer1") {
		dy = enemy_speed;
		setTextureRect(sf::IntRect(LEFT, TOP, W, H));
	}
}



//-----------------------------------------------------------------------

Enemy::~Enemy()
{
	attack->~Attacked();
	fout << "Enemy has destructed!" << std::endl;
}
//-----------------------------------------------------------------------

const int Enemy::getDir() const
{
	return direction;
}

//-----------------------------------------------------------------------

bool Enemy::isTimeBullet(const sf::Int64 time)
{
	if (bulletTimer >= 100.0f)
	{
		bulletTimer = 0.0f;
		return true;
	}
	else
	{
		bulletTimer += time * 0.012f;
		return false;
	}
}

//-----------------------------------------------------------------------

//#ifndef WS
//#define WS SCREEN::W
//#ifndef HS
//#define HS SCREEN::H

void Enemy::checkPos()
{
	if (this->isAlive())
	{
		//SCREEN::W;
		if ((this->Pos.x <= WGRASS / 2) || (this->Pos.x >= SCREEN::W - WGRASS / 2) ||
			(this->Pos.y <= HGRASS / 2) || (this->Pos.y >= SCREEN::H - HGRASS / 2))
		{
			this->setPosition(WGRASS + 100 + ENEMY::W/2, HGRASS + 100 + ENEMY::H/2);
			std::cout << "!!!!!!!! checkPos !!!!!!!!!" << std::endl;
			Pos.x = WGRASS + 100;
			Pos.y = HGRASS + 100;
		}
	}
}

//#endif WS
//#undef WS
//#endif HS
//#undef HS

//-----------------------------------------------------------------------

float distance(const sf::Vector2f & vec1, const sf::Vector2f & vec2)
{
	return (sqrt(pow(vec1.x - vec2.x, 2) + pow(vec1.y - vec2.y, 2)));
}

//-----------------------------------------------------------------------

void Enemy::followPlayer(const sf::Vector2f & plPos)
{
	
	if (distance(Pos, plPos) <= 200.f) {
		if (Pos.x - plPos.x > 10.0f)  // constant!!!
		{
			direction = LEFT_DIR;
			dx = -enemy_speed;
		}
		if (plPos.x - Pos.x > 10.0f)
		{
			direction = RIGHT_DIR;
			dx = enemy_speed;
		}
		if (Pos.y - plPos.y > 10.0f)
		{
			direction = UP_DIR;
			dy = enemy_speed;
		}
		if (plPos.y - Pos.y > 10.0f)
		{
			direction = DOWN_DIR;
			dy = -enemy_speed;
		}
	}
}

//-----------------------------------------------------------------------

void Enemy::generateDir(const sf::Int64 & time)
{
	dirTimer += 0.01f * time;
	if (dirTimer >= 10.0f)
	{
		direction = abs(int(rand())%4);
		dirTimer = 0.0f;
	}
}

//-----------------------------------------------------------------------

void Enemy::addBullet(const sf::Int64 & time) // !!!
{
	bulletTimer = 0.0f;
}

//-----------------------------------------------------------------------

const float Enemy::createBulletTimeValue()
{
	return float(BULLET_TIMER_DENOMINATOR + rand() % BULLET_TIMER_DENOMINATOR);
}

//-----------------------------------------------------------------------

void Enemy::playerCollision(const Player & Hero)
{
	if (((IsAttacked(Hero.GetPos(), Hero.Height)) && (Hero.GetHit()) && (Hero.GetTimer())))     ////////////////   !!!!!!!!!!!!!!!!!!!!
	{
		SetAttacked();
		ReduceHP(/*damage*/);

	}
}

//-----------------------------------------------------------------------

void Enemy::illustrateDamage()
{
	if (!attack->getAttackedValue())
	{
		setColor(sf::Color::Red);
		attack->SetAttacked(false);
	}
	else
	{
		setColor(sf::Color::White);
	}
}

//-----------------------------------------------------------------------

const float Enemy::getHP()const
{
	return Heatpoints;
}

//-----------------------------------------------------------------------

void Enemy::Destruct()
{
	if (Alive == false)
		this->~Enemy();
}

//-----------------------------------------------------------------------

void Enemy::SetAttacked()
{
	isDamageDisplay = true;
	attackedTimer = 0;
	setColor(sf::Color::Red);
}

//-----------------------------------------------------------------------

void Enemy::DisplayDamage(const sf::Int64 time)
{
	if (isDamageDisplay) {
		attackedTimer += int(time);
		std::cout << "AttackedTimer = " << attackedTimer << std::endl;
		if (attackedTimer > 300)
		{
			isDamageDisplay = false;
			setColor(sf::Color::White);
			attackedTimer = 0;
		}
	}
}

//-----------------------------------------------------------------------

void Enemy::ReduceHP(/*const int damage*/)
{
	//Heatpoints -= damage;
	Heatpoints -= DAMAGE;

	fout << "DAMAGED!" << std::endl;

	if (Heatpoints <= 0)
	{
		Alive = false;
		Destruct();
	}
}

//-----------------------------------------------------------------------

bool Enemy::IsAttacked(const sf::Vector2f & plPos, const float distance)
{
	return attack->IsAttacked(plPos, Pos, distance);
}

//-----------------------------------------------------------------------

const sf::Vector2f & Enemy::getCoord()
{
	return Pos;
}

//-----------------------------------------------------------------------

void Enemy::SetNext(Enemy * next_en)
{
	enemy_next = next_en;
}

//-----------------------------------------------------------------------

Enemy * Enemy::GetNext()
{
	return enemy_next;
}

//-----------------------------------------------------------------------

void Enemy::CheckCollision(Map & map, float dx_, float dy_)
{
	for (int i(int(Pos.y / HGRASS)); i < int(Pos.y + Height + 48) / HGRASS; i++)
		for (int j(int(Pos.x / WGRASS)); j < (int(Pos.x + Width) / WGRASS); j++)
		{
			char sym = map.GetElemMap(i, j);
			if ((sym == '0') || (sym == 'B') || (sym == 'T'))
			{
				if (dy_ > 0)
				{
					Pos.y = i * HGRASS - Height + 15.9999f;
					dy = -enemy_speed;
					setScale(1.0f, 1.0f);
					direction = UP_DIR;
				}
				if (dy_ < 0)
				{
					Pos.y = i * HGRASS + Height / 2 + 35;
					dy = enemy_speed;
					direction = DOWN_DIR;
				}
				if (dx_ > 0)
				{
					Pos.x = j * WGRASS - Width + 47.99f;
					dx = -enemy_speed;
					setScale(1.0f, 1.0f);
					direction = LEFT_DIR;
				}
				if (dx_ < 0)
				{
					Pos.x = float(j * WGRASS + WGRASS);
					dx = enemy_speed;
					setScale(-1.0f, 1.0f);
					direction = RIGHT_DIR;
				}
			}
		}
}

//-----------------------------------------------------------------------

void Enemy::Update(Map & map, sf::Int64 time)
{
	if (Name == "Archer1")
	{
		this->generateDir(time);
		switch (direction)
		{
		case LEFT_DIR:
		{
			dx = -enemy_speed;
			dy = 0.0f;
			break;
		}
		case RIGHT_DIR:
		{
			dx = enemy_speed;
			dy = 0.0f;
			break;
		}
		case UP_DIR:
		{
			dx = 0.0f;
			dy = -enemy_speed;
			break;
		}
		case DOWN_DIR:
		{
			dx = 0.0f;
			dy = enemy_speed;
			break;
		}
		default:
			dx = 0.0f;
			dy = 0.0f;
			break;
		}

		this->checkPos();


		Timer += time;
		/*if (Timer >= 3000.0f)
		{
		dx *= -1;
		Timer = 0;
		}*/
		CheckCollision(map, dx, dy);
		Pos.x += dx * time;
		Pos.y += dy * time; //
		setPosition(Pos.x + W / 2, Pos.y + H / 2);
		if (Heatpoints <= 0.0f)
			Alive = false;
	}

	// addBullet()
}

//-----------------------------------------------------------------------

const sf::Vector2i	Enemy::getSize() const
{
	return sf::Vector2i(W, H);
}

//-------------------------------END-ENEMY.CPP---------------------------
