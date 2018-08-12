#pragma once


#include "Enemy.h"
#include "Map.h"
#include "Player.h"
#include "Bullet.h"



class PoolEnemies
{
public:
	explicit PoolEnemies(const size_t size, const std::string file, std::string name_,
		float x, float y, float w, float h);
	~PoolEnemies();
	void Init(const std::string file, std::string name_, float x, float y, float w, float h);
	void Create(Enemy* enemy, const std::string file, std::string name_,
		float x, float y, float w, float h);
	const size_t GetSize();
	void DrawPool(sf::RenderWindow & window, const sf::Int64 time);
	void PrintPosition();
	void Update(Map & map, sf::Int64 time);
	void isAttackedP(const Player & Hero/*, const int damage*/);
	const sf::Vector2i getSizeEnemies() const;


private:
	static const size_t		MAX_PULL_SIZE = 200;
	size_t					size_;
	Enemy **				m_enemies;
	Enemy *					first_enemy;

	void playerCollision(const Player & Hero, const int pos);
	void bulletCollision(const bs::Bullet & bullet, const int pos);
};
