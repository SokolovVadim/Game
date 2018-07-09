#pragma once

class Enemy : public Entity
{
private:
	enum ENTITY
	{
		W = 64,
		H = 66,
		LEFT = 0,       ///////////////////////////!!!!!!!!!!!!!!!!!!!!!!!! 
		TOP = 5 * H 
	};
	const float enemy_speed = 0.1f;
public: 
	Enemy(sf::Image & image_, std::string name_, float x, float y, float w, float h);
};

Enemy::Enemy(sf::Image & image_, std::string name_, float x, float y, float w, float h) :
	Entity(image_, name_, x, y, w, h)
{
	if (name_ == "Archer1") {
		dx = enemy_speed;
		sprite.setTextureRect(sf::IntRect(LEFT, TOP, W, H));
	}
}