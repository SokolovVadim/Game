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
	void PushStr(std::string value);
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
	stream_t	(""),             // can not deliver the stream
	size_		(size)
{
	text_t.setFont			(font);
	text_t.setString			(str);
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

void Text::PushStr(int value)
{
	stream_t.str(std::string());
	stream_t << value;
}

void Text::PushStr(std::string value)
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
	//window.display();
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
	void DrawSprite (MyView & View, sf::RenderWindow & window, bool & is_show, sf::Sprite & Kumach_s);
	void DrawTXT(MyView & View, Actor & Hero, sf::RenderWindow & window);
	void React(sf::RenderWindow & window, bool & is_show, MyView & View, Actor & Hero, sf::Sprite & Kumach_s);
	Text & GetText();
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

void AllText::DrawSprite(MyView & View, sf::RenderWindow & window, bool & is_show, sf::Sprite & Kumach_s)
{
	if (!is_show) {
		
		//window.display();
		Kumach_s.setPosition(View.view.getCenter().x + 120, View.view.getCenter().y - 100);
		window.draw(Kumach_s);
		task_t.Draw(View, window, 200, -100);
	}
}

void AllText::PrintAll()
{
	score_t.Print();
	water_t.Print();
	hp_t.Print();
}

void AllText::React(sf::RenderWindow & window, bool & is_show, MyView & View, Actor & Hero, sf::Sprite & Kumach_s)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	
		if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Tab)) {
			fout << "TAB has pressed" << std::endl;
			switch (is_show)
			{
			case true:
			{
				task_t.PushStr( GetTextMission(GetCurMission(Hero.GetCoordX())));
				
				//task_t.PrepareToDraw(View, 200, -100);
				Kumach_s.setPosition(View.view.getCenter().x + 120, View.view.getCenter().y - 100);
				is_show = false;
				break;
			}
			case false:
			{				
				is_show = true;
				break;
			}
			}
		}
	}
}



//void React(sf::RenderWindow & window, bool & show_mission_text, std::ostringstream & task,
//	sf::Text & task_txt, MyView & View, Actor & Hero, sf::Sprite & Kumach_s)
//{
//	sf::Event event;
//	while (window.pollEvent(event))
//	{
//		if (event.type == sf::Event::Closed)
//			window.close();
//
//		if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Tab)) {
//			fout << "TAB has pressed" << std::endl;
//
//			switch (show_mission_text)
//			{
//			case true:
//			{
//
//				task << GetTextMission(GetCurMission(Hero.GetCoordX()));
//				task_txt.setString("Task: " + task.str());
//				task_txt.setPosition(View.view.getCenter().x + 200, View.view.getCenter().y - 100);
//				Kumach_s.setPosition(View.view.getCenter().x + 120, View.view.getCenter().y - 100);
//				show_mission_text = false;
//				break;
//			}
//			case false:
//			{
//				task_txt.setString("six nine");
//				show_mission_text = true;
//
//				break;
//			}
//			}
//		}
//	}
//}



//void DrawObjects(MyView & View, Actor & Hero, sf::Text & game_over, sf::RenderWindow & window,
//	bool & show_mission_text, sf::Text & task_txt, sf::Sprite & Kumach_s)
//{
//	if ((View.view.getCenter().x >= W - SETCAMX / 2) && (!Hero.GetAlive()))
//	{
//		//           COnstants below!
//		game_over.setPosition(View.view.getCenter().x - 310, View.view.getCenter().y - 100);
//		window.draw(game_over);
//	}
//
//	if (!show_mission_text) {
//		task_txt.setPosition(View.view.getCenter().x + 200, View.view.getCenter().y - 100);
//		Kumach_s.setPosition(View.view.getCenter().x + 120, View.view.getCenter().y - 100);
//		window.draw(Kumach_s);
//		window.draw(task_txt);
//	}
//}