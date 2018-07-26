#include <string>
//#include <iostream>
#include "PoolEnemies.h"
#include "Enemy.h"
PoolEnemies::PoolEnemies(size_t size, const std::string file, std::string name_, float x, float y, float w, float h)
{
	m_enemies = new Enemy*[size];
	for (int i(0); i < size; i++)
	{
		m_enemies[i] = new Enemy(file, name_, x, y, w, h);
	}
}