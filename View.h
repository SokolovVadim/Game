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


//MyView View;
//View.view.reset(sf::FloatRect(XPOS - SETCAMX / 2, YPOS - SETCAMY / 2, SETCAMX, SETCAMY));
//window.create(sf::VideoMode(SETCAMX, SETCAMY), "Game", sf::Style::Fullscreen);


//MyView::MyView():
//	view		(sf::View()),
//	window		({})
//{
//	view.reset		(sf::FloatRect(XPOS - SETCAMX / 2, YPOS - SETCAMY / 2, SETCAMX, SETCAMY));
//	window.create	(sf::VideoMode(SETCAMX, SETCAMY), "Game", sf::Style::Fullscreen);
//}

//sf::View MyView::GetCoordView(float xcoord, float ycoord)
//{
//	float cur_x = xcoord;
//	float cur_y = ycoord;
//
//	if (xcoord < LEFTWALL)
//		cur_x = LEFTWALL;
//	if (ycoord < UPWALL)
//		cur_y = UPWALL;
//	if (xcoord > RIGHTWALL)
//		cur_x = RIGHTWALL;
//	if (ycoord > DOWNWALL)
//		cur_y = DOWNWALL;
//
//
//	view.setCenter(cur_x + MOVEVIEW, cur_y);
//	return view;
//}
//
//sf::View MyView::ScrollMap(sf::Int64 time)
//{
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
//		view.move(-0.1f * time, 0);
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
//		view.move(0.1f * time, 0);
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
//		view.move(0, -0.1f * time);
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
//		view.move(0, 0.1f * time);
//	return view;
//}
//
//
//
//void MyView::ScrollMouse(sf::Window & window, sf::Int64 time, const bool isAlive)
//{
//	sf::Vector2i position = sf::Mouse::getPosition(window);
//
//	//fout << "Mouse position: x = " << position.x << ", y = " << position.y << std::endl;
//	if (isAlive) {
//		if (position.x < 3)
//			view.move(-0.2f * time, 0);
//		if (position.x > int(window.getSize().x - 3))
//			view.move(0.2f * time, 0);
//		if (position.y < 3)
//			view.move(0, -0.2f * time);
//		if (position.y > int(window.getSize().y - 3))
//			view.move(0, 0.2f * time);
//	}
//}