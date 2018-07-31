#pragma once
class Attacked
{
private:

	const float DISTANSE = HEROX; // (enemy + hero)/2

	bool isAttacked;
	bool isNear;

	bool IsNear(Player & player, Enemy & enemy);

public:
	Attacked();
	~Attacked();
	bool IsAttacked(Player & player, Enemy & enemy);
};

Attacked::Attacked() :
	isAttacked(false),
	isNear(false)
{}

Attacked::~Attacked()
{
	fout << "Attacked class has destructed!" << std::endl;
}

bool Attacked::IsNear(Player & player, Enemy & enemy)
{
	if (pow(player.GetCoordX() - enemy.getCoord().x, 2) + pow(player.GetCoordY() - enemy.getCoord().y, 2) < DISTANSE)
		return true;
	else
		return false;
}

bool Attacked::IsAttacked(Player & player, Enemy & enemy)
{
	if ((IsNear(player, enemy)) && (player.GetHit()))
	{
		return true;
	}
	else
		return false;
}