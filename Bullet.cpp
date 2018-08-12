#include "Bullet.h"

namespace bs {

	Bullet::Bullet(const std::string file, const std::string name_, const float speed, float x, float y, float w, float h, int dir) :
		Entity(file, name_, x, y, w, h),
		_direction(dir),
		_distanceToEnemy(0, 0)
	{
		_bulletSpeed = (speed);
		Speed = _bulletSpeed;
	}



	void Bullet::Update(const float time/*, PoolEnemies & pool*/)
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

		wallsCollision(Pos);		


		//entitiesCollision(pool);


		// Add cicle to find all hitted enemies
		// Add interraction with map


		// decide to use special manager class or functions in the Bullet namespace



		setPosition(Pos.x, Pos.y);

	}




	void wallsCollision(sf::Vector2f & pos)
	{
		if (&pos != nullptr)
		{
			if (pos.x <= BORDER_LENGTH) ///     CONSTANTS SHOULD BE ADDED IN COMPONENTS
				pos.x = BORDER_LENGTH;
			if (pos.y <= BORDER_LENGTH) //    REPEATABLE CODE!!!!!!!!!!!!!!!!!!!!!!
				pos.y = BORDER_LENGTH;
		}

	}

}