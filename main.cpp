#include "Game.h"




void PlayKotik()
{
	PlaySoundA("Music/laba.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	PlaySoundA("Music/vapa.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	PlaySoundA("Music/hentai.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}


int main()
{

	//PlayKotik();

	sf::RenderWindow window(sf::VideoMode(W, H), "OSM");

	MyView View;
	

	View.view.reset(sf::FloatRect(XPOS - SETCAMX/2, YPOS - SETCAMY/2, SETCAMX, SETCAMY));



	sf::Image map_image;
	if (!map_image.loadFromFile("images/map.png"))
	{
		std::cout << "Map was not loaded!" << std::endl;
	}
	sf::Texture map;
	map.loadFromImage(map_image);
	sf::Sprite map_sprite;
	map_sprite.setTexture(map);

	Engine Hero("sheet2.png", HEALTH, 0, SETBEGIN, HEROX, HEROY);




	/*sf::Vector2f VLeft	(float(-0.1),  float( 0.0 ));
	sf::Vector2f VRight	(float(0.1),   float( 0.0 ));
	sf::Vector2f VUp	(float(0),	   float( -0.1));
	sf::Vector2f VDown	(float(0),	   float( 0.1 ));*/


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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			Hero.SetDir(0);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
				Hero.SetSpeed(Hero.n_speed * 2);
			else
				Hero.SetSpeed(Hero.n_speed);
			CurFrame += 0.0052 * time;
			if (CurFrame > 9)
			{
				CurFrame -= 9;
			}
			Hero.sprite.setTextureRect(sf::IntRect(HEROX * int(CurFrame), HEROY, HEROX, HEROY));
			View.GetCoordView(Hero.GetCoordX(), Hero.GetCoordY());
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			Hero.SetDir(1);
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
				Hero.SetSpeed(Hero.n_speed * 2);
			else
				Hero.SetSpeed(Hero.n_speed);
			CurFrame += 0.0052 * time;
			if (CurFrame > 9)
			{
				CurFrame -= 9;
			}
			Hero.sprite.setTextureRect(sf::IntRect(HEROX * int(CurFrame), 3 * HEROY, HEROX, HEROY));
			View.GetCoordView(Hero.GetCoordX(), Hero.GetCoordY());
		}	
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			Hero.SetDir(2);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
				Hero.SetSpeed(Hero.n_speed * 2);
			else
				Hero.SetSpeed(Hero.n_speed);
			CurFrame += 0.0052 * time;
			std::cout << "CurFr: " << CurFrame << std::endl;
			if (CurFrame > 9)
			{
			CurFrame -= 9;
			}
			Hero.sprite.setTextureRect(sf::IntRect(93 * int(CurFrame), 0, HEROX, HEROY));
			View.GetCoordView(Hero.GetCoordX(), Hero.GetCoordY());
		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			Hero.SetDir(3);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
				Hero.SetSpeed(Hero.n_speed * 2);
			else
				Hero.SetSpeed(Hero.n_speed);
			CurFrame += 0.0052 * time;
			std::cout << "CurFr: " << CurFrame << std::endl;
			if (CurFrame > 9)
			{
				CurFrame -= 9;
			}
			Hero.sprite.setTextureRect(sf::IntRect(93 * int(CurFrame), 2 * HEROY, HEROX, HEROY));
			View.GetCoordView(Hero.GetCoordX(), Hero.GetCoordY());
		}

		Hero.Update(time);
		View.ScrollMap(time);
		window.setView(View.view);
		window.clear(sf::Color(175, 140, 90, 0));

		for (int i(0); i < HEIGHT; ++i)
		{
			for (int j(0); j < WIDTH; ++j)
			{
				if (TileMap[i][j] == ' ')
					map_sprite.setTextureRect(sf::IntRect(0, 0, WGRASS, HGRASS));
				if (TileMap[i][j] == '0')
					map_sprite.setTextureRect(sf::IntRect(WGRASS, 0, WGRASS, HGRASS));
				if (TileMap[i][j] == 's')
					map_sprite.setTextureRect(sf::IntRect(WGRASS * 2, 0, WGRASS, HGRASS));
				if (TileMap[i][j] == 'w')
					map_sprite.setTextureRect(sf::IntRect(WGRASS * 3 + 4, 0, WGRASS, HGRASS));
				if (TileMap[i][j] == 'R')
					map_sprite.setTextureRect(sf::IntRect(WGRASS * 4 + 5, 0, WGRASS, HGRASS));

				map_sprite.setPosition(j * WGRASS, i * HGRASS);
				window.draw(map_sprite);
			}
		}

		
		window.draw(Hero.sprite);
		window.display();
	}

	return 0;
}