#pragma once

#include "Entity.h"



namespace bulletStuff {



	class Bullet : public Entity
	{
	public:

		Bullet(const std::string file, const std::string name_, float x, float y, float w, float h, int dir);

		void Update(const float time);

	private:

		int direction;
		const float bulletSpeed = 0.9f;
	};


	//Bullet::Bullet(const std::string file, const std::string name_, float x, float y, float w, float h, int dir) :
	//	Entity(file, name_, x, y, w, h),
	//	direction(dir)
	//{
	//	Speed = bulletSpeed;
	//}


	//void Bullet::Update(const float time)
	//{
	//	switch (direction)
	//	{
	//	case 0: {
	//		dx = -Speed, dy = 0;
	//		break;
	//	}
	//	case 1: {
	//		dx = Speed, dy = 0;
	//		break;
	//	}
	//	case 2: {
	//		dx = 0, dy = -Speed;
	//		break;
	//	}
	//	case 3: {
	//		dx = 0, dy = Speed;
	//		break;
	//	}
	//	case 4: {
	//		dx = Speed, dy = -Speed;
	//		//dx = 0, dy = 0;
	//	}
	//	default: {
	//		dx = 0; dy = 0;
	//	}
	//	};
	//}

	/*class EnemyBullet :public Bullet
	{
	};*/

}