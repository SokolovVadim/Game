#ifndef MISSION_H
#define MISSION_H

#include "Components.h"
#include "Constants.h"

extern std::ofstream fout;

class Mission
{
private:
	sf::Image			Kumach;
	sf::Texture			Kumach_texture;
	sf::Sprite			Kumach_s;

	sf::Image			Intro;
	sf::Texture			Intro_texture;
	sf::Sprite			Intro_s;


	bool				show_mission_text;
	std::string			File_Kum;
	std::string			File_Intro;
	enum MISS_NUMB
	{
		RUBINS = 1,
		LAVA = 2,
		LENIN = 3
	};
	MISS_NUMB miss_numb;
public:
	Mission(const std::string file_Kum, const std::string file_Intro);
	~Mission();
	void			SetCurMission(float coord_x);
	unsigned int	GetCurMission();
	std::string		GetTextMission(unsigned int mission_numb);
	void			LoadMission();
	bool	 &		IsShow();
	void			SetShow(bool value);
	void			SetKum(float coord_x, float coord_y);
	void			DrawKum(sf::RenderWindow & window);
	void			SetIntro(float coord_x, float coord_y);
	void			DrawIntro(sf::RenderWindow & window);
};

#endif MISSION_H
