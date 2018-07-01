#pragma once


class Text 
{
private:
	//sf::Font				font_t;
	sf::Text				text_t;
	sf::Color				color_t;
	sf::Text::Style			style_t;
	std::string				str_t;
	std::ostringstream		stream_t;
	unsigned int			size_;

public:

	Text();
	Text(sf::Font & font, sf::Text & text, const sf::Color color, sf::Text::Style style,
		std::string & str, /*std::ostringstream & stream,*/ unsigned int size);
	void Draw(MyView & View, sf::RenderWindow & window, int correct_x, int correct_y);
	void Print();
	void PushStr(int value);
	std::ostringstream & GetStream();
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
	stream_t	(""),             // can not deliver the stream
	size_		(size)
{
	text_t.setFont			(font);
	text_t.setString			(str);
	text_t.setCharacterSize	(size);
	text_t.setFillColor		(color);
	text_t.setStyle			(style);
}

void Text::PushStr(int value)
{
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
	Text power_t;
	Text time_;
	Text		go_t;
	Text		task_t;
public:
	AllText(sf::Font & font_, sf::Text & text, sf::Text & water, sf::Text & hp,
		sf::Text & game_over, sf::Text & task, sf::Text & power, sf::Text & time);
	void DrawAll	(MyView & View, sf::RenderWindow & window, Actor & Hero, sf::Int64 & time, int & game_time);
	void PrintAll	();
};

AllText::AllText(sf::Font & font_, sf::Text & text, sf::Text & water, sf::Text & hp,
	sf::Text & game_over, sf::Text & task, sf::Text & power, sf::Text & time) :
	score_t (font_, text,      sf::Color::Black, sf::Text::Bold, std::string("Rubins: " ), (unsigned int)24 ),
	water_t (font_, water,     sf::Color::Blue,  sf::Text::Bold, std::string("Air: "    ), (unsigned int)24 ),
	hp_t	(font_, hp,        sf::Color::Red,   sf::Text::Bold, std::string("Health: " ), (unsigned int)24 ),
	power_t(font_, power, sf::Color::Red, sf::Text::Bold, std::string("Power: "), (unsigned int)24),
	time_(font_, time, sf::Color::Red, sf::Text::Bold, std::string("Time: "), (unsigned int)24),
	go_t    (font_, game_over, sf::Color::Red,   sf::Text::Bold, std::string("Game over"), (unsigned int)128),
	task_t  (font_, task,      sf::Color::Black, sf::Text::Bold, std::string("Task: "   ), (unsigned int)16 )
{
	;
}


void AllText::DrawAll(MyView & View, sf::RenderWindow & window, Actor & Hero, sf::Int64 & time, int & game_time)
{
	Hero.PushScore(score_t.GetStream());
	score_t.Draw(View, window, -TEXTX, -TEXTY);

	Hero.GetAir(water_t.GetStream(), time);
	water_t.Draw(View, window, -TEXTX, -AIR);

	time_.PushStr(game_time);
	Hero.PushPower(power_t.GetStream());

	Hero.SetHP(hp_t.GetStream());
	hp_t.Draw	(View, window, -TEXTX, -HPY);
	// time_  &  power_t
}


//void PrintText(Actor   & Hero, std::ostringstream & ScoreString, sf::Text  & text, MyView   & View,
//	sf::RenderWindow   & window, std::ostringstream & ScoreAir, sf::Int64 & time, sf::Text & water,
//	std::ostringstream & time_string, int & game_time, std::ostringstream & Power, std::ostringstream & HeatPoints,
//	sf::Text & hp)
//{
//	Hero.PushScore(ScoreString);
//	text.setString("Rubins: " + ScoreString.str());
//	text.setPosition(View.view.getCenter().x - TEXTX, View.view.getCenter().y - TEXTY);
//	window.draw(text);
//	//window.draw(Kumach_s);
//
//	Hero.GetAir(ScoreAir, time);
//	water.setString("Air: " + ScoreAir.str());
//	water.setPosition(View.view.getCenter().x - TEXTX, View.view.getCenter().y - AIR);
//	window.draw(water);
//
//	time_string << game_time;
//	Hero.PushPower(Power);
//
//	Hero.SetHP(HeatPoints);
//	hp.setString("Health: " + HeatPoints.str() + "\nTime: " + time_string.str() + "\nPower: " + Power.str());
//	hp.setPosition(View.view.getCenter().x - TEXTX, View.view.getCenter().y - HPY);
//	window.draw(hp);
//}p


void AllText::PrintAll()
{
	score_t.Print();
	water_t.Print();
	hp_t.Print();
}
