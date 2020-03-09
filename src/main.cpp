#include "Engine.h"


void PlayKotik()
{

	PlaySoundA("Music/laba.wav",	NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	PlaySoundA("Music/vapa.wav",	NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	//PlaySoundA("Music/japan.wav",	NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

void playDebug()
{
	PlaySoundA("Music/rain.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

bool	IsWalk				();
void	ChooseAction		(Player & Hero, int dir, double & CurFrame, sf::Int64 time, int X, int Y);
void	Process				(sf::RenderWindow & window, Map & map, MyView & View, Player & Hero, std::list<Enemy> & list);
void	ActionSwitch		(Player & Hero, double & CurFrame, sf::Int64 & time,
							sf::RenderWindow & window, MyView & View,
							PoolEnemies & poolEn, bool & isHit, sf::Event & event,
							bool isCreatePools, const bool isFoundAll, au::Audio & audio);
void	Hit					(Player & Hero, sf::Int64 & time,
							sf::RenderWindow & window, MyView & View);
void	SetCam				(sf::Event & event, sf::RenderWindow & window, bool & IsFullscreen);
//void	ChooseHit			(Player & Hero, int dir, double & CurFrame, sf::Int64 time, int X, int Y);

void Process (sf::RenderWindow & window, Map & map, MyView & View, Player & Hero, std::list<Enemy> & list)
{
	bool			IsFullscreen		(true);
	bool			isHit				(false);
	bool			isCreatePools		(false);
	bool			isFoundAll			(false);

	double			CurFrame			(0.0);
	sf::Clock		clock;
	sf::Clock		game_time_clock;
	int				game_time			(0);
	sf::Int64		timer				(0); 

	au::Audio audio				(1);
	std::vector<std::string>	strLoads{ "gun.wav" };
	audio.loadSounds			(strLoads);
	//audio.playSound				(0);

	/*sf::SoundBuffer buffer;
	if (!buffer.loadFromFile("Music/gun.wav"))
	{
		std::cout << "Audio error!!!" << std::endl;
	}

	sf::Sound sound;

	sound.setBuffer(buffer);
	sound.play();*/

	
	menu::showMenu(window, "Menu1.jpg");


	PoolEnemies enemy_pool	(30, "Enemy.png", "Archer1", W/2 + 200, H - 200, 64, 66);
	bs::PoolBullets bullet_pool;						// creating a pool

	Mission mission			("Kumach.png", "Intro.png");

	//std::list<Enemy>::iterator it;

	AllText fulltxt;
	fulltxt.PrintAll		();

	mission.LoadMission		();

	DragAndDrop dnd			(window);

	while (window.isOpen())
	{
		bool poolAlive = enemy_pool.isPoolAlive();
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
			
			if ((isFoundAll))
			{
				if((event.type == event.KeyPressed) && (event.key.code == sf::Keyboard::Space))
				{
					isCreatePools = true;
				}
			}
			//dnd.MoveMouse(window);
		}
		dnd.MoveSprite		(Hero, time);
		

		//dnd.DropColor(Hero, event);
		dnd.Action			(Hero);

		ActionSwitch		(Hero, CurFrame, time, window, View, enemy_pool, isHit,
							 event, isCreatePools, isFoundAll, audio);

 		View.ScrollMouse	(window, time, Hero.GetAlive());

		map.GenerateInTime	(timer, time, 15000, ' ', 'H', 1);
		map.GenerateInTime	(timer, time, 15000, ' ', 'M', 1);

		Hero.PurpleStyle	(time);
		Hero.OnFire			(time);

		

		Hero.Update			(time, map);
		Hit					(Hero, time, window, View);
		list.front			().Update		 (map, time);
		list.back			().Update		 (map, time);


		if (isCreatePools) {
			enemy_pool.addBullet(bullet_pool, "bullet1.png", "Bullet1", 0.2f, time, audio);
			bullet_pool.Update			(time);
			enemy_pool.Update			(map, time, Hero);
			bullet_pool.playerCollision	(Hero);
			Hero.underFire				(time);
			enemy_pool.bulletCollision	(bullet_pool);
		}


		View.ScrollMap		(time);
		window.setView		(View.view);
		window.clear		(sf::Color(175, 140, 90, 0));

		map.DrawMap			(window);

		fulltxt.DrawAll		(View, window, Hero, time, game_time);
		fulltxt.DrawTXT		(View, window, Hero, game_time, poolAlive);

		if (!isCreatePools)
		{
			fulltxt.DrawLazer(View, window, Hero, isFoundAll);
		}

		fulltxt.DrawSprite	(View, window, mission);

		fulltxt.DrawIntro	(View, window, mission, Hero);

		if (isCreatePools) {
			enemy_pool.DrawPool(window, time);
			bullet_pool.draw(window);
			if (!poolAlive)
			{
				static int ctime = game_time;
				fulltxt.drawFinalScore(View, window, Hero, ctime);
			}
		}

		// draw func

		Hero.draw			(window);
		list.front().draw	(window);
		list.back().draw	(window);
		

		//
		
		window.display	();
	}
}


//if (isF && isSpace)
//isCr = true;

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
		Hero.setTextureRect(sf::IntRect(X, Y, HEROX, HEROY));
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
	MyView & View, PoolEnemies & poolEn, bool & isHit, sf::Event & event,
	bool isCreatePools, const bool isFoundAll, au::Audio & audio)
{
	if (Hero.GetAlive()) {
		

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				ChooseAction(Hero, 0, CurFrame, time, HEROX * int(CurFrame), HEROY);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				ChooseAction(Hero, 1, CurFrame, time, HEROX * int(CurFrame), 3 * HEROY);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				ChooseAction(Hero, 2, CurFrame, time, HEROX * int(CurFrame), 0);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				ChooseAction(Hero, 3, CurFrame, time, HEROX * int(CurFrame), 2 * HEROY);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				window.close();
			}
			if (event.type == sf::Event::KeyPressed) {
				if ((event.key.code == sf::Keyboard::LAlt))
				{
					if (isHit == false)
					{
						std::cout << "Hitted!" << std::endl;
						isHit = true;
						Hero.SetHit();
						//audio.playSound(0);

						if(isCreatePools)
							poolEn.isAttacked(Hero);
					}

				}
			}
			else if (event.type == sf::Event::KeyReleased)
			{
				isHit = false;
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

//void ChooseHit(Player & Hero, int dir, double & CurFrame, sf::Int64 time, int X, int Y)
//{
//
//}

void Hit(Player & Hero, sf::Int64 & time, sf::RenderWindow & window,
	MyView & View)
{
	switch (Hero.GetDir())
	{
	case 0:
	{
		Hero.Hit(time, 5 * HEROY);
		break;
	}
	case 1:
	{
		Hero.Hit(time, 7 * HEROY);
		break;
	}
	case 2:
	{
		Hero.Hit(time, 4 * HEROY);
		break;

	}
	case 3:
	{
		Hero.Hit(time, 6 * HEROY);
		break;
	}
	default:
	{
		Hero.Hit(time, 5 * HEROY);
		break;
	}

}

	//Hero.sprite.setTextureRect(sf::IntRect(X, Y, HEROX, HEROY));
}



void FirstLevel(/*sf::RenderWindow & window*/)
{
	sf::RenderWindow window(sf::VideoMode(W, H), "Jeday");

	//window.setKeyRepeatEnabled(false);

	MyView View;
	View.view.reset(sf::FloatRect(XPOS - SETCAMX / 2, YPOS - SETCAMY / 2, SETCAMX, SETCAMY));
	window.create(sf::VideoMode(SETCAMX, SETCAMY), "Game", sf::Style::Fullscreen);


	Map    map("map.png");

	map.RandomGenerator(' ', 'P', 12);
	map.RandomGenerator(' ', 'D', 8);
	map.RandomGenerator(' ', 'R', 3);



	Enemy Archer1("Enemy.png", "Archer1", W / 2 + 280, H - 160, 64, 66, 0.0f);
	Enemy Archer2("Enemy.png", "Archer1", W / 2 + 180, H - 160, 64, 66, 0.0f);

	std::list<Enemy> enemies;
	enemies.push_back(Archer1);
	enemies.push_back(Archer2);
	

	Player Hero("with lazer1.png", "Player", 200, SETBEGIN, HEROX, HEROY);

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
