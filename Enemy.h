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
	Enemy(sf::Image & image_, std::string name_, float x, float y, float w, float h);
	void CheckCollision(Map & map, float dx_, float dy_);
	void Update(Map & map, sf::Int64 time);
};

Enemy::Enemy(sf::Image & image_, std::string name_, float x, float y, float w, float h) :
	Entity(image_, name_, x, y, w, h)
{
	if (name_ == "Archer1") {
		dx = -enemy_speed;
		sprite.setTextureRect(sf::IntRect(LEFT, TOP, W, H));
	}
}



//
//f(dy_ > 0)
//{
//	Ycoord = i * HGRASS - Height + 15.9999f;
//	dy = 0;
//	OnGround = true;
//}
//if (dy_ < 0)
//{
//	Ycoord = i * HGRASS + Height / 2 + 18;
//	dy = 0;
//}
//if (dx_ > 0)
//{
//	Xcoord = j * WGRASS - Width + 47.99f;
//	dx = 0;
//}
//if (dx_ < 0)
//{
//	Xcoord = j * WGRASS + Width / 2 + 1;
//	dx = 0;
//}


void Enemy::CheckCollision(Map & map, float dx_, float dy_)
{
	for (int i(int(Ycoord / HGRASS)); i < int(Ycoord + Height + 48) / HGRASS; i++)
		for (int j(int((Xcoord) / WGRASS)); j < (int(Xcoord + Width) / WGRASS); j++)
		{
			char sym = map.GetElemMap(i, j);
			if ((sym == '0') || (sym == 'B'))
			{
				if (dy_ > 0)
				{
					Ycoord = i * HGRASS - Height + 15.9999f;
				}
				if (dy_ < 0)
				{
					Ycoord = i * HGRASS + Height / 2 + 18;
				}
				if (dx_ > 0)
				{
					Xcoord = j * WGRASS - Width + 47.99f;
					dx = -enemy_speed;
					sprite.setScale(1, 1);
					//break;
				}
				if (dx_ < 0)
				{
					Xcoord = float(j * WGRASS + WGRASS);
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
		Xcoord += dx * time;
		sprite.setPosition(Xcoord + W / 2, Ycoord + H / 2);
		if (Heatpoints <= 0.0f)
			Alive = false;
	}
}