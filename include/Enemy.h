#pragma once
#ifndef ENEMY_H
#define ENEMY_H



#include "Entity.h"
#include "Map.h"
#include "Attacked.h"
#include "Player.h"
//#include "PoolBullets.h"


class Enemy : public Entity
{
public:
	explicit Enemy();
	Enemy(const std::string file, std::string name_,
		float x, float y, float w, float h, float startTimer);
	~Enemy();
	void						CheckCollision			(Map & map, float dx_, float dy_);
	void						Update					(Map & map, sf::Int64 time);
	void						SetNext					(Enemy * next_en);
	void						ReduceHP				(/*const int damage*/);
	void						Destruct				();
	void						illustrateDamage		();
	void						SetAttacked				();
	void						DisplayDamage			(const sf::Int64 time);
	void						playerCollision			(const Player & Hero);
	void						addBullet				(const sf::Int64 & time);
	void						generateDir				(const sf::Int64 & time);
	void						followPlayer			(const sf::Vector2f & plPos);
	const sf::Vector2f &    	getCoord				();
	const sf::Vector2i			getSize					() const;
	Enemy *						GetNext					();
	bool						IsAttacked				(const sf::Vector2f & plPos, const float distance);
	bool						isTimeBullet			(const sf::Int64 time);
	const float					getHP					() const;
	const int					getDir					() const;

private:

	const float					createBulletTimeValue	();
	void						checkPos				();

	int direction;

	enum ENEMY
	{
		W = 64,
		H = 66,
		LEFT = 0,       ///////////////////////////!!!!!!!!!!!!!!!!!!!!!!!! 
		TOP = 5 * H,
		DAMAGE = 30,             // from hero on enemy
		BULLET_TIMER_DENOMINATOR = 5
	};

	enum STATUS
	{
		LEFT_DIR,
		RIGHT_DIR,
		UP_DIR,
		DOWN_DIR,
		SHIFT
	};

	const float			enemy_speed = 0.1f;
	float				bulletTimer;
	float				dirTimer;
	bool				isDamageDisplay;
	int					attackedTimer;
	Enemy*				enemy_next;
	Attacked * attack;
};

#endif // !ENEMY_H
