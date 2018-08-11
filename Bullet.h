#pragma once

#include "Entity.h"
#include "PoolEnemies.h"



namespace bulletStuff {


	enum COMPONENTS
	{
		HP = 10,
		BORDER_LENGTH = 10,
		DAMAGE = 10
	};


	class Bullet : public Entity
	{
	public:

		Bullet	(const std::string file, const std::string name_,
			const float speed, float x, float y, float w, float h, int dir);

		void Update					(const float time, PoolEnemies & pool);
		void entitiesCollision		(PoolEnemies & pool);

	private:
		int _direction;
		sf::Vector2i _distanceToEnemy;
		/*static*/ float _bulletSpeed;
	};

	void wallsCollision(sf::Vector2f & vec);




	/*class EnemyBullet :public Bullet
	{
	};*/

}