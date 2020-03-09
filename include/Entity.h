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
	Entity();
	Entity		(const std::string file, const std::string name_,
							 float x, float y, float w, float h);
	~Entity();
	void				setRotate		(const float value);
	void				setColor		(const sf::Color & color);
	void				setOrigin		(const float x, const float y);
	void				setPosition		(const float x, const float y);
	void				setTextureRect	(const sf::IntRect & rect);
	void				setTexture		(sf::Texture & texture);
	void				setScale		(const float factorX, const float factorY);
	void virtual		draw			(sf::RenderWindow & window);
	const sf::Vector2f	getPosition		();
	const sf::Sprite	getSprite		() const;
	const bool			getGlobalBounds	(const sf::Vector2f & vec) const;
	const bool			isAlive			() const;

private:
	sf::Sprite		sprite;
};



#endif ENTITY_H