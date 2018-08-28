#include "Menu.h"

Menu::Menu():
	_file				(""),
	_sprite				(sf::Sprite()),
	_texture			(sf::Texture()),
	_isShow				(true),
	_bannerNumber		(BANNER::_PLAY)
{}

Menu::Menu(std::string & file):
	_file				(file),
	_sprite				(sf::Sprite()),
	_texture			(sf::Texture()),
	_isShow				(true),
	_bannerNumber		(BANNER::_PLAY)
{}

Menu::~Menu()
{}

void Menu::loadTextures()
{
	_texture.loadFromFile(_file);
}
