#include "PoolBullets.h"



namespace bs {

	PoolBullets::PoolBullets() :
		size_(0)
	{
		std::cout << "Pool of bullets has created!" << std::endl;
	}

	//-----------------------------------------------------------------------

	PoolBullets::PoolBullets(std::size_t size)
	{
		if (size > MAX_POOL_SIZE)
		{
			size_ = MAX_POOL_SIZE;
			std::cout << "Pool is limited of " << MAX_POOL_SIZE <<
				"bullets!" << std::endl;
		}
		else
			size_ = size;
		std::cout << "Pool of bullets has created! Current size = " <<
			size_ << std::endl;

		std::list<Bullet> temp(size_);         // todo: search the best way to init list
		listOfBullets = temp;

	}

	//-----------------------------------------------------------------------

	PoolBullets::~PoolBullets()
	{
		std::cout << "Pool of bullets has destructed!" << std::endl;
	}

	//-----------------------------------------------------------------------

	void PoolBullets::addBullet(const sf::Vector2f & enPos) // add new param(dir)
	{                                                       // write a Bullet::Bullet(Pos, dir);
		Bullet _bullet;
		listOfBullets.push_back(_bullet);
	}

	//-----------------------------------------------------------------------

	void PoolBullets::playerCollision(Player & hero)  // bullets kill player
	{
		std::list<Bullet>::iterator it = listOfBullets.begin();
		std::list<Bullet>::iterator listEnd = listOfBullets.end();
		while (it != listEnd)
		{
			std::cout << "Bullet: " << (*it).Name << std::endl;
			if (((*it).isAlive()) && (hero.isBulletAttack((*it).getPosition(), HEROX))) //!!!
			{
				hero.setBulletAttacked();
			}
		}
		
	}


	//-----------------------------------------------------------------------

	/*bool PoolBullets::isAttacked(const sf::Vector2f & playerPos, const sf::Vector2f & bulletPos,
		const float distance)
	{
		if (pow(playerPos.x - bulletPos.x, 2) + pow(playerPos.y - bulletPos.y, 2) <= pow(distance, 2))
		{
			return true;
		}
		else
			return false;
	}*/

	//-----------------------------------------------------------------------

	void PoolBullets::enemyCollision(Enemy * enemy)   // bullets kill enemies
	{
		std::list<Bullet>::iterator it = listOfBullets.begin();
		std::list<Bullet>::iterator listEnd = listOfBullets.end();
		while (it != listEnd)
		{
			if ((enemy->isAlive()) && (enemy->IsAttacked(it->getPosition(), it->Height)))
			{
				enemy->SetAttacked();
				enemy->ReduceHP();
			}
			it++;
		}
	}




	//-----------------------------------------------------------------------

}