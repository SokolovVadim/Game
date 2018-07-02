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
};


DragAndDrop::DragAndDrop(sf::RenderWindow & window, bool & IsMove_, float & Dx_, float & Dy_) :
	isMove(IsMove_),
	Dx(Dx_),
	Dy(Dy_),
	PixPos(sf::Mouse::getPosition(window)),
	WindPos(window.mapPixelToCoords(PixPos))
{}

void DragAndDrop::MoveMouse(sf::RenderWindow & window)
{
	fout << "Mouse pixel  coord.x = " << PixPos.x  << " coord.y = " << PixPos.y  << std::endl;
	fout << "Mouse window coord.x = " << WindPos.x << " coord.y = " << WindPos.y << std::endl;
}

void DragAndDrop::MainEffect(sf::Event & event, Actor & Hero)
{
	if ((event.type == sf::Event::MouseButtonPressed) && (event.key.code == sf::Mouse::Left)
		&& (Hero.sprite.getGlobalBounds().contains(WindPos)))
	{
		fout << "Click!" << std::endl;
		Dx = PixPos.x - Hero.sprite.getPosition().x;
		Dy = PixPos.y - Hero.sprite.getPosition().y;

		std::cout << "Dx = " << Dx << " Dy = " << Dy << std::endl;


		isMove = true;
	}
	if ((event.type == sf::Event::MouseButtonReleased) && (event.key.code == sf::Mouse::Left))
	{
		isMove = false;
		Hero.sprite.setColor(sf::Color::White);
	}
}

void DragAndDrop::Action(Actor & Hero)
{
	if (isMove) {
		Hero.sprite.setColor(sf::Color::Cyan);
		Hero.SetCoord(PixPos.x - Dx, PixPos.y - Dy);
	}
}
