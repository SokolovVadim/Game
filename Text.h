#pragma once

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

Text::Text() :
	color_t		(sf::Color::Black),
	style_t		(sf::Text::Bold),
	str_t		(""),
	size_		(0)
{
	;
}

Text::Text(sf::Font & font, sf::Text & text, const sf::Color color, sf::Text::Style style,
	std::string & str, unsigned int size) :
	text_t		(text),
	color_t		(color),
	style_t		(style),
	str_t		(str),
	stream_t	(""),
	size_		(size)
{
	text_t.setFont			(font);
	text_t.setString		(str);
	text_t.setCharacterSize	(size);
	text_t.setFillColor		(color);
	text_t.setStyle			(style);
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



class AllText
{
private:
	Text		score_t;
	Text		water_t;
	Text		hp_t;
	Text		power_t;
	Text		time_;
	Text		go_t;
	Text		task_t;
public:
	AllText(sf::Font & font_, sf::Text & text, sf::Text & water, sf::Text & hp,
		sf::Text & game_over, sf::Text & task, sf::Text & power, sf::Text & time);
	void DrawAll	(MyView & View, sf::RenderWindow & window, Actor & Hero, sf::Int64 & time, int & game_time);
	void PrintAll	();
	void DrawSprite (MyView & View, sf::RenderWindow & window, Mission & mission);
	void DrawTXT	(MyView & View, Actor & Hero, sf::RenderWindow & window);
	void React		(sf::Event & event, sf::RenderWindow & window, Mission & mission, MyView & View, Actor & Hero);
	Text & GetText	();
};

AllText::AllText(sf::Font & font_, sf::Text & text, sf::Text & water, sf::Text & hp,
	sf::Text & game_over,	   sf::Text & task,  sf::Text & power, sf::Text & time) :
	score_t (font_, text,      sf::Color::Black, sf::Text::Bold, std::string("Rubins: " ), 24u ),
	water_t (font_, water,     sf::Color::Blue,  sf::Text::Bold, std::string("Air: "    ), 24u ),
	hp_t	(font_, hp,        sf::Color::Red,   sf::Text::Bold, std::string("Health: " ), 24u ),
	power_t	(font_, power,	   sf::Color::Red,   sf::Text::Bold, std::string("Power: "  ), 24u ),
	time_	(font_, time,	   sf::Color::Red,   sf::Text::Bold, std::string("Time: "   ), 24u ),
	go_t    (font_, game_over, sf::Color::Red,   sf::Text::Bold, std::string("Game over"), 128u),
	task_t  (font_, task,      sf::Color::Black, sf::Text::Bold, std::string("Task: "   ), 16u )
{ }

Text & AllText::GetText()
{
	return task_t;
}

void AllText::DrawAll(MyView & View, sf::RenderWindow & window, Actor & Hero, sf::Int64 & time, int & game_time)
{
	Hero.PushScore(score_t.GetStream());
	score_t.Draw(View, window, -TEXTX, -TEXTY);

	Hero.GetAir(water_t.GetStream());
	water_t.Draw(View, window, -TEXTX, -TEXTY + 30);

	Hero.PushPower(power_t.GetStream());
	power_t.Draw(View, window, -TEXTX, -TEXTY + 60);

	Hero.SetHP(hp_t.GetStream());
	hp_t.Draw	(View, window, -TEXTX, -TEXTY + 90);

	time_.PushStr(game_time);
	time_.Draw(View, window, -TEXTX, -TEXTY + 120);
}

void AllText::DrawTXT(MyView & View, Actor & Hero, sf::RenderWindow & window)
{
	if ((View.view.getCenter().x >= W - SETCAMX / 2) && (!Hero.GetAlive()))
		{
			//           COnstants below!
			go_t.Draw(View, window, -310, -100);
		}
}

void AllText::DrawSprite(MyView & View, sf::RenderWindow & window, Mission & mission)
{
	if (!mission.IsShow()) {
		
		mission.SetSpr	(View.view.getCenter().x + 120, View.view.getCenter().y - 100);
		mission.Draw	(window);
		task_t.Draw		(View, window, 200, -100);
	}
}

void AllText::PrintAll()
{
	score_t.Print();
	water_t.Print();
	hp_t.Print();
}

void AllText::React(sf::Event & event, sf::RenderWindow & window, Mission & mission, MyView & View, Actor & Hero)
{
	if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Tab)) {
		fout << "TAB has pressed" << std::endl;
		switch (mission.IsShow())
		{
		case true:
		{
			task_t.PushStr	( mission.GetTextMission(mission.GetCurMission(Hero.GetCoordX())));
			mission.SetSpr	(View.view.getCenter().x + 120, View.view.getCenter().y - 100);
			mission.SetShow	(false);
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
