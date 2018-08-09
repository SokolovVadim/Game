#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include "Components.h"
#include "Constants.h"

extern std::ofstream fout;


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

	//	sf::Sprite		sprite;

	Entity(const std::string file, const std::string name_, float x, float y, float w, float h);
	~Entity();
	void				setRotate(const float value);
	void				setColor(const sf::Color & color);
	void				setOrigin(const float x, const float y);
	void				setPosition(const float x, const float y);
	void				setTextureRect(const sf::IntRect & rect);
	void				setTexture(sf::Texture & texture);
	void				setScale(const float factorX, const float factorY);
	void				draw(sf::RenderWindow & window);
	const sf::Vector2f	getPosition();
	const sf::Sprite	getSprite() const;
	const bool			getGlobalBounds(const sf::Vector2f & vec) const;

private:
	sf::Sprite		sprite;
};

//Entity::Entity(const std::string file, const std::string name_, float x, float y, float w, float h) :
//	Heatpoints(100.0f),
//	Pos(x, y),
//	Speed(0.0f),
//	Width(w),
//	Height(h),
//	Timer(0),
//	Alive(true),
//	IsMove(false),
//	OnGround(false),
//	Image({ sf::Image() }),
//	Texture({ sf::Texture() }),
//	Name(name_),
//	File(file),
//	dx(0.0f),
//	dy(0.0f),
//	sprite({ sf::Sprite() })
//{
//	Image.loadFromFile("Images/" + File);
//	Texture.loadFromImage(Image);
//	sprite.setTexture(Texture);
//	//sprite.setOrigin(w / 2, h / 2);
//}
//
//
//Entity::~Entity()
//{
//	fout << "Entity has destructed" << std::endl;
//}
//
//void Entity::setRotate(const float value)
//{
//	sprite.setRotation(value);
//}
//
//void Entity::setColor(const sf::Color & color)
//{
//	sprite.setColor(color);
//}
//
//const sf::Vector2f Entity::getPosition()
//{
//	return sprite.getPosition();
//}
//
//void Entity::setOrigin(const float x, const float y)
//{
//	sprite.setOrigin(x, y);
//}
//
//void Entity::setPosition(const float x, const float y)
//{
//	sprite.setPosition(x, y);
//}
//
//const sf::Sprite Entity::getSprite() const
//{
//	return sprite;
//}
//
//
//void Entity::setTextureRect(const sf::IntRect & rect)
//{
//	sprite.setTextureRect(rect);
//}
//
//void Entity::setTexture(sf::Texture & texture)
//{
//	sprite.setTexture(texture);
//}
//
//void Entity::setScale(const float factorX, const float factorY)
//{
//	sprite.setScale(factorX, factorY);
//}
//
//const bool Entity::getGlobalBounds(const sf::Vector2f & vec) const
//{
//	return sprite.getGlobalBounds().contains(vec);
//}
//
//void Entity::draw(sf::RenderWindow & window)
//{
//	window.draw(sprite);
//}


#endif ENTITY_H