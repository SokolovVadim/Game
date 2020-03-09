#include "Menu.h"
namespace menu {


	MenuSet::MenuSet() :
		_file(""),
		_texture(sf::Texture()),
		_sprite(_texture)
	{}

	MenuSet::MenuSet(const std::string & file) :
		_file(file),
		_texture(sf::Texture()),
		_sprite(sf::Sprite())
	{
		_texture.loadFromFile("Images/" + _file);
		_sprite.setTexture(_texture);
	}

	MenuSet::~MenuSet()
	{}

	void MenuSet::setPosition(const sf::Vector2f & pos)
	{
		_sprite.setPosition(pos);
	}

	void MenuSet::draw(sf::RenderWindow & window)
	{
		window.draw(_sprite);
	}

	void MenuSet::setColor(const sf::Color color)
	{
		_sprite.setColor(color);
	}

	//-----------------------------------------------------------------------------------

	// write setPos & setColor with variable args, draw func without var. args

	Menu::Menu() :
		_numbSets				(0ul),
		//_setsVec				(_numbSets),
		_isShow					(true),
		_bannerNumber			(BANNER::_PLAY)
	{
		//_texture.loadFromFile("Images/" + _file);
	}

	Menu::Menu(std::size_t size, ...) :
		_numbSets				(size),
		//_setsVec				(_numbSets),
		_isShow					(true),
		_bannerNumber			(BANNER::_PLAY)
	{
		va_list args;

		va_start(args, size);

		while (size--)
		{
			_setsVec.push_back(*(new MenuSet(va_arg(args, char*))));
			//std::cout << va_arg(args, char*) << std::endl;
		}

		va_end(args);

		/*_texture.loadFromFile("Images/" + _file);
		_sprite.setTexture(_texture);*/
	}

	Menu::~Menu()
	{}

	void Menu::setPosition(std::size_t size, ... )
	{
		va_list args;

		/*std::size_t */size =						_setsVec.size();
		std::vector<MenuSet>::iterator it =		_setsVec.begin();
		std::vector<MenuSet>::iterator vecEnd = _setsVec.end();

		va_start(args, size);

		//std::cout << (va_arg(args, int)) << std::endl;

		while ((it != vecEnd) && (size--))
		{
			//sf::Vector2f cur_vec = sf::Vector2f(va_arg(args, const sf::Vector2f));
			it->setPosition((va_arg(args, const sf::Vector2f )));  // no refs!!!
			//std::cout << (va_arg(args, float)) << std::endl;
			it++;
		}

		va_end(args);
	}

	void Menu::setColor(...)
	{
		va_list args;

		std::size_t size = _setsVec.size();
		std::vector<MenuSet>::iterator it = _setsVec.begin();
		std::vector<MenuSet>::iterator vecEnd = _setsVec.end();

		va_start(args, size);
		while ((it != vecEnd) && (size--))
		{
			it->setColor(va_arg(args, const sf::Color));
			it++;
		}

		va_end(args);
	}

	void Menu::draw(sf::RenderWindow & window)
	{
		std::vector<MenuSet>::iterator it = _setsVec.begin();
		std::vector<MenuSet>::iterator vecEnd = _setsVec.end();

		while (it != vecEnd)
		{
			it->draw(window);
			it++;
		}
		window.display();
		//std::cout << _setsVec.size() << std::endl;
	}

	const bool Menu::isDrawable() const
	{
		return _isShow;
	}

	void Menu::setMenuNum(int number, au::Audio & audio)
	{
		switch (number)
		{
		case BANNER::_PLAY:
		{
			_bannerNumber = _PLAY;
			break;
		}
		case BANNER::_SETTINGS:
		{
			_bannerNumber = _SETTINGS;
			break;
		}
		case BANNER::_EXIT:
		{
			_bannerNumber = _EXIT;
			break;
		}
		default:
		{
			_bannerNumber = _EXIT;
		}
		}

		/*if(number != 0)*/
		//audio.playSound(2);
	}

	void Menu::setMenuStatus(const bool status)
	{
		_isShow = status;
	}

	const Menu::BANNER Menu::getStatus() const
	{
		return _bannerNumber;
	}

	MenuSet & Menu::getSet(const std::size_t num)
	{
		return _setsVec[num];
	}


	//-----------------------------------------------------------------------------------

	void showMenu(sf::RenderWindow & window, const std::string & file, au::Audio & audio)
	{
		bool isPlay = false;
		const std::size_t numbPict = 4;
		const float centreX = (1600 - 640) / 2.f;
		const float centreY = (900 - (numbPict - 1)*120) / 2.f;
		Menu menu(numbPict, "Menu1.jpg", "play.png", "settings.png", "exit.png");

		//sf::Vector2f pos_1 = new sf::Vector2f;

		menu.setPosition(numbPict, sf::Vector2f(0.f, 0.f), sf::Vector2f(centreX, centreY),
			sf::Vector2f(centreX, centreY + 120), sf::Vector2f(centreX, centreY + 240)); // it is not so bad
													  // but it should be corrected
		while (menu.isDrawable())
		{
			//menu.setColor				(sf::Color::White, sf::Color::White);
			menu.setMenuNum				(1, audio);
			
			//window.clear(sf::Color(100, 0, 10, 10));
			//window.clear(sf::Color(175, 140, 90, 0));

			if (sf::IntRect(int(centreX), int(centreY), 640, 120).contains(sf::Mouse::getPosition(window))) // play
			{
				if (!audio.isPlay(0))
				{
					audio.setPlay(0, true);
					audio.playSound(2);
				}
				menu.getSet(1).setColor				(sf::Color::Red);
				menu.setMenuNum						(0, audio);
			}
			else
			{
				audio.setPlay(0, false);
				menu.getSet(1).setColor(sf::Color::White);
			}
			if (sf::IntRect(int(centreX), int(centreY) + 120, 640, 120).contains(sf::Mouse::getPosition(window))) // exit
			{
				if (!audio.isPlay(1))
				{
					audio.setPlay(1, true);
					audio.playSound(2);
				}
				
				menu.getSet(2).setColor(sf::Color::Red);
				menu.setMenuNum(1, audio);
			}
			else
			{
				audio.setPlay(1, false);
				menu.getSet(2).setColor(sf::Color::White);
			}
			if (sf::IntRect(int(centreX), int(centreY) + 240, 640, 120).contains(sf::Mouse::getPosition(window))) // play
			{
				if (!audio.isPlay(2))
				{
					audio.setPlay(2, true);
					audio.playSound(2);
				}
				
				menu.getSet(3).setColor(sf::Color::Red);
				menu.setMenuNum(2, audio);
			}
			else
			{
				audio.setPlay(2, false);
				menu.getSet(3).setColor(sf::Color::White);
			}
			

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) // play
			{
				audio.playSound(3);
				int status = menu.getStatus(); // menu num

				switch (status)
				{
				case 0: // play
				{
					menu.setMenuStatus(false);
					break;
				}
				case 1: // settings
				{
					/*window.close();
					menu.setMenuStatus(false);*/
					break;
				}
				case 2: // exit
				{
					window.close();
					menu.setMenuStatus(false);
					break;
				}
				}
			}

			menu.draw(window);
		}
	}

}
