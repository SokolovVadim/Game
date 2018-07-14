#pragma once

class Enemy : public Entity
{
private:
	enum ENTITY
	{
		W = 64,
		H = 66,
		LEFT = 0,       ///////////////////////////!!!!!!!!!!!!!!!!!!!!!!!! 
		TOP = 5 * H 
	};
	const float enemy_speed = 0.1f;
public: 
	Enemy							(const std::string file, std::string name_, float x, float y, float w, float h);
	void			CheckCollision	(Map & map, float dx_, float dy_);
	void			Update			(Map & map, sf::Int64 time);
};

Enemy::Enemy(const std::string file, std::string name_, float x, float y, float w, float h) :
	Entity(file, name_, x, y, w, h)
{
	if (name_ == "Archer1") {
		dx = -enemy_speed;
		sprite.setTextureRect(sf::IntRect(LEFT, TOP, W, H));
	}
}



void Enemy::CheckCollision(Map & map, float dx_, float dy_)
{
	for (int i(int(pos.y / HGRASS)); i < int(pos.y + Height + 48) / HGRASS; i++)
		for (int j(int(pos.x / WGRASS)); j < (int(pos.x + Width) / WGRASS); j++)
		{
			char sym = map.GetElemMap(i, j);
			if ((sym == '0') || (sym == 'B'))
			{
				if (dy_ > 0)
				{
					pos.y = i * HGRASS - Height + 15.9999f;
				}
				if (dy_ < 0)
				{
					pos.y = i * HGRASS + Height / 2 + 18;
				}
				if (dx_ > 0)
				{
					pos.x = j * WGRASS - Width + 47.99f;
					dx = -enemy_speed;
					sprite.setScale(1, 1);
				}
				if (dx_ < 0)
				{
					pos.x = float(j * WGRASS + WGRASS);
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
		pos.x += dx * time;
		sprite.setPosition(pos.x + W / 2, pos.y + H / 2);
		if (Heatpoints <= 0.0f)
			Alive = false;
	}
}