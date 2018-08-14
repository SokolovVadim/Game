#include "Attacked.h"


Attacked::Attacked() :
	isAttacked			(false),
	isNear				(false)
{} 

Attacked::~Attacked()
{
	std::cout << "Attacked class has destructed!" << std::endl;
}


const bool Attacked::getAttackedValue() const
{
	return isAttacked;
}

void Attacked::SetAttacked(const bool isAtt)
{
	isAttacked = isAtt;
}

bool Attacked::IsNear(const sf::Vector2f & plPos, const sf::Vector2f & enPos,
	const float distance)
{
	if (pow(plPos.x - enPos.x, 2) + pow(plPos.y - enPos.y, 2) < pow(distance, 2))
	{
		isNear = true;
		return true;
	}
	else
		return false;
}

bool Attacked::IsAttacked(const sf::Vector2f & plPos, const sf::Vector2f & enPos, const float distance)
{
	if (IsNear(plPos, enPos, distance))
	{
		isAttacked = true;
		return true;
	}
	else
		return false;
}