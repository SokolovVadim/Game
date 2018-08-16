#pragma once

#include "Entity.h"
#include "Map.h"
#include "Attacked.h"
#include "Player.h"

class Enemy : public Entity
{
public:
	Enemy(const std::string file, std::string name_,
		float x, float y, float w, float h);
	~Enemy();
	void						CheckCollision		(Map & map, float dx_, float dy_);
	void						Update				(Map & map, sf::Int64 time);
	void						SetNext				(Enemy * next_en);
	void						ReduceHP			(/*const int damage*/);
	void						Destruct			();
	void						illustrateDamage	();
	void						SetAttacked			();
	void						DisplayDamage		(const sf::Int64 time);
	void playerCollision(const Player & Hero);
	const sf::Vector2f &    	getCoord			();
	const sf::Vector2i			getSize				() const;
	Enemy *						GetNext				();
	bool						IsAttacked			(const sf::Vector2f & plPos, const float distance);
	const float					getHP				()const;

private:

	enum ENEMY
	{
		W = 64,
		H = 66,
		LEFT = 0,       ///////////////////////////!!!!!!!!!!!!!!!!!!!!!!!! 
		TOP = 5 * H,
		DAMAGE = 30             // from hero on enemy
	};
	const float			enemy_speed = 0.1f;
	bool				isDamageDisplay;
	int					attackedTimer;
	Enemy*				enemy_next;
	Attacked * attack;
};
