#pragma once
class Entity
{

private:

	float			Heatpoints;
	float			Xcoord;
	float			Ycoord;

	float			Speed;
	float			Width;
	float			Height;
	float			Timer;

	bool			Alive;
	bool			IsMove;
	bool			OnGround;

	//sf::Image		Image;
	sf::Texture		Texture;
	
	std::string		Name;

public:
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
	Heatpoints			(100),
	Xcoord				(x),
	Ycoord				(y),
	Speed				(0),
	Width				(w),
	Height				(h),
	Timer				(0),
	Alive				(true),
	IsMove				(false),
	OnGround			(false),
	Name				(name_),
	dx					(0),
	dy					(0)
{
	Texture.loadFromImage(image);
	sprite.setTexture(Texture);
	sprite.setOrigin(w / 2, h / 2);
}