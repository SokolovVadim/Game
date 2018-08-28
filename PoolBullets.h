#pragma once

#ifndef POOL_BULLETS_H
#define POOL_BULLETS_H
#include "Bullet.h"
//#include "Player.h"
#include "Enemy.h"
#include <list>


//------------------------------------------------------------
// Here is a Pool of bullets on std::list
// All bullets are not depend on their "parents"
// And when the number of bullets is more than M_P_S
// Pull will finish creating bullets
//------------------------------------------------------------


namespace bs {

	enum POOL_CONSTANTS {
		MAX_POOL_SIZE = 200
	};


	class PoolBullets
	{
	public:

		PoolBullets								();
		explicit PoolBullets					(std::size_t size);   // attention!!!
		~PoolBullets							();
		void			playerCollision			( Player & hero);
		/*bool isAttacked				(const sf::Vector2f & playerPos, const sf::Vector2f & bulletPos,
									 const float distance);*/
		void			enemyCollision			(Enemy * enemy);
		void			addBullet				(const sf::Vector2f & enPos, const std::string file, const std::string name_, const float speed, const int dir);
		void			Update					(const sf::Int64 time);
		void			draw					(sf::RenderWindow & window);

		std::size_t		getSize					();

	private:
		std::list<Bullet>			listOfBullets;
		std::size_t					size_;
	};
}

#endif POOL_BULLETS_H
