// before redesign
#include "Game.h"

void PlayKotik()
{
	PlaySoundA("Music/laba.wav",   NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	PlaySoundA("Music/vapa.wav",   NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	PlaySoundA("Music/hentai.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

void LoadMission(bool show_mission_text);
void LoadText(sf::Font & font, sf::Text & text, std::string str,
	unsigned int size, sf::Color colour, sf::Text::Style style);

void Process(sf::RenderWindow & window, Map & map, MyView & View, Actor & Hero,
	sf::Clock & clock, sf::Clock & game_time_clock, int game_time,
	double CurFrame, sf::Text & text, sf::Text & water, sf::Text & hp,
	sf::Text & game_over, bool show_mission_text)
{
	while (window.isOpen())
	{

		sf::Int64 time = clock.getElapsedTime().asMicroseconds();

		if (Hero.GetAlive())
			game_time = int(game_time_clock.getElapsedTime().asSeconds());

		clock.restart();
		time /= 800;

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Tab)) {


				switch (show_mission_text)
				{
				case true:
				{
					break;
				}
				case false:
				{
					break;
				}
				}

			}






		}

		std::ostringstream GameOver;
		GameOver << "Game over";
		game_over.setString(GameOver.str());


		if (Hero.GetAlive()) {
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
				
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				Hero.SetDir(1);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
					Hero.SetSpeed(Hero.n_speed * 2);
				else
					Hero.SetSpeed(Hero.n_speed);
				CurFrame += 0.0052 * time;
				if (CurFrame > 9)
				{
					CurFrame -= 9;
				}
				Hero.sprite.setTextureRect(sf::IntRect(HEROX * int(CurFrame), 3 * HEROY, HEROX, HEROY));
				
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
				
			}


			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)))
			{
				Hero.SetDir(4);
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
				
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window.close();
			}
			View.GetCoordView(Hero.GetCoordX(), Hero.GetCoordY());
		}
		else
		{
			if (View.view.getCenter().x < W - SETCAMX/2)
			{
				View.view.move(0.5, 0);
				fout << "CoordX: " << View.view.getCenter().x << std::endl;
				
			}
		}

		if (Hero.GetScore() == MAXSCORE)  // need redesign
		{
			window.close();
		}

		Hero.Update(time);
		View.ScrollMap(time);
		window.setView(View.view);
		window.clear(sf::Color(175, 140, 90, 0));

		map.DrawMap(window);

		std::ostringstream ScoreString;
		Hero.PushScore(ScoreString);
		text.setString("Rubins: " + ScoreString.str());
		text.setPosition(View.view.getCenter().x - TEXTX, View.view.getCenter().y - TEXTY);
		window.draw(text);
 
		std::ostringstream ScoreAir;
		Hero.GetAir(ScoreAir, time);
		water.setString("Air: " + ScoreAir.str());
		water.setPosition(View.view.getCenter().x - TEXTX, View.view.getCenter().y - AIR);
		window.draw(water);

		std::ostringstream time_string;
		time_string << game_time;

		std::ostringstream HeatPoints;
		Hero.SetHP(HeatPoints);
		hp.setString("Health: " + HeatPoints.str() + "\nTime: " + time_string.str());
		hp.setPosition(View.view.getCenter().x - TEXTX, View.view.getCenter().y - HPY);
		window.draw(hp);

		if((View.view.getCenter().x >= W - SETCAMX / 2) && (!Hero.GetAlive()))
		{
			//           COnstants below!
			game_over.setPosition(View.view.getCenter().x - 180, View.view.getCenter().y - 50);
			window.draw(game_over);
		}


		window.draw(Hero.sprite);
		window.display();
	}
}






// наследовать Hero из Actor
// переделать карту
//

int main()
{

	//PlayKotik();

	sf::RenderWindow window(sf::VideoMode(W, H), "Jeday");
	MyView View;
	View.view.reset(sf::FloatRect(XPOS - SETCAMX/2, YPOS - SETCAMY/2, SETCAMX, SETCAMY));

	sf::Image	map_image;
	sf::Texture map_texture;
	sf::Sprite	map_sprite;

	Map    map		(map_image, map_texture, map_sprite);
	Actor Hero		("sheet2.png", HEALTH, 0, SETBEGIN, HEROX, HEROY);

	double			CurFrame			(0.0);
	sf::Clock		clock;
	sf::Clock		game_time_clock;
	int				game_time			(0);
	bool			show_mission_text	(true);

	sf::Font font;
	sf::Text text;
	sf::Text water;
	sf::Text hp;
	sf::Text game_over;


	//LoadMission(show_mission_text);
	font.loadFromFile("Text/ARIAL.TTF");

	{
		fout << "Text has loaded" << std::endl;
		text.setFont				(font);
		text.setString				("Rubins: ");
		text.setCharacterSize		(24);     // PRETTY CONSTATNT
		text.setFillColor			(sf::Color::Black);
		text.setStyle				(sf::Text::Bold | sf::Text::Underlined);

		LoadText(font, water,     "Air: ",     24, sf::Color::Blue, sf::Text::Bold);
		LoadText(font, hp,        "Health",    24, sf::Color::Red,  sf::Text::Bold);
		LoadText(font, game_over, "Game over", 64, sf::Color::Red,  sf::Text::Bold);


	}

	Process(window, map, View, Hero, clock, game_time_clock, game_time,
		CurFrame, text, water, hp, game_over, show_mission_text);
	return 0;
}


void LoadText(sf::Font & font, sf::Text & text, std::string str,
	unsigned int size, sf::Color color, sf::Text::Style style)
{
	text.setFont(font);
	text.setString(str);
	text.setCharacterSize(size);
	text.setFillColor(color);
	text.setStyle(style);

}

void LoadMission(bool show_mission_text)
{
	sf::Image Kumach;
	Kumach.loadFromFile("Images/Kumach.png");
	Kumach.createMaskFromColor(sf::Color::Transparent);
	sf::Texture Kumach_texture;
	Kumach_texture.loadFromImage(Kumach);
	sf::Sprite Kumach_s;
	Kumach_s.setTexture(Kumach_texture);
	Kumach_s.setTextureRect(sf::IntRect(0, 0, 320, 100));
	//Kumach_s.setScale();
}



