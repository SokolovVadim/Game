#include "PoolEnemies.h"

PoolEnemies::PoolEnemies(const size_t size, const std::string file, std::string name_,
	float x, float y, float w, float h) :
	size_(size),
	PoolAlive_(true),
	first_enemy(nullptr)
{
	if (size_ > MAX_PULL_SIZE)
		size_ = MAX_PULL_SIZE;
	m_enemies = new Enemy*[size_];
	float RandX(0.0f), RandY(0.0f);
	for (int i(0); i < size_; i++)
	{
		RandX = float(100 + rand() % (W - 200));
		RandY = float(100 + rand() % (H - 200));
		if ((RandX > W - 100) || (RandX < 100) || (RandY > H - 100) || (RandY < 100))
		{
			RandX = W / 2;
			RandY = H / 2;
		}
		fout << "RandX = " << RandX << ", Rand Y = " << RandY << std::endl;
		m_enemies[i] = new Enemy(file, name_, RandX, RandY, w, h, i/2.0f);
	}
	Init(file, name_, x, y, w, h);
}

const bool PoolEnemies::isPoolAlive() const
{
	for (int i(0); i < this->size_; ++i)
	{
		if ((m_enemies[i]->isAlive()))
		{
			return true;
		}
	}
	return false;
}

void PoolEnemies::addBullet(bs::PoolBullets & poolBullets, const std::string file,
	const std::string name_, const float speed, const sf::Int64 time, au::Audio & audio)
{
	for (int i(0); i < this->size_; ++i)
	{
		if ((m_enemies[i]->isAlive()) && (m_enemies[i]->isTimeBullet(time)))
		{
			poolBullets.addBullet(m_enemies[i]->getPosition(), file, name_, speed, m_enemies[i]->getDir(), i);
		}
	}
}

void PoolEnemies::Update(Map & map, sf::Int64 time, const Player & Hero)
{
	for (int i(0); i < size_; i++)
	{
		if (m_enemies[i]->isAlive())
		{
			m_enemies[i]->Update(map, time);
			m_enemies[i]->followPlayer(Hero.GetPos());
		}
	}
}

void PoolEnemies::PrintPosition()
{
	for (int i(0); i < size_; i++)
	{
		if (m_enemies[i]->isAlive()) {
			std::cout << "pos [" << i << "] = ( " << m_enemies[i]->Pos.x << ", " << m_enemies[i]->Pos.y << " )" << std::endl;
		}
	}
}

void PoolEnemies::DrawPool(sf::RenderWindow & window, const sf::Int64 time)
{
	for (int i(0); i < size_; i++)
	{
		if ((m_enemies[i]->isAlive()) && (m_enemies[i]->getHP() > 0.0f))
		{
			m_enemies[i]->DisplayDamage(time);
			window.draw(m_enemies[i]->getSprite());
		}
		else
		{
			fout << "m_enemies[i] = nullptr" << std::endl;
		}
	}
}

const size_t PoolEnemies::GetSize()
{
	return size_;
}

void PoolEnemies::Create(Enemy* enemy, const std::string file, std::string name_, float x, float y, float w, float h)
{
	Enemy * cur_enemy = new Enemy(file, name_, x, y, w, h, 0.0f);
	enemy->SetNext(cur_enemy);
	cur_enemy->SetNext(nullptr);
	first_enemy = cur_enemy;
	size_++;
}

PoolEnemies::~PoolEnemies()
{
	fout << "Pool start destructing" << std::endl;
	for (int i(0); i < size_; i++)
	{
		if (m_enemies[i]->isAlive())
			delete m_enemies[i];
	}
	delete[] m_enemies;
	size_ = 0;
}

void PoolEnemies::Init(const std::string file, std::string name_, float x, float y, float w, float h)
{
	first_enemy = m_enemies[0];

	for (int i(0); i < size_ - 1; i++)
	{
		m_enemies[i]->SetNext(m_enemies[i + 1]);
	}

	m_enemies[size_ - 1]->SetNext(nullptr);
}


void PoolEnemies::isAttacked(const Player & Hero/*, const int damage*/)
{
	for (int i(0); i < size_; ++i)
	{
		if (m_enemies[i]->isAlive()) {
			m_enemies[i]->playerCollision(Hero);
		}
	}
}

void PoolEnemies::bulletCollision(bs::PoolBullets & bPool)
{
	for (int i(0); i < size_; i++) 
	{
		if(m_enemies[i]->isAlive())
			bPool.enemyCollision(m_enemies[i], i); // every enemy has special number in Pool. To avoid
		                                           // collision with it's own bullet there is a verification
												   // number of enemy with bullet parent ID
	}
}


const sf::Vector2i PoolEnemies::getSizeEnemies() const
{
	if (m_enemies[0] != nullptr)
		return m_enemies[0]->getSize();
	else
		return sf::Vector2i(0, 0);
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