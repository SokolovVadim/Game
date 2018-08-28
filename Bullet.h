#pragma once

#include "Entity.h"
//#include "PoolEnemies.h"


// bs <=> bulletStuff
namespace bs {


	enum COMPONENTS
	{
		HP = 10,
		BORDER_LENGTH_X = WGRASS - 10,
		BORDER_LENGTH_Y = HGRASS - 10,
		DAMAGE = 10
	};


	class Bullet : public Entity
	{
	public:

		Bullet();

		Bullet									(const std::string file, const std::string name_,
												 const float speed, float x, float y,
												 float w, float h, int dir);

		void			Update					(const sf::Int64 time/*, PoolEnemies & pool*/);
		void			setAlive				(const bool alive_status);
	

	private:
		int					_direction;
		sf::Vector2i		_distanceToEnemy;
		/*static*/ float	_bulletSpeed;
	};

	bool wallsCollision(sf::Vector2f & vec);




	/*class EnemyBullet :public Bullet
	{
	};*/

}