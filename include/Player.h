
#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"
#include "Map.h"
#include <sstream>

class Player : public Entity
{

private:

	int				Dir;
	int				PurpleTimer;
	int				FireTimer;
	unsigned int	Score;

	float			Power;
	float			Air;
	float			HitTimer;
	float			BulletTimer;

	bool			IsSelect;
	bool			IsPurple;
	bool			IsOnFire;
	bool			IsHit;
	bool			IsBulletAttacked;
	bool			isDamagedByBullet;

	enum STATUS
	{
		LEFT = 0,
		RIGHT,
		UP,
		DOWN,
		SHIFT
	};

	enum DAMAGE
	{
		BULLET_DAMAGE = 10
	};


public:

	const float		n_speed = 0.2f;

	Player								(const std::string file,
										 const std::string name,
										 float x, float y,
										 float w, float h);
	~Player();
	bool			Update				(sf::Int64 time, Map & map);
	bool			GetAlive			();
	bool			SetPower			(sf::Int64 time);
	bool			GetSelect			();
	bool			GetMove				();
	bool			GetHit				()const;
	bool			isBulletAttack		(const sf::Vector2f & bullPos, const float distance);
	bool			GetTimer			() const;
	float			GetCoordX			() const;
	float			GetCoordY			() const;
	float			GetSpeed			() const;
	float			GetPower			() const;
	void			SetDir				(int dir);
	void			SetSpeed			(float speed);
	void			InterractMap		(sf::Int64 time, Map & map);
	void			SetHP				(std::ostringstream & HeatPoints);
	void			PushScore			(std::ostringstream & ScoreString);
	void			GetAir				(std::ostringstream & ScoreAir);
	void			PushPower			(std::ostringstream & Power_str);
	void			IncreasePower		(sf::Int64 time);
	void			SetCoord			(const float x, const float y);
	void			SetSelect			(bool value);
	void			SetMove				(bool value);
	void			IncCoord			(const float x, const float y);
	void			PurpleStyle			(sf::Int64 & time);
	void			OnFire				(sf::Int64 & time);
	void			SetPurple			();
	void			SetRed				();
	void			SetHit				();
	void			Hit					(sf::Int64 & time, int Y);
	void			setBulletAttacked	();
	void			underFire			(const sf::Int64 & time);
	unsigned int	GetScore			();
	int				GetDir				() const;

	const sf::Vector2f & GetPos()const;
};

#endif PLAYER_H
