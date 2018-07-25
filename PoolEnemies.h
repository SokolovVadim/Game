#pragma once

class PoolEnemies
{
public:
	explicit PoolEnemies(const size_t size, const std::string file, std::string name_,
		float x, float y, float w, float h);
	~PoolEnemies();
	void Init(const std::string file, std::string name_, float x, float y, float w, float h);
	void Create(Enemy* enemy, const std::string file, std::string name_, float x, float y, float w, float h);
	size_t GetSize();
	void DrawPool(sf::RenderWindow & window);
private:
	size_t   size_;
	Enemy ** m_enemies;
	Enemy*   first_enemy;
};

PoolEnemies::PoolEnemies(const size_t size, const std::string file, std::string name_,
	float x, float y, float w, float h):
	size_			(size),
	first_enemy		(nullptr)
{
	m_enemies = new Enemy*[size_];
	for (int i(0); i < size_; i++)
	{
		m_enemies[i] = new Enemy(file, name_, x, y + i* 10, w, h);
		fout << "Enemy[" << i << "] has constructed! Y pos = " << 300 + i << std::endl;
	}
}

void PoolEnemies::DrawPool(sf::RenderWindow & window)
{
	for (int i(0); i < size_; i++)
	{
		window.draw(m_enemies[i]->sprite);
	}
}

size_t PoolEnemies::GetSize()
{
	return size_;
}

void PoolEnemies::Create(Enemy* enemy, const std::string file, std::string name_, float x, float y, float w, float h)
{
	Enemy * cur_enemy = new Enemy(file, name_, x, y, w, h);
	enemy->SetNext(cur_enemy);
	cur_enemy->SetNext(nullptr);
	first_enemy = cur_enemy;
	size_++;
}

PoolEnemies::~PoolEnemies()
{
	for (int i(0); i < size_; i++)
	{
		delete[] m_enemies[i];
	}
	delete[] m_enemies;
	size_ = 0;
}

void PoolEnemies::Init(const std::string file, std::string name_, float x, float y, float w, float h)
{
	/*Enemy * cur_enemy = new Enemy(file, name_, x, y, w, h);
	cur_enemy->SetNext(nullptr);
	size_++;*/


	first_enemy = m_enemies[0];
	
	for (int i(0); i < size_ - 1; i++)
	{
		m_enemies[i]->SetNext(m_enemies[i + 1]);
	}

	m_enemies[size_]->SetNext(nullptr);

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