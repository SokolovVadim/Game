#pragma once

class PoolEnemies
{
public:
	explicit PoolEnemies	(const size_t size, const std::string file, std::string name_,
		float x, float y, float w, float h);
	~PoolEnemies			();
	void Init				(const std::string file, std::string name_, float x, float y, float w, float h);
	void Create				(Enemy* enemy, const std::string file, std::string name_,
		float x, float y, float w, float h);
	const size_t GetSize	();
	void DrawPool			(sf::RenderWindow & window);
	void PrintPosition		();
	void Update				(Map & map, sf::Int64 time);
	void isAttacked			(const Player & Hero);
private:
	static const size_t		MAX_PULL_SIZE = 200;
	size_t					size_;
	Enemy **				m_enemies;
	Enemy *					first_enemy;
};

PoolEnemies::PoolEnemies(const size_t size, const std::string file, std::string name_,
	float x, float y, float w, float h):
	size_			(size),
	first_enemy		(nullptr)
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
		m_enemies[i] = new Enemy(file, name_, RandX, RandY, w, h);
	}
	Init(file, name_, x, y, w, h);
}

void PoolEnemies::Update(Map & map, sf::Int64 time)
{
	for (int i(0); i < size_; i++)
	{
		if(m_enemies[i]->isAlive())
			m_enemies[i]->Update(map, time);
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

void PoolEnemies::DrawPool(sf::RenderWindow & window)
{
	for (int i(0); i < size_; i++)
	{
		if((m_enemies[i]->isAlive()) && (m_enemies[i]->getHP() > 0.0f))
			window.draw(m_enemies[i]->sprite);
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
	Enemy * cur_enemy = new Enemy(file, name_, x, y, w, h);
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


void PoolEnemies::isAttacked(/*Attacked & attack,*/ const Player & Hero)
{
	for (int i(0); i < size_; ++i)
	{
		if (m_enemies[i]->isAlive()) {
			if ((m_enemies[i]->IsAttacked(Hero.GetPos())) && (Hero.GetHit()) && (Hero.GetTimer()))
			{
				m_enemies[i]->ReduceHP();
			}
		}
		//attack.IsAttacked(Hero.GetPos(), m_enemies[i]->getCoord());
	}
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