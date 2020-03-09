#include "Bullet.h"

namespace bs {


	Bullet::Bullet():
		Entity()
	{

	}

	Bullet::Bullet(const std::string file, const std::string name_, const float speed, float x, float y, float w, float h, int dir) :
		Entity(file, name_, x, y, w, h),
		_direction(dir),
		_distanceToEnemy(0, 0)
	{
		_bulletSpeed = (speed);
		Speed = _bulletSpeed;
	}



	void Bullet::Update(const sf::Int64 time/*, PoolEnemies & pool*/)
	{
		switch (_direction)
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
		}
		};

		Pos.x += dx * time;
		Pos.y += dy * time;

		if (wallsCollision(Pos))
		{
			this->setAlive(false);
		}


		//entitiesCollision(pool);


		// Add cicle to find all hitted enemies
		// Add interraction with map


		// decide to use special manager class or functions in the Bullet namespace



		this->setPosition(Pos.x, Pos.y);

	}

	void Bullet::setAlive(const bool alive_status)
	{
		this->Alive = alive_status;
		if (!this->Alive)
			this->Heatpoints = 0.0f;
	}


	bool wallsCollision(sf::Vector2f & pos)
	{
		bool isCollide(false);
		if (&pos != nullptr)
		{
			if (pos.x <= BORDER_LENGTH_X)
			{
				pos.x = BORDER_LENGTH_X;
				isCollide = true;
			}
			if (pos.y <= BORDER_LENGTH_Y) //    REPEATABLE CODE!!!!!!!!!!!!!!!!!!!!!!
			{
				pos.y = BORDER_LENGTH_Y;
				isCollide = true;
			}
		}
		return isCollide;
	}

}