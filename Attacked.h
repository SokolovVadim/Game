#pragma once
class Attacked
{
private:

	const float DISTANCE = HEROX; // (enemy + hero)/2

	bool isAttacked;
	bool isNear;

	bool IsNear(Player & player, const float enx, const float eny);

public:
	Attacked();
	~Attacked();
	bool IsAttacked(Player & player, const float enx, const float eny);
};

Attacked::Attacked() :
	isAttacked		(false),
	isNear			(false)
{}

Attacked::~Attacked()
{
	fout << "Attacked class has destructed!" << std::endl;
}

bool Attacked::IsNear(Player & player, const float enx, const float eny)
{
	if (pow(player.GetCoordX() - enx, 2) + pow(player.GetCoordY() - eny, 2) < pow(DISTANCE, 2))
		return true;
	else
		return false;
}

bool Attacked::IsAttacked(Player & player, const float enx, const float eny)
{
	if ((IsNear(player, enx, eny)) && (player.GetHit()))
	{
		return true;
	}
	else
		return false;
}