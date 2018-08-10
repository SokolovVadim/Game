#include "Bullet.h"

namespace bulletStuff {

	Bullet::Bullet(const std::string file, const std::string name_, float x, float y, float w, float h, int dir) :
		Entity(file, name_, x, y, w, h),
		direction(dir)
	{
		Speed = bulletSpeed;
	}


	void Bullet::Update(const float time)
	{
		switch (direction)
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

		if (Pos.x <= 10) ///     CONSTANTS SHOULD BE ADDED IN COMPONENTS
			Pos.x = 10;
		if (Pos.y <= 10) //    REPEATABLE CODE!!!!!!!!!!!!!!!!!!!!!!
			Pos.y = 10;

		


		// Add cicle to find all hitted enemies
		// Add interraction with map


		// decide to use special manager class or functions in the Bullet namespace



		setPosition(Pos.x, Pos.y);

	}

}