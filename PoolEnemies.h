#pragma once


#include "Enemy.h"
#include "Map.h"
#include "Player.h"
#include "PoolBullets.h"
#include "Audio.h"



class PoolEnemies
{
public:
	explicit PoolEnemies				(	const size_t size,
											const std::string file,
											std::string name_,
											float x, float y,
											float w, float h);
	~PoolEnemies						();
	void				Init			(	const std::string file,
											std::string name_,
											float x, float y,
											float w, float h);
	void				Create			(	Enemy* enemy,
											const std::string file,
											std::string name_,
											float x, float y,
											float w, float h);
	const size_t		GetSize			();
	void				DrawPool		(sf::RenderWindow & window, const sf::Int64 time);
	void				PrintPosition	();
	void				Update			(Map & map, sf::Int64 time, const Player & Hero);
	void				isAttacked		(const Player & Hero/*, const int damage*/);
	void				addBullet		(bs::PoolBullets & poolBullets, const std::string file,
										 const std::string name_, const float speed,
										 const sf::Int64 time, au::Audio & audio);
	void				bulletCollision	(bs::PoolBullets & bPool);
	const sf::Vector2i	getSizeEnemies	() const;
	const bool			isPoolAlive		() const;


private:
	static const size_t		MAX_PULL_SIZE = 200;
	size_t					size_;
	bool					PoolAlive_;
	Enemy **				m_enemies;
	Enemy *					first_enemy;

	//void playerCollision(const Player & Hero, const int pos);
};
