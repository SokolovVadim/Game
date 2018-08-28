#pragma once
#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

//-----------------------------------------------------------------------
/// \brief Menu class to choose the game mode or settings
//-----------------------------------------------------------------------

class Menu
{
public:
	Menu();
	Menu(std::string & file);
	~Menu();
	void loadTextures();


private:
	std::string			_file;
	sf::Sprite			_sprite;
	sf::Texture			_texture;

	bool _isShow;
	enum BANNER
	{
		_PLAY = 0,
		_EXIT = 1
	};

	BANNER _bannerNumber;
};


#endif // !MENU_H
