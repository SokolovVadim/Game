#pragma once

class Enemy : public Entity
{
public: 
	Enemy										(const std::string file, std::string name_,
													float x, float y, float w, float h);
	~Enemy();
	void						CheckCollision	(Map & map, float dx_, float dy_);
	void						Update			(Map & map, sf::Int64 time);
	void						SetNext			(Enemy * next_en);
	void ReduceHP();
	void Destruct();
	const sf::Vector2f &    	getCoord		();
	Enemy *						GetNext			();
	bool						IsAttacked		(const sf::Vector2f & plPos);
	const float					getHP			()const;

private:

	enum ENEMY
	{
		W = 64,
		H = 66,
		LEFT = 0,       ///////////////////////////!!!!!!!!!!!!!!!!!!!!!!!! 
		TOP = 5 * H,
		DAMAGE = 60             // from hero on enemy
	};
	const float			enemy_speed = 0.1f;
	Enemy*				enemy_next;
	Attacked * attack;
};

Enemy::Enemy(const std::string file, std::string name_, float x, float y, float w, float h) :
	Entity(file, name_, x, y, w, h),
	enemy_next(nullptr),
	attack(new Attacked)
{
	sprite.setOrigin(w / 2, h / 2);
	if (name_ == "Archer1") {
		dx = -enemy_speed;
		sprite.setTextureRect(sf::IntRect(LEFT, TOP, W, H));
	}
}

Enemy::~Enemy()
{
	fout << "Enemy has destructed!" << std::endl;
}

const float Enemy::getHP()const
{
	return Heatpoints;
}

void Enemy::Destruct()
{
	this->~Enemy();
}

void Enemy::ReduceHP()
{
	Heatpoints -= DAMAGE;

	if (Heatpoints <= 0)
	{
		Destruct();
	}
}

bool Enemy::IsAttacked(const sf::Vector2f & plPos)
{
	return attack->IsAttacked(plPos, Pos);
}

const sf::Vector2f & Enemy::getCoord()
{
	return Pos;
}

void Enemy::SetNext(Enemy * next_en)
{
	enemy_next = next_en;
}

Enemy * Enemy::GetNext()
{
	return enemy_next;
}

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
					sprite.setScale(1, 1);
				}
				if (dx_ < 0)
				{
					Pos.x = float(j * WGRASS + WGRASS);
					dx = enemy_speed;
					sprite.setScale(-1, 1);
				}
			}
		}
}
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
		sprite.setPosition(Pos.x + W / 2, Pos.y + H / 2);
		if (Heatpoints <= 0.0f)
			Alive = false;
	}
}