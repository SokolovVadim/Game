#pragma once
#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

//-----------------------------------------------------------------------
/// \brief Menu class to choose the game mode or settings
//-----------------------------------------------------------------------

namespace menu {
	class Menu
	{

	private:
		enum BANNER
		{
			_PLAY = 0,
			_EXIT = 1
		};
	public:
		Menu();
		Menu(const std::string & file);
		~Menu();

		void			setPosition	(const sf::Vector2f & pos);
		void			draw(sf::RenderWindow & window);
		void			setColor(const sf::Color color);
		void			setMenuNum(int number);
		void setMenuStatus(const bool status);

		const bool isDrawable() const;
		const BANNER getStatus() const;

		//void			loadTextures		();
		//void			loadSprites			();


	private:
		std::string			_file;
		sf::Texture			_texture;
		sf::Sprite			_sprite;

		//sf::RenderWindow	_window;

		bool _isShow;

		BANNER _bannerNumber;
	};

	void showMenu(sf::RenderWindow & window, const std::string & file);

}


#endif // !MENU_H
