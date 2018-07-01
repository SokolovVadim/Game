#pragma once


class Text 
{
private:
	sf::Font				font_t;
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
	std::string & str, /*std::ostringstream & stream,*/ unsigned int size) :
	font_t		(font),
	text_t		(text),
	color_t		(color),
	style_t		(style),
	str_t		(str),
	stream_t	(""),             // can not deliver the stream
	size_		(size)
{
	text.setFont			(font);
	text.setString			(str);
	text.setCharacterSize	(size);
	text.setFillColor		(color);
	text.setStyle			(style);
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


class AllText
{
private:
	Text		text1;
	Text		text2;
	Text		text3;
	sf::Font	font;
public:
	AllText			(sf::Font & font_, sf::Text & text, sf::Text & water, sf::Text & hp);
	void DrawAll	(MyView & View, sf::RenderWindow & window);
	void PrintAll	();
};

AllText::AllText(sf::Font & font_, sf::Text & text, sf::Text & water, sf::Text & hp) :
	text1(font_, text,  sf::Color::Black, sf::Text::Bold, std::string("Rubins: "), (unsigned int)24),
	text2(font_, water, sf::Color::Blue,  sf::Text::Bold, std::string("Air: "   ), (unsigned int)24),
	text3(font_, hp,    sf::Color::Red,   sf::Text::Bold, std::string("Health: "), (unsigned int)24)
{
	font.loadFromFile("Text/ARIAL.TTF");                // check how it works (reference in init. list)
	
}


void AllText::DrawAll(MyView & View, sf::RenderWindow & window)
{
	text1.Draw(View, window, -TEXTX, -TEXTY);
	text2.Draw(View, window, -TEXTX, -AIR);
	text3.Draw(View, window, -TEXTX, -HPY);
}

void AllText::PrintAll()
{
	text1.Print();
	text2.Print();
	text3.Print();
}
