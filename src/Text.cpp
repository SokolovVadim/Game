#include "Text.h"

Text::Text() :
	color_t(sf::Color::Black),
	style_t(sf::Text::Bold),
	str_t(""),
	size_(0)
{
	;
}

Text::Text(sf::Font & font, sf::Text & text, const sf::Color color, sf::Text::Style style,
	std::string & str, unsigned int size) :
	text_t(text),
	color_t(color),
	style_t(style),
	str_t(str),
	stream_t(""),
	size_(size)
{
	text_t.setFont(font);
	text_t.setString(str);
	text_t.setCharacterSize(size);
	text_t.setFillColor(color);
	text_t.setStyle(style);
}

sf::Text & Text::GetText()
{
	return text_t;
}

void Text::PrepareToDraw(MyView & View, int correct_x, int correct_y)
{
	text_t.setString(str_t + stream_t.str());
	text_t.setPosition(View.view.getCenter().x + correct_x, View.view.getCenter().y + correct_y);
}

template<typename T>
void Text::PushStr(T value)
{
	stream_t.str(std::string());
	stream_t << value;
}

std::ostringstream & Text::GetStream()
{
	return stream_t;
}


void Text::Draw(MyView & View, sf::RenderWindow & window, int correct_x, int correct_y)
{
	text_t.setString(str_t + stream_t.str());
	text_t.setPosition(View.view.getCenter().x + correct_x, View.view.getCenter().y + correct_y);
	window.draw(text_t);
}

void Text::Print()
{
	fout << "default text: " << str_t << ", now text: " << stream_t.str() << std::endl;
}



AllText::AllText() :
	font({ sf::Font() }),
	score_t(font, sf::Text(), sf::Color::Black, sf::Text::Bold, std::string("Rubins: "), 24u),
	water_t(font, sf::Text(), sf::Color::Blue, sf::Text::Bold, std::string("Air: "), 24u),
	hp_t(font, sf::Text(), sf::Color::Red, sf::Text::Bold, std::string("Health: "), 24u),
	power_t(font, sf::Text(), sf::Color::Red, sf::Text::Bold, std::string("Power: "), 24u),
	time_(font, sf::Text(), sf::Color::Red, sf::Text::Bold, std::string("Time: "), 24u),
	go_t(font, sf::Text(), sf::Color::Red, sf::Text::Bold, std::string("Game over"), 128u),
	task_t(font, sf::Text(), sf::Color::Black, sf::Text::Bold, std::string("Task: "), 16u),
	lazer_t(font, sf::Text(), sf::Color::Red, sf::Text::Bold, std::string("         You have taken"
		" all rubins\n             for lazer of justice!\nPress SPACE to go to the next level!\n"
		"	P.S. don't eat a lot of mushrooms"), 32u),
	final_score_t(font, sf::Text(), sf::Color::Black, sf::Text::Bold, std::string("YOUR SCORE: "), 32u)
{
	if (!font.loadFromFile("Text/ARIAL.TTF"))		// check how it works (reference in init. list)
		fout << "Text has not loaded!" << std::endl;
}

void AllText::DrawLazer(MyView & View, sf::RenderWindow & window, Player & Hero, bool & isFoundAll)
{
	if ((Hero.GetScore() >= 3) && (Hero.GetAlive()))
	{
		lazer_t.Draw(View, window, -210, -100);
		isFoundAll = true;
	}
}

Text & AllText::GetText()
{
	return task_t;
}

void AllText::DrawAll(MyView & View, sf::RenderWindow & window, Player & Hero, sf::Int64 & time, int & game_time)
{
	Hero.PushScore(score_t.GetStream());
	score_t.Draw(View, window, -TEXTX, -TEXTY);

	Hero.GetAir(water_t.GetStream());
	water_t.Draw(View, window, -TEXTX, -TEXTY + 30);

	Hero.PushPower(power_t.GetStream());
	power_t.Draw(View, window, -TEXTX, -TEXTY + 60);

	Hero.SetHP(hp_t.GetStream());
	hp_t.Draw(View, window, -TEXTX, -TEXTY + 90);

	time_.PushStr(game_time);
	time_.Draw(View, window, -TEXTX, -TEXTY + 120);
}

void AllText::drawFinalScore(MyView & View, sf::RenderWindow & window, Player & Hero, int & time)
{
	final_score_t.PushStr	(time);
	final_score_t.Draw		(View, window, -100, 100); //!!!
}

void AllText::DrawTXT(MyView & View, sf::RenderWindow & window, Player & Hero, int & time, const bool poolAlive)
{
	if ((View.view.getCenter().x >= W - SETCAMX / 2) && (!Hero.GetAlive()) && (poolAlive))
	{
		//           COnstants below!

		go_t.Draw			(View, window, -310, -100);
		drawFinalScore		(View, window, Hero, time);

		//final_score_t.PushStr(time);
		//final_score_t.Draw(View, window, -100, 100); //!!!
	}
}

void AllText::DrawSprite(MyView & View, sf::RenderWindow & window, Mission & mission)
{
	if (!mission.IsShow()) {

		mission.SetKum(View.view.getCenter().x + 120, View.view.getCenter().y - 100);
		mission.DrawKum(window);
		task_t.Draw(View, window, 200, -100);
	}
}

void AllText::PrintAll()
{
	score_t.Print();
	water_t.Print();
	hp_t.Print();
}

void AllText::React(sf::Event & event, sf::RenderWindow & window, Mission & mission, MyView & View, Player & Hero)
{
	if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Tab)) {
		fout << "TAB has pressed" << std::endl;
		switch (mission.IsShow())
		{
		case true:
		{
			mission.SetCurMission(Hero.GetCoordX());
			task_t.PushStr(mission.GetTextMission(mission.GetCurMission()));
			mission.SetKum(View.view.getCenter().x + 120, View.view.getCenter().y - 100);
			mission.SetShow(false);
			break;
		}
		case false:
		{
			mission.SetShow(true);
			break;
		}
		}
	}
}

void AllText::SetIntro(Mission & mission, Player & Hero, MyView & View, sf::RenderWindow & window)
{
	if (Hero.GetCoordX() < 100.0f)
	{
		mission.SetIntro(View.view.getCenter().x - 100, View.view.getCenter().y - 80);
	}
}

void AllText::DrawIntro(MyView & View, sf::RenderWindow & window, Mission & mission, Player & Hero)
{
	if (Hero.GetCoordX() < 100.0f)
	{
		mission.SetIntro(View.view.getCenter().x - 100, View.view.getCenter().y - 80);
		mission.DrawIntro(window);
	}
}

