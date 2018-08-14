#pragma once
#include "Bullet.h"
#include "Player.h"
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

		PoolBullets					();
		PoolBullets					(std::size_t size);
		~PoolBullets				();
		void playerCollision		(const Player & hero);
		bool isAttacked				(const sf::Vector2f & playerPos, const sf::Vector2f & bulletPos,
									 const float distance);

	private:
		std::list<Bullet>			listOfBullets;
		std::size_t					size_;
	};
}