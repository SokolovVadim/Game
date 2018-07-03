﻿#include "Game.h"

void PlayKotik()
{
	PlaySoundA("Music/laba.wav",	NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	PlaySoundA("Music/vapa.wav",	NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	PlaySoundA("Music/hentai.wav",	NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

bool	IsWalk				();
void	ChooseAction		(Actor & Hero, int dir, double & CurFrame, sf::Int64 time, int X, int Y);
void	LoadMission			(sf::Sprite & Kumach_s, sf::Texture & Kumach_texture);
void	Process				(sf::RenderWindow & window, Map & map, MyView & View, Actor & Hero);
void	ActionSwitch		(Actor & Hero, double & CurFrame, sf::Int64 & time,
							sf::RenderWindow & window, MyView & View);

void Process (sf::RenderWindow & window, Map & map, MyView & View, Actor & Hero)
{
	// ref

	double			CurFrame(0.0);
	sf::Clock		clock;
	sf::Clock		game_time_clock;
	int				game_time(0);
	bool			show_mission_text(true);
	

	sf::Font font;

	if (!font.loadFromFile("Text/ARIAL.TTF"))		// check how it works (reference in init. list)
		fout << "Text has not loaded!" << std::endl;

	sf::Text text, water, hp, game_over, task_txt, power, time_t;

	AllText fulltxt(font, text, water, hp, game_over, task_txt, power, time_t);
	fulltxt.PrintAll();

	sf::Sprite		Kumach_s;
	sf::Texture		Kumach_texture;
	LoadMission		(Kumach_s, Kumach_texture);

	sf::Int64		timer	(0);

	// rpg interface  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	int tempX(0);
	int tempY(0);
	float distance(0.0f);

	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	DragAndDrop dnd(window);

	while (window.isOpen())
	{
		
		dnd.SetVectors(window);
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
			fulltxt.React(event, window, show_mission_text, View, Hero, Kumach_s);
			dnd.MainEffect(event, Hero);
			dnd.Select(window, event, Hero);
			dnd.Rpg(event, Hero);
			
			//dnd.MoveMouse(window);
		}
		dnd.MoveSprite(Hero, time);
		//dnd.DropColor(Hero, event);
		dnd.Action(Hero);

		ActionSwitch(Hero, CurFrame, time, window, View);

		View.ScrollMouse(window, time, Hero);

		map.GenerateInTime(timer, time, 10000, ' ', 'H', 1);

		Hero.Update			(time, map);
		View.ScrollMap		(time);
		window.setView		(View.view);
		window.clear		(sf::Color(175, 140, 90, 0));

		map.DrawMap(window);

		fulltxt.DrawAll(View, window, Hero, time, game_time);
		fulltxt.DrawTXT(View, Hero, window);

		fulltxt.DrawSprite(View, window, show_mission_text, Kumach_s); 

		window.draw(Hero.sprite);
		window.display();
	}
}

void ChooseAction(Actor & Hero, int dir, double & CurFrame, sf::Int64 time, int X, int Y)
{
		Hero.SetDir(dir);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			if (Hero.SetPower(time))
				Hero.SetSpeed(Hero.n_speed * 2);
			else
				Hero.SetSpeed(Hero.n_speed);
		}
		else
		{
			Hero.SetSpeed(Hero.n_speed);
			Hero.ReducePower(time);
		}
		CurFrame += 0.0052 * time;
		
		if (CurFrame > 9)
		{
			CurFrame -= 9;
		}
		Hero.sprite.setTextureRect(sf::IntRect(X, Y, HEROX, HEROY));
}

bool IsWalk()
{
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down)  || (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) ||
		(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))))
		return true;
	else
		return false;
}

void LoadMission(sf::Sprite & Kumach_s, sf::Texture & Kumach_texture)
{
	sf::Image Kumach;
	Kumach.loadFromFile("Images/Kumach.png");
	
	Kumach_texture.loadFromImage	(Kumach);
	Kumach_s.setTexture				(Kumach_texture);
	Kumach_s.setTextureRect			(sf::IntRect(20, 0, 300, 100));
	//Kumach_s.setScale(1.0, 1.0);
}


void ActionSwitch(Actor & Hero, double & CurFrame, sf::Int64 & time, sf::RenderWindow & window,
	MyView & View)
{
	if (Hero.GetAlive()) {

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			ChooseAction(Hero, 0, CurFrame, time, HEROX * int(CurFrame), HEROY);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			ChooseAction(Hero, 1, CurFrame, time, HEROX * int(CurFrame), 3 * HEROY);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			ChooseAction(Hero, 2, CurFrame, time, 93 * int(CurFrame), 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			ChooseAction(Hero, 3, CurFrame, time, 93 * int(CurFrame), 2 * HEROY);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			window.close();
		}
		if (!IsWalk())
		{
			;
		}
		if (!((sf::Keyboard::isKeyPressed(sf::Keyboard::W)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) ||
			(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) ||
			(sf::Mouse::isButtonPressed(sf::Mouse::Left))))
			View.GetCoordView(Hero.GetCoordX(), Hero.GetCoordY());
	}
	else
	{
		if (View.view.getCenter().x < W - SETCAMX / 2)
		{
			View.view.move(0.5, 0);
			fout << "CoordX: " << View.view.getCenter().x << std::endl;

		}
	}
}


int main()
{

	//PlayKotik();

	sf::RenderWindow window(sf::VideoMode(W, H), "Jeday");
	MyView View;
	View.view.reset(sf::FloatRect(XPOS - SETCAMX / 2, YPOS - SETCAMY / 2, SETCAMX, SETCAMY));

	sf::Image	map_image;
	sf::Texture map_texture;
	sf::Sprite	map_sprite;

	Map    map(map_image, map_texture, map_sprite);

	map.RandomGenerator(' ', 's', 1);
	map.RandomGenerator(' ', 'D', 8);
	map.RandomGenerator(' ', 'R', 1);

	Actor Hero("sheet2.png", HEALTH, 0, SETBEGIN, HEROX, HEROY);

	Process(window, map, View, Hero);
	return 0;
}
