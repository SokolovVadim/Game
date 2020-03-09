#include "DragAndDrop.h"
DragAndDrop::DragAndDrop(sf::RenderWindow & window) :
	tempX(0.0f),
	tempY(0.0f),
	distance(0.0f),
	isMove(false),
	Dx(0.0f),
	Dy(0.0f),
	DeltaX(0.0f),
	DeltaY(0.0f),
	Rotation(0.0f),
	PixPos(sf::Mouse::getPosition(window)),
	WindPos(window.mapPixelToCoords(PixPos))
{}


void DragAndDrop::Rotate(Player & Hero)
{
	DeltaX = WindPos.x - Hero.GetCoordX();
	DeltaY = WindPos.y - Hero.GetCoordY();
	Rotation = (atan2(DeltaX, DeltaY)) * 180.0f / float(3.14/*M_PI*/);
	Hero.setRotate(Rotation);
}



void DragAndDrop::DropColor(Player & Hero, sf::Event & event)
{
	if (event.type == sf::Event::MouseButtonPressed)
		if (event.key.code == sf::Mouse::Left)
			if (Hero.getGlobalBounds(WindPos))
				if (Hero.GetSelect())
				{
					Hero.setColor(sf::Color::Red);
					Hero.SetSelect(false);
				}
}

void DragAndDrop::MoveSprite(Player & Hero, sf::Int64 & time)
{
	if (Hero.GetMove()) {
		distance = sqrt((pow(tempX - Hero.GetCoordX(), 2) + pow(tempY - Hero.GetCoordY(), 2)));
		if (distance > 2.0)
		{
			Hero.IncCoord(0.1f*time*(tempX - Hero.GetCoordX()) / distance, 0.1f*time*(tempY - Hero.GetCoordY()) / distance);
		}
		else
		{
			Hero.SetMove(false);
			fout << "Arrived!" << std::endl;
		}
	}
}


void DragAndDrop::Select(sf::RenderWindow & window, sf::Event & event, Player & Hero)
{
	if (event.type == sf::Event::KeyPressed)
		if (event.key.code == sf::Keyboard::C)
			if (Hero.getGlobalBounds(WindPos))
			{
				Hero.setColor(sf::Color::Red);
				Hero.SetSelect(true);
			}
}

void DragAndDrop::Rpg(sf::Event & event, Player & Hero)
{
	if (Hero.GetSelect())
		if (event.type == sf::Event::MouseButtonPressed)
			if (event.key.code == sf::Mouse::Right)
			{
				Hero.SetMove(true);
				Hero.SetSelect(false);
				Hero.setColor(sf::Color::White);
				tempX = WindPos.x;
				tempY = WindPos.y;
				//Rotate(Hero);  !!!  I banned it cas it didn't work correctly   !!!!!!!!!!!!!!!!!!!!!!!!!!
			}
}


void DragAndDrop::SetVectors(sf::RenderWindow & window)
{
	PixPos = (sf::Mouse::getPosition(window));
	WindPos = (window.mapPixelToCoords(PixPos));
}

void DragAndDrop::MoveMouse(sf::RenderWindow & window)
{
	fout << "Mouse pixel  coord.x = " << PixPos.x << " coord.y = " << PixPos.y << std::endl;
	fout << "Mouse window coord.x = " << WindPos.x << " coord.y = " << WindPos.y << std::endl;
}

void DragAndDrop::MainEffect(sf::Event & event, Player & Hero)
{
	if (event.type == sf::Event::MouseButtonPressed)
		if (event.key.code == sf::Mouse::Left)
			if (Hero.getGlobalBounds(WindPos))
			{
				Dx = WindPos.x - Hero.getPosition().x;
				Dy = WindPos.y - Hero.getPosition().y;
				isMove = true;
			}
	if (event.type == sf::Event::MouseButtonReleased)
		if (event.key.code == sf::Mouse::Left)
		{
			isMove = false;
			Hero.setColor(sf::Color::White);
		}
}

void DragAndDrop::Action(Player & Hero)
{
	if (isMove)
	{
		fout << "Hero: x = " << Hero.GetCoordX() << ", y = " << Hero.GetCoordY() << " Window: x = " << (WindPos.x - Dx) << ", y = " << (WindPos.y - Dy) << std::endl;
		Hero.setColor(sf::Color::Magenta);
		Hero.SetCoord(WindPos.x - Dx, WindPos.y - Dy);
	}
}