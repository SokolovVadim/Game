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

	sf::Image map_image;
	if (!map_image.loadFromFile("images/map.png"))
	{
		std::cout << "Map was not loaded!" << std::endl;
	}
	sf::Texture map;
	map.loadFromImage(map_image);
	sf::Sprite map_sprite;
	map_sprite.setTexture(map);

	Engine Hero("sheet2.png", HEALTH, 0, 200, 90, 100);




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
			Hero.Dir = 0;
			Hero.Speed = 0.2;
			CurFrame += 0.0052 * time;
			if (CurFrame > 9)
			{
				CurFrame -= 9;
			}
			Hero.sprite.setTextureRect(sf::IntRect(93 * int(CurFrame), 100, 93, 100));
		}



		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			Hero.Dir = 1;
			Hero.Speed = 0.2;
			CurFrame += 0.0052 * time;
			if (CurFrame > 9)
			{
				CurFrame -= 9;
			}
			Hero.sprite.setTextureRect(sf::IntRect(93 * int(CurFrame), 300, 93, 100));
		}

		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			Hero.Dir = 2;
			Hero.Speed = 0.2;
			CurFrame += 0.0052 * time;
			std::cout << "CurFr: " << CurFrame << std::endl;
			if (CurFrame > 9)
			{
			CurFrame -= 9;
			}
			Hero.sprite.setTextureRect(sf::IntRect(93 * int(CurFrame), 0, 93, 100));

		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			Hero.Dir = 3;
			Hero.Speed = 0.2;
			CurFrame += 0.0052 * time;
			std::cout << "CurFr: " << CurFrame << std::endl;
			if (CurFrame > 9)
			{
				CurFrame -= 9;
			}
			Hero.sprite.setTextureRect(sf::IntRect(93 * int(CurFrame), 200, 93, 100));

		}

	

		Hero.Update(time);

		window.clear();

		for (int i(0); i < HEIGHT; ++i)
		{
			for (int j(0); j < WIDTH; ++j)
			{
				if (TileMap[i][j] == ' ')
					map_sprite.setTextureRect(sf::IntRect(0, 0, 48, 64));
				if (TileMap[i][j] == '0')
					map_sprite.setTextureRect(sf::IntRect(48, 0, 48, 64));
				if (TileMap[i][j] == 's')
					map_sprite.setTextureRect(sf::IntRect(96, 0, 48, 64));
				if (TileMap[i][j] == 'w')
					map_sprite.setTextureRect(sf::IntRect(134, 0, 48, 64));

				map_sprite.setPosition(j * 48, i * 64);
				window.draw(map_sprite);
			}
		}

		
		window.draw(Hero.sprite);
		window.display();
	}

	return 0;
}