#pragma once



class DragAndDrop
{
private:
	float			tempX;
	float			tempY;
	float			distance;
	bool			isMove;
	float			Dx;
	float			Dy;
	sf::Vector2i	PixPos;
	sf::Vector2f	WindPos;
public:
	DragAndDrop				(sf::RenderWindow & window);
	void MoveMouse			(sf::RenderWindow & window);
	void MainEffect			(sf::Event & event, Actor & Hero);
	void Action				(Actor & Hero);
	void SetVectors			(sf::RenderWindow & window);
	void Select				(sf::RenderWindow & window, sf::Event & event, Actor & Hero);
	void Rpg				(sf::Event & event, Actor & Hero);
	void MoveSprite			(Actor & Hero, sf::Int64 & time);
	void DropColor			(Actor & Hero, sf::Event & event);
};


DragAndDrop::DragAndDrop(sf::RenderWindow & window) :
	tempX			(0.0f),
	tempY			(0.0f),
	distance		(0.0f),
	isMove			(false),
	Dx				(0.0f),
	Dy				(0.0f),
	PixPos			(sf::Mouse::getPosition(window)),
	WindPos			(window.mapPixelToCoords(PixPos))
{}

void DragAndDrop::DropColor(Actor & Hero, sf::Event & event)
{
	if (event.type == sf::Event::MouseButtonPressed)
		if (event.key.code == sf::Mouse::Left)
			if (Hero.sprite.getGlobalBounds().contains(WindPos))
				if(Hero.GetSelect())
				{
					Hero.sprite.setColor(sf::Color::Red);
					Hero.SetSelect(false);
				}
}

void DragAndDrop::MoveSprite(Actor & Hero, sf::Int64 & time)
{
	if (Hero.GetMove()) {
		distance = sqrt((pow(tempX - Hero.GetCoordX(), 2) + pow(tempY - Hero.GetCoordY(), 2)));
		if (distance > 2.0)
		{
			Hero.IncCoord(0.1*time*(tempX - Hero.GetCoordX()) / distance, 0.1*time*(tempY - Hero.GetCoordY()) / distance);
		}
		else
		{
			Hero.SetMove(false);
			fout << "Arrived!" << std::endl;
		}
	}
}


void DragAndDrop::Select(sf::RenderWindow & window, sf::Event & event, Actor & Hero)
{
	if(event.type == sf::Event::KeyPressed)
		if (event.key.code == sf::Keyboard::C)
			if (Hero.sprite.getGlobalBounds().contains(WindPos))
			{
				Hero.sprite.setColor(sf::Color::Red);
				Hero.SetSelect(true);
			}
}

void DragAndDrop::Rpg(sf::Event & event, Actor & Hero)
{
	if (Hero.GetSelect())
		if (event.type == sf::Event::MouseButtonPressed)
			if (event.key.code == sf::Mouse::Right)
			{
				Hero.SetMove(true);
				Hero.SetSelect(false);
				Hero.sprite.setColor(sf::Color::White);
				tempX = WindPos.x;
				tempY = WindPos.y;
			}
}


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
