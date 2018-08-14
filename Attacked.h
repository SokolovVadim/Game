#pragma once


#include "Components.h"


#include "Constants.h"

class Attacked
{
private:

	const float DISTANCE = HEROX; // (enemy + hero)/2

	bool	isAttacked;
	bool	isNear;

	bool	IsNear					(const sf::Vector2f & plPos,
		const sf::Vector2f & enPos, const float distance);

public:
	Attacked();
	~Attacked();
	bool		IsAttacked				(const sf::Vector2f & plPos,
		const sf::Vector2f & enPos, const float distance);
	const bool	getAttackedValue		() const;
	void		SetAttacked				(const bool isAtt);

};


//Attacked::Attacked() :
//	isAttacked(false),
//	isNear(false)
//{}
//
//Attacked::~Attacked()
//{
//	std::cout << "Attacked class has destructed!" << std::endl;
//}
//
//
//const bool Attacked::getAttackedValue() const
//{
//	return isAttacked;
//}
//
//void Attacked::SetAttacked(const bool isAtt)
//{
//	isAttacked = isAtt;
//}
//
//bool Attacked::IsNear(const sf::Vector2f & plPos, const sf::Vector2f & enPos)
//{
//	if (pow(plPos.x - enPos.x, 2) + pow(plPos.y - enPos.y, 2) < pow(DISTANCE, 2))
//	{
//		isNear = true;
//		return true;
//	}
//	else
//		return false;
//}
//
//bool Attacked::IsAttacked(const sf::Vector2f & plPos, const sf::Vector2f & enPos)
//{
//	if (IsNear(plPos, enPos))
//	{
//		isAttacked = true;
//		return true;
//	}
//	else
//		return false;
//}



