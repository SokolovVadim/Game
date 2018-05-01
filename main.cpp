#include "Game.h"




void PlayKotik()
{
	PlaySoundA("laba.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	//PlaySoundA("vapa.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}







int main()
{

	PlayKotik();

	sf::RenderWindow window(sf::VideoMode(1080, 720), "OSM");
	
	//sf::Image heroimage;
	sf::Image fleximage;
	//heroimage.loadFromFile("Images/osm1.png");
	fleximage.loadFromFile("Images/sheet2.png");

	sf::Texture flextexture;
	//sf::Texture herotexture;
	/*if (!herotexture.loadFromImage(heroimage))
	{
		std::cout << "Loading from image failed!" << std::endl;
	}*/
	if (!flextexture.loadFromImage(fleximage))
	{
		std::cout << "Loading from image failed!" << std::endl;
	}
	

	



	


	//sf::Sprite herosprite;

	//herosprite.setTexture(herotexture);
	//herosprite.setTextureRect(sf::IntRect(0, 0, 400, 234));
	
	//herosprite.setPosition(sf::Vector2f(50, 50));

	sf::Sprite flexsprite;
	flexsprite.setTexture(flextexture);
	flexsprite.setTextureRect(sf::IntRect(0, 200, 90, 100));
	flexsprite.setPosition(sf::Vector2f(POSITIONX, POSITIONY));
	


	sf::Vector2f VLeft	(float(-0.1),  float( 0.0 ));
	sf::Vector2f VRight	(float(0.1),   float( 0.0 ));
	sf::Vector2f VUp	(float(0),	   float( -0.1));
	sf::Vector2f VDown	(float(0),	   float( 0.1 ));
	double CurFrame(0.0);
	sf::Clock clock;
	while (window.isOpen())
	{
		
		sf::Int64 time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time /= 800;

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}


		/*VLeft.x *= time;
		VLeft.y *= time;
		VRight.x *= time;
		VRight.y *= time;
		VUp.x *= time;
		VUp.y *= time;
		VDown.x *= time;
		VDown.y *= time;*/


		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			CurFrame += 0.0052 * time;
			std::cout << "CurFr: " << CurFrame << std::endl;
			if (CurFrame > 9)
			{
				CurFrame = 0;
			}
			flexsprite.setTextureRect(sf::IntRect(93 * int(CurFrame), 100, 93, 100));
			flexsprite.move(SPEED(-1), 0);
			
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			CurFrame += 0.0052 * time;
			std::cout << "CurFr: " << CurFrame << std::endl;
			if (CurFrame > 9)
			{
				CurFrame -= 9;
			}
			flexsprite.setTextureRect(sf::IntRect(93 * int(CurFrame), 300, 93, 100));
			flexsprite.move(SPEED(1), 0);

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			CurFrame += 0.0052 * time;
			std::cout << "CurFr: " << CurFrame << std::endl;
			if (CurFrame > 9)
			{
				CurFrame -= 9;
			}
			flexsprite.setTextureRect(sf::IntRect(93 * int(CurFrame), 0, 93, 100));
			flexsprite.move(0, SPEED(-1));

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			CurFrame += 0.0052 * time;
			std::cout << "CurFr: " << CurFrame << std::endl;
			if (CurFrame > 9)
			{
				CurFrame -= 9;
			}
			flexsprite.setTextureRect(sf::IntRect(93 * int(CurFrame), 200, 93, 100));
			flexsprite.move(0, SPEED(1));

		}
		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))	{ flexsprite.move(SPEED(1), 0); flexsprite.setTextureRect(sf::IntRect(90,  300, 90, 100));}
		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))		{ flexsprite.move(0, SPEED(-1));    flexsprite.setTextureRect(sf::IntRect(90, 0, 90, 100));}
		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))		{ flexsprite.move(0, SPEED(1));  flexsprite.setTextureRect(sf::IntRect(0,   200, 90, 100));}


		window.clear();
		//window.draw(herosprite);
		window.draw(flexsprite);
		window.display();
	}

	return 0;
}