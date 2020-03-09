#pragma once


#include "Components.h"
#include "Constants.h"

enum VIEW
{
	MOVEVIEW = 0,
	SETCAMX = 720,
	SETCAMY = 480,
	TEXTX = SETCAMX / 2 - 10,
	TEXTY = SETCAMY / 2 - 10,
};

enum WALLS
{
	LEFTWALL = SETCAMX / 2,
	UPWALL = SETCAMY / 2,
	RIGHTWALL = W - LEFTWALL,
	DOWNWALL = H - UPWALL
};

class MyView
{
public:
	sf::View view;
	sf::RenderWindow		window;

	//MyView();
	sf::View GetCoordView(float xcoord, float ycoord);
	sf::View ScrollMap(sf::Int64 time);
	void ScrollMouse(sf::Window & window, sf::Int64 time, const bool isAlive);

};
