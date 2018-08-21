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
										 const sf::Vector2f & enPos,
										 const float distance);
	const bool	getAttackedValue		() const;
	void		SetAttacked				(const bool isAtt);

};
