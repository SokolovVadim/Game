#pragma once
class Entity
{

public:

	float			Heatpoints;
	sf::Vector2f	pos;

	float			Speed;
	float			Width;
	float			Height;
	sf::Int64		Timer;

	bool			Alive;
	bool			IsMove;
	bool			OnGround;

	//sf::Image		Image;
	sf::Texture		Texture;
	
	std::string		Name;


	float			dx;
	float			dy;

	sf::Sprite		sprite;

	Entity(sf::Image & image, std::string name_, float x, float y, float w, float h);
	~Entity();
};


Entity::~Entity()
{
	fout << "Entity has destructed" << std::endl;
}
Entity::Entity(sf::Image & image, std::string name_, float x, float y, float w, float h) :
	Heatpoints			(100.0f),
	pos(x, y),
	Speed				(0.0f),
	Width				(w),
	Height				(h),
	Timer				(0),
	Alive				(true),
	IsMove				(false),
	OnGround			(false),
	Texture				({sf::Texture()}),
	Name				(name_),
	dx					(0.0f),
	dy					(0.0f),
	sprite				({sf::Sprite()})
{
	Texture.loadFromImage(image);
	sprite.setTexture(Texture);
	sprite.setOrigin(w / 2, h / 2);
}


class Player: public Entity
{

private:

	unsigned int	Score;

	float			Power;
	float			Air;

	enum STATUS
	{
		LEFT,
		RIGHT,
		UP,
		DOWN,
		SHIFT,
		JUMP,
		STAY
	};

	STATUS Status;

public:

	const float		n_speed = 0.2f;
	const float		j_speed = -0.4f;


	Player(sf::Image & image_, std::string name_, float x, float y, float w, float h);
	~Player();
	bool			Update		(sf::Int64 & time, Map & map, MyView & View);
	bool			GetAlive	();
	float			GetCoordX	() const;
	float			GetCoordY	() const;
	void			SetSpeed	(float speed);
	unsigned int	GetScore	();
	void ActionSwitch			(/*double & CurFrame,*/ sf::Int64 & time/*, sf::RenderWindow & window, MyView & View*/);
	void ChooseAction			(Player::STATUS dir/*, double & CurFrame*/, sf::Int64 time/*, int X, int Y*/);
	void CheckCollision			(Map & map, float dx_, float dy_);
};


Player::Player(sf::Image & image_, std::string name_, float x, float y, float w, float h):
	Entity(image_, name_, x, y, w, h),
	Score(0),
	Power(0.0f),
	Air(0.0f),
	Status(STAY)
{
	if (name_ == "Player1")
		sprite.setTextureRect(sf::IntRect(0, SETBEGIN, HEROX, HEROY));
}