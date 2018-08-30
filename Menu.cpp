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

	Menu::Menu() :
		_numbSets				(0ul),
		_setsVec				(_numbSets),
		_isShow					(true),
		_bannerNumber			(BANNER::_PLAY)
	{
		//_texture.loadFromFile("Images/" + _file);
	}

	Menu::Menu(std::size_t size, ...) :
		_numbSets				(size),
		_setsVec				(_numbSets),
		_isShow					(true),
		_bannerNumber			(BANNER::_PLAY)
	{
		va_list args;

		va_start(args, size);

		while (size--)
		{
			_setsVec.push_back(*(new MenuSet(va_arg(args, const std::string))));
		}

		va_end(args);

		/*_texture.loadFromFile("Images/" + _file);
		_sprite.setTexture(_texture);*/
	}

	Menu::~Menu()
	{}

	void MenuSet::setPosition(const sf::Vector2f & pos)
	{
		_sprite.setPosition(pos);
	}

	void MenuSet::draw(sf::RenderWindow & window)
	{
		window.draw			(_sprite);
		window.display		();
	}

	const bool Menu::isDrawable() const
	{
		return _isShow;
	}

	void MenuSet::setColor(const sf::Color color)
	{
		_sprite.setColor(color);
	}

	void Menu::setMenuNum(int number)
	{
		switch (number)
		{
		case BANNER::_PLAY:
			_bannerNumber = _PLAY;
		case BANNER::_EXIT:
			_bannerNumber = _EXIT;
		default:
		{
			_bannerNumber = _EXIT;
		}
		}
	}

	void Menu::setMenuStatus(const bool status)
	{
		_isShow = status;
	}

	const Menu::BANNER Menu::getStatus() const
	{
		return _bannerNumber;
	}

	void showMenu(sf::RenderWindow & window, const std::string & file)
	{
		Menu menu(2, "Menu1.jpg", "play.png");
		//menu.setPosition(sf::Vector2f(0.f, 0.f)); // it is not so bad
													  // but it should be corrected
		while (menu.isDrawable())
		{
			//menu.setColor				(sf::Color::White);
			menu.setMenuNum				(0);
			window.clear(sf::Color(10, 10, 10, 10));

			//if (sf::IntRect(100, 100, 100, 100).contains(sf::Mouse::getPosition(window))) // play
			//{
			//	menu.setColor					(sf::Color::Blue);
			//	menu.setMenuNum					(0);
			//}
			//if (sf::IntRect(100, 200, 100, 100).contains(sf::Mouse::getPosition(window))) // exit
			//{
			//	menu.setColor					(sf::Color::Blue);
			//	menu.setMenuNum					(1);
			//}
			//if (sf::IntRect(100, 300, 100, 100).contains(sf::Mouse::getPosition(window))) // smth new (sttngs?)
			//{
			//	menu.setColor					(sf::Color::Blue);
			//	menu.setMenuNum					(2);
			//}

			//if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) // play
			//{
			//	int status = menu.getStatus();

			//	switch (status)
			//	{
			//	case 0:
			//		menu.setMenuStatus(false);
			//	case 1:
			//	{
			//		window.close();
			//		menu.setMenuStatus(false);
			//	}
			//	}

			//}

			//menu.draw(window);
		}
	}

}
//void Menu::loadTextures()
//{
//	_texture.loadFromFile(_file);
//}

//void Menu::loadSprites() :
//	_sprite(_texture)
//{
//	;
//}
