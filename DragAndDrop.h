#pragma once

#include "Player.h"

class DragAndDrop
{
private:
	float			tempX;
	float			tempY;
	float			distance;
	bool			isMove;

	float			Dx;
	float			Dy;
	float			DeltaX;
	float			DeltaY;
	float			Rotation;

	sf::Vector2i	PixPos;
	sf::Vector2f	WindPos;
public:
	DragAndDrop				(sf::RenderWindow & window);
	void MoveMouse			(sf::RenderWindow & window);
	void MainEffect			(sf::Event & event, Player & Hero);
	void Action				(Player & Hero);
	void SetVectors			(sf::RenderWindow & window);
	void Select				(sf::RenderWindow & window, sf::Event & event, Player & Hero);
	void Rpg				(sf::Event & event, Player & Hero);
	void MoveSprite			(Player & Hero, sf::Int64 & time);
	void DropColor			(Player & Hero, sf::Event & event);
	void Rotate				(Player & Hero);
};
