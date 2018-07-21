#pragma once


class Entity
{

public:

	float			Heatpoints;
	sf::Vector2f	Pos;

	float			Speed;
	float			Width;
	float			Height;
	sf::Int64		Timer;

	bool			Alive;
	bool			IsMove;
	bool			OnGround;

	sf::Image		Image;
	sf::Texture		Texture;
	
	std::string		Name;
	std::string		File;


	float			dx;
	float			dy;

	sf::Sprite		sprite;

	Entity	(const std::string file, const std::string name_, float x, float y, float w, float h);
	~Entity	();
};

Entity::Entity(const std::string file, const std::string name_, float x, float y, float w, float h) :
	Heatpoints			(100.0f),
	Pos					(x, y),
	Speed				(0.0f),
	Width				(w),
	Height				(h),
	Timer				(0),
	Alive				(true),
	IsMove				(false),
	OnGround			(false),
	Image				({sf::Image()}),
	Texture				({sf::Texture()}),
	Name				(name_),
	File(file),
	dx					(0.0f),
	dy					(0.0f),
	sprite				({sf::Sprite()})
{
	Image.loadFromFile("Images/" + File);
	Texture.loadFromImage(Image);
	sprite.setTexture(Texture);
	//sprite.setOrigin(w / 2, h / 2);
}


Entity::~Entity()
{
	fout << "Entity has destructed" << std::endl;
}
