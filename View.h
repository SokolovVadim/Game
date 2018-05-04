#pragma once


enum VIEW
{
	MOVEVIEW = 0,
	SETCAMX = 640,
	SETCAMY = 480
};

enum WALLS
{
	LEFTWALL = 320,
	UPWALL = 240,
	RIGHTWALL = W - LEFTWALL,
	DOWNWALL = H - UPWALL
};

class MyView
{
public:
	sf::View view;
	sf::View GetCoordView(float xcoord, float ycoord);
	sf::View ScrollMap(sf::Int64 time);
};


// Set coord if Hero overwalk the wall

sf::View MyView::GetCoordView(float xcoord, float ycoord)
{
	float cur_x = xcoord;
	float cur_y = ycoord;

	if (xcoord < LEFTWALL)
		cur_x = LEFTWALL;
	if (ycoord < UPWALL)
		cur_y = UPWALL;
	if (xcoord > RIGHTWALL)
		cur_x = RIGHTWALL;
	if (ycoord > DOWNWALL)
		cur_y = DOWNWALL;




	view.setCenter(cur_x + MOVEVIEW, cur_y);
	return view;
}

sf::View MyView::ScrollMap(sf::Int64 time)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		view.move(-0.1f*time, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		view.move(0.1f*time, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		view.move(0, -0.1f*time);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		view.move(0, 0.1f*time);
	return view;
}

