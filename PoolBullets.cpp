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

	void PoolBullets::draw(sf::RenderWindow & window)
	{
		std::list<Bullet>::iterator it = listOfBullets.begin();
		std::list<Bullet>::iterator listEnd = listOfBullets.end();
		//std::size_t size(0lu);
		while ((it != listEnd) /*&& (size < size_)*/)
		{
			if (it->isAlive())
				window.draw(it->getSprite());
			it++;
		}
	}

	//-----------------------------------------------------------------------

	std::size_t PoolBullets::getSize()
	{
		return listOfBullets.size();
	}

	//-----------------------------------------------------------------------

	void PoolBullets::Update(const sf::Int64 time)
	{
		std::list<Bullet>::iterator it = listOfBullets.begin();
		std::list<Bullet>::iterator listEnd = listOfBullets.end();
		//std::size_t size(0lu);
		while ((it != listEnd)/* && (size < size_)*/)
		{
			if(it->isAlive())
				it->Update(time);
			it++;
		}
	}

	//-----------------------------------------------------------------------

	void PoolBullets::addBullet(const sf::Vector2f & enPos, const std::string file, const std::string name_, const float speed, const int dir) // add new param(dir)
	{                                                       
		//Bullet _bullet(file, name_, speed, enPos.x, enPos.y, 64, 66, dir);
		listOfBullets.push_back(*(new Bullet(file, name_, speed, enPos.x, enPos.y, 64, 66, dir)));
		size_++;
	}

	//-----------------------------------------------------------------------

	void PoolBullets::playerCollision(Player & hero)  // bullets kill player
	{
		std::list<Bullet>::iterator it = listOfBullets.begin();
		std::list<Bullet>::iterator listEnd = listOfBullets.end();
		while (it != listEnd)
		{
			//std::cout << "Bullet: " << it->Name << std::endl;
			if ((it->isAlive()) && (hero.isBulletAttack(it->getPosition(), HEROX))) //!!!
			{
				hero.setBulletAttacked();
				it->setAlive(false);
			}
			it++;
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
				it->Alive = false;
			}
			it++;
		}
	}




	//-----------------------------------------------------------------------

}