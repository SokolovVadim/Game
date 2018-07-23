#include "Game.h"

void PlayKotik()
{
	PlaySoundA("Music/laba.wav",	NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	PlaySoundA("Music/vapa.wav",	NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	PlaySoundA("Music/hentai.wav",	NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

bool	IsWalk				();
void	ChooseAction		(Player & Hero, int dir, double & CurFrame, sf::Int64 time, int X, int Y);
void	Process				(sf::RenderWindow & window, Map & map, MyView & View, Player & Hero, std::list<Enemy> & list);
void	ActionSwitch		(Player & Hero, double & CurFrame, sf::Int64 & time,
							sf::RenderWindow & window, MyView & View);
void	SetCam				(sf::Event & event, sf::RenderWindow & window, bool & IsFullscreen);

void Process (sf::RenderWindow & window, Map & map, MyView & View, Player & Hero, std::list<Enemy> & list)
{
	bool			IsFullscreen		(true);
	double			CurFrame			(0.0);
	sf::Clock		clock;
	sf::Clock		game_time_clock;
	int				game_time			(0);
	sf::Int64		timer				(0); 

	Mission mission("Kumach.png", "Intro.png");

	std::list<Enemy>::iterator it;

	AllText fulltxt;
	fulltxt.PrintAll();

	mission.LoadMission();

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
			SetCam(event, window, IsFullscreen);
			
			fulltxt.React		(event, window, mission, View, Hero);
			fulltxt.SetIntro	(mission, Hero, View, window);
			dnd.MainEffect		(event, Hero);
			dnd.Select			(window, event, Hero);
			dnd.Rpg				(event, Hero);
			
			//dnd.MoveMouse(window);
		}
		dnd.MoveSprite		(Hero, time);
		

		//dnd.DropColor(Hero, event);
		dnd.Action			(Hero);

		ActionSwitch		(Hero, CurFrame, time, window, View);

 		View.ScrollMouse	(window, time, Hero);

		map.GenerateInTime	(timer, time, 15000, ' ', 'H', 1);
		map.GenerateInTime	(timer, time, 15000, ' ', 'M', 1);

		Hero.PurpleStyle	(time);
		Hero.OnFire			(time);

		

		Hero.Update			(time, map);
		list.front().Update		(map, time);
		list.back().Update(map, time);
		View.ScrollMap		(time);
		window.setView		(View.view);
		window.clear		(sf::Color(175, 140, 90, 0));

		map.DrawMap			(window);

		fulltxt.DrawAll		(View, window, Hero, time, game_time);
		fulltxt.DrawTXT		(View, window, Hero); 
		fulltxt.DrawLazer	(View, window, Hero);

		fulltxt.DrawSprite	(View, window, mission);  ////!!!!!!!!!!

		fulltxt.DrawIntro	(View, window, mission, Hero);

		window.draw		(Hero.sprite);
		window.draw		(list.front().sprite);
		window.draw(list.back().sprite);
		window.display	();
	}
}

void SetCam(sf::Event & event, sf::RenderWindow & window, bool & IsFullscreen)
{
	switch (event.type)
	{
	case sf::Event::KeyReleased:
		switch (event.key.code)
		{
		case sf::Keyboard::Return:

			if (IsFullscreen) {
				window.create(sf::VideoMode(SETCAMX, SETCAMY), "Game", sf::Style::Default);
				IsFullscreen = false;
			}
			else {
				window.create(sf::VideoMode(SETCAMX, SETCAMY), "Game", sf::Style::Fullscreen);
				IsFullscreen = true;
			}
			break;
		}
		break;
	case sf::Event::Closed:
		window.close();
		break;
	}
}

void ChooseAction(Player & Hero, int dir, double & CurFrame, sf::Int64 time, int X, int Y)
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
			Hero.IncreasePower(time);
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

void ActionSwitch(Player & Hero, double & CurFrame, sf::Int64 & time, sf::RenderWindow & window,
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
			Hero.IncreasePower(time);
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



void FirstLevel(/*sf::RenderWindow & window*/)
{
	sf::RenderWindow window(sf::VideoMode(W, H), "Jeday");
	MyView View;
	View.view.reset(sf::FloatRect(XPOS - SETCAMX / 2, YPOS - SETCAMY / 2, SETCAMX, SETCAMY));
	window.create(sf::VideoMode(SETCAMX, SETCAMY), "Game", sf::Style::Fullscreen);


	Map    map("map.png");

	map.RandomGenerator(' ', 'P', 12);
	map.RandomGenerator(' ', 'D', 8);
	map.RandomGenerator(' ', 'R', 3);


	Enemy Archer1("Enemy.png", "Archer1", W / 2 + 280, H - 160, 64, 66);
	Enemy Archer2("Enemy.png", "Archer1", W / 2 + 180, H - 160, 64, 66);

	std::list<Enemy> enemies;
	enemies.push_back(Archer1);
	enemies.push_back(Archer2);
	

	Player Hero("sheet2.png", "Player", 200, SETBEGIN, HEROX, HEROY);

	Process(window, map, View, Hero, enemies);
}




int main()
{

	//PlayKotik();

	FirstLevel(/*window*/);
	//switch (LEVEL)
	//{
	//case 1:
	//	FirstLevel(window);
	//	break;
	//case 2:
	//	SecondLevel(window);
	//	break;
	//}

	return 0;
}
