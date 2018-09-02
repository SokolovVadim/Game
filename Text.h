#pragma once


#include "Player.h"
#include "View.h"
#include "Mission.h"

class Text
{
private:
	sf::Text				text_t;
	sf::Color				color_t;
	sf::Text::Style			style_t;
	std::string				str_t;
	std::ostringstream		stream_t;
	unsigned int			size_;

public:

	Text();
	Text(sf::Font & font, sf::Text & text, const sf::Color color, sf::Text::Style style,
		std::string & str, unsigned int size);
	void Draw(MyView & View, sf::RenderWindow & window, int correct_x, int correct_y);
	void Print();

	template <typename T>
	void PushStr(T value);

	void PrepareToDraw(MyView & View, int correct_x, int correct_y);
	std::ostringstream & GetStream();
	sf::Text & GetText();
};




class AllText
{
private:
	sf::Font    font;
	Text		score_t;
	Text		water_t;
	Text		hp_t;
	Text		power_t;
	Text		time_;
	Text		go_t;
	Text		task_t;
	Text		lazer_t;
	Text		final_score_t;

public:
	AllText();
	void DrawAll(MyView & View, sf::RenderWindow & window, Player & Hero, sf::Int64 & time, int & game_time);
	void PrintAll();
	void DrawSprite(MyView & View, sf::RenderWindow & window, Mission & mission);
	void DrawTXT(MyView & View, sf::RenderWindow & window, Player & Hero, int & time, const bool poolAlive);
	void React(sf::Event & event, sf::RenderWindow & window, Mission & mission, MyView & View, Player & Hero);
	void SetIntro(Mission & mission, Player & Hero, MyView & View, sf::RenderWindow & window);
	void DrawIntro(MyView & View, sf::RenderWindow & window, Mission & mission, Player & Hero);
	void DrawLazer(MyView & View, sf::RenderWindow & window, Player & Hero, bool & isFoundAll);
	void drawFinalScore(MyView & View, sf::RenderWindow & window, Player & Hero, int & time);
	Text & GetText();
};

