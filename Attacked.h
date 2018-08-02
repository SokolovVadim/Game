#pragma once
class Attacked
{
private:

	const float DISTANCE = HEROX; // (enemy + hero)/2

	bool isAttacked;
	bool isNear;

	bool IsNear(const sf::Vector2f & plPos, const sf::Vector2f & enPos);

public:
	Attacked();
	~Attacked();
	bool IsAttacked(const sf::Vector2f & plPos, const sf::Vector2f & enPos);
};

Attacked::Attacked() :
	isAttacked		(false),
	isNear			(false)
{}

Attacked::~Attacked()
{
	fout << "Attacked class has destructed!" << std::endl;
}

bool Attacked::IsNear(const sf::Vector2f & plPos, const sf::Vector2f & enPos)
{
	if (pow(plPos.x - enPos.x, 2) + pow(plPos.y - enPos.y, 2) < pow(DISTANCE, 2))
		return true;
	else
		return false;
}

bool Attacked::IsAttacked(const sf::Vector2f & plPos, const sf::Vector2f & enPos)
{
	if (IsNear(plPos, enPos))
	{
		return true;
	}
	else
		return false;
}

