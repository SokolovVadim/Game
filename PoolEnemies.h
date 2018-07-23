#pragma once

class PoolEnemies
{
public:
	explicit PoolEnemies(size_t size, const std::string file
		, std::string name_, float x, float y, float w, float h);
	~PoolEnemies();

private:
	size_t size_;
	Enemy ** m_enemies;
	Enemy* first_enemy;
};

PoolEnemies::PoolEnemies(size_t size, const std::string file,
	std::string name_, float x, float y, float w, float h):
	size_(size),
	first_enemy(nullptr)
{
	m_enemies = new Enemy*[size_];
	for (int i(0); i < size_; i++)
	{
		m_enemies[i] = new Enemy(file, name_, x, y, w, h);
	}
}

PoolEnemies::~PoolEnemies()
{
	for (int i(0); i < size_; i++)
	{
		delete[] m_enemies[i];
	}
	delete[] m_enemies; 
}


//class PoolEnemies
//{
//public:
//	explicit PoolEnemies(const std::string file, std::string name_, float x, float y, float w, float h) :
//		m_enemies(10, Enemy(file, name_, x, y, w, h))
//	{};
//
//private:
//	std::vector<Enemy> m_enemies;
//};