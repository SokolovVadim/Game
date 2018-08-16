#include "Entity.h"

Entity::Entity() :
	Heatpoints		(100.0f),
	Pos				(0, 0),
	Speed			(0.0f),
	Width			(0.0f),
	Height			(0.0f),
	Timer			(0),
	Alive			(true),
	IsMove			(false),
	OnGround		(false),
	Image			(sf::Image()),
	Texture			(sf::Texture()),
	Name			(""),
	File			(""),
	dx				(0.0f),
	dy				(0.0f),
	sprite			(sf::Sprite())
{
	std::cout << "Basic constructor of Entity!" << std::endl;
}

Entity::Entity(const std::string file, const std::string name_, float x, float y, float w, float h) :
	Heatpoints(100.0f),
	Pos(x, y),
	Speed(0.0f),
	Width(w),
	Height(h),
	Timer(0),
	Alive(true),
	IsMove(false),
	OnGround(false),
	Image({ sf::Image() }),
	Texture({ sf::Texture() }),
	Name(name_),
	File(file),
	dx(0.0f),
	dy(0.0f),
	sprite({ sf::Sprite() })
{
	Image.loadFromFile("Images/" + File);
	Texture.loadFromImage(Image);
	sprite.setTexture(Texture);
	//sprite.setOrigin(w / 2, h / 2);
}


Entity::~Entity()
{
	std::cout << "Entity has destructed" << std::endl;
}

const bool Entity::isAlive() const
{
	return Alive;
}

void Entity::setRotate(const float value)
{
	sprite.setRotation(value);
}

void Entity::setColor(const sf::Color & color)
{
	sprite.setColor(color);
}

const sf::Vector2f Entity::getPosition()
{
	return sprite.getPosition();
}

void Entity::setOrigin(const float x, const float y)
{
	sprite.setOrigin(x, y);
}

void Entity::setPosition(const float x, const float y)
{
	sprite.setPosition(x, y);
}

const sf::Sprite Entity::getSprite() const
{
	return sprite;
}


void Entity::setTextureRect(const sf::IntRect & rect)
{
	sprite.setTextureRect(rect);
}

void Entity::setTexture(sf::Texture & texture)
{
	sprite.setTexture(texture);
}

void Entity::setScale(const float factorX, const float factorY)
{
	sprite.setScale(factorX, factorY);
}

const bool Entity::getGlobalBounds(const sf::Vector2f & vec) const
{
	return sprite.getGlobalBounds().contains(vec);
}

void Entity::draw(sf::RenderWindow & window)
{
	window.draw(sprite);
}