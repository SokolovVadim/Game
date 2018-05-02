#pragma once


enum VIEW
{
	MOVEVIEW = 0,
	SETCAMX = 640,
	SETCAMY = 480
};

class MyView
{
public:
	sf::View view;
	sf::View GetCoordView(float xcoord, float ycoord);
	sf::View ScrollMap(float time);
};


// Set coord if Hero overwalk the wall

sf::View MyView::GetCoordView(float xcoord, float ycoord)
{
	float cur_x = xcoord;
	float cur_y = ycoord;

	if (xcoord < 320)
		cur_x = 320;
	if (ycoord < 240)
		cur_y = 240;
	if (xcoord > 736)
		cur_x = 736;
	if (ycoord > 464)
		cur_y = 464;




	view.setCenter(cur_x + MOVEVIEW, cur_y);
	return view;
}

sf::View MyView::ScrollMap(float time)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		view.move(-0.1*time, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		view.move(0.1*time, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		view.move(0, -0.1*time);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		view.move(0, 0.1*time);
	return view;
}

