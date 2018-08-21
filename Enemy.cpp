
#include "Enemy.h"

//-----------------------------------------------------------------------

Enemy::Enemy() :
	Entity				("Enemy.png", "Enemy", 0.0f, 0.0f, 0.0f, 0.0f),
	bulletTimer			(0.0f),
	isDamageDisplay		(false),
	attackedTimer		(0),
	enemy_next			(nullptr),
	attack				(new Attacked)
{}

//-----------------------------------------------------------------------

Enemy::Enemy(const std::string file, std::string name_, float x, float y, float w, float h) :
	Entity				(file, name_, x, y, w, h),
	bulletTimer			(0.0f),
	isDamageDisplay		(false),
	attackedTimer		(0),
	enemy_next			(nullptr),
	attack				(new Attacked)
{
	setOrigin(w / 2, h / 2);
	if (name_ == "Archer1") {
		dx = -enemy_speed;
		setTextureRect(sf::IntRect(LEFT, TOP, W, H));
	}
}

//-----------------------------------------------------------------------

Enemy::~Enemy()
{
	fout << "Enemy has destructed!" << std::endl;
}

//-----------------------------------------------------------------------

void Enemy::addBullet(const sf::Int64 & time)
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
				}
				if (dy_ < 0)
				{
					Pos.y = i * HGRASS + Height / 2 + 18;
				}
				if (dx_ > 0)
				{
					Pos.x = j * WGRASS - Width + 47.99f;
					dx = -enemy_speed;
					setScale(1.0f, 1.0f);
				}
				if (dx_ < 0)
				{
					Pos.x = float(j * WGRASS + WGRASS);
					dx = enemy_speed;
					setScale(-1.0f, 1.0f);
				}
			}
		}
}

//-----------------------------------------------------------------------

void Enemy::Update(Map & map, sf::Int64 time)
{
	if (Name == "Archer1")
	{
		Timer += time;
		/*if (Timer >= 3000.0f)
		{
		dx *= -1;
		Timer = 0;
		}*/
		CheckCollision(map, dx, 0);
		Pos.x += dx * time;
		setPosition(Pos.x + W / 2, Pos.y + H / 2);
		if (Heatpoints <= 0.0f)
			Alive = false;
	}
}

//-----------------------------------------------------------------------

const sf::Vector2i	Enemy::getSize() const
{
	return sf::Vector2i(W, H);
}

//-------------------------------END-ENEMY.CPP---------------------------
