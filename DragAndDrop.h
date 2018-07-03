#pragma once



class DragAndDrop
{
private:
	bool			isMove;
	float			Dx;
	float			Dy;
	sf::Vector2i	PixPos;
	sf::Vector2f	WindPos;
public:
	DragAndDrop				(sf::RenderWindow & window, bool & Ismove_, float & Dx_, float & Dy_);
	void MoveMouse			(sf::RenderWindow & window);
	void MainEffect			(sf::Event & event, Actor & Hero);
	void Action(Actor & Hero);
	void SetVectors(sf::RenderWindow & window);
};


DragAndDrop::DragAndDrop(sf::RenderWindow & window, bool & IsMove_, float & Dx_, float & Dy_) :
	isMove(IsMove_),
	Dx(Dx_),
	Dy(Dy_),
	PixPos(sf::Mouse::getPosition(window)),
	WindPos(window.mapPixelToCoords(PixPos))
{}


void DragAndDrop::SetVectors(sf::RenderWindow & window)
{
	PixPos = (sf::Mouse::getPosition(window));
	WindPos = (window.mapPixelToCoords(PixPos));
}

void DragAndDrop::MoveMouse(sf::RenderWindow & window)
{
	fout << "Mouse pixel  coord.x = " << PixPos.x  << " coord.y = " << PixPos.y  << std::endl;
	fout << "Mouse window coord.x = " << WindPos.x << " coord.y = " << WindPos.y << std::endl;
}

void DragAndDrop::MainEffect(sf::Event & event, Actor & Hero)
{
	if (event.type == sf::Event::MouseButtonPressed)
			if (event.key.code == sf::Mouse::Left)
				if (Hero.sprite.getGlobalBounds().contains(WindPos.x, WindPos.y))
				{
					Dx = WindPos.x - Hero.sprite.getPosition().x;
					Dy = WindPos.y - Hero.sprite.getPosition().y;
					isMove = true;
				}
	if (event.type == sf::Event::MouseButtonReleased)
		if (event.key.code == sf::Mouse::Left)
		{
			isMove = false;
			Hero.sprite.setColor(sf::Color::White);
		}
}

void DragAndDrop::Action(Actor & Hero)
{
	if (isMove)
	{

		fout << "Hero: x = " << Hero.GetCoordX() << ", y = " << Hero.GetCoordY() << " Window: x = " << (WindPos.x - Dx) << ", y = " << (WindPos.y - Dy) << std::endl;
		Hero.sprite.setColor(sf::Color::Magenta);
		Hero.SetCoord(WindPos.x - Dx, WindPos.y - Dy);
	}
}

//while (window.pollEvent(event))
//{
//	if (event.type == sf::Event::Closed)
//		window.close();
//	fulltxt.React(event, window, show_mission_text, View, Hero, Kumach_s);
//	if (event.type == sf::Event::MouseButtonPressed)
//		if (event.key.code == sf::Mouse::Left)
//			if (Hero.sprite.getGlobalBounds().contains(WindPos.x, WindPos.y))
//			{
//				Dx = WindPos.x - Hero.sprite.getPosition().x;
//				Dy = WindPos.y - Hero.sprite.getPosition().y;
//				IsMove = true;
//			}
//	if (event.type == sf::Event::MouseButtonReleased)
//		if (event.key.code == sf::Mouse::Left)
//		{
//			IsMove = false;
//			Hero.sprite.setColor(sf::Color::White);
//		}
//
//	dnd.MainEffect(event, Hero);
//	dnd.MoveMouse(window);
//}
//if (IsMove)
//{
//	Hero.sprite.setColor(sf::Color::Magenta);
//	Hero.SetCoord(WindPos.x - Dx, WindPos.y - Dy);
//}
