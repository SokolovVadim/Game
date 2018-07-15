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
		LAVA   = 2,
		LENIN  = 3
	};
	MISS_NUMB miss_numb;
public:
	Mission							(const std::string file_Kum, const std::string file_Intro);
	~Mission						();
	void			SetCurMission	(float coord_x);
	unsigned int	GetCurMission	();
	std::string		GetTextMission	(unsigned int mission_numb);
	void			LoadMission		();
	bool	 &		IsShow			();
	void			SetShow			(bool value);
	void			SetKum			(float coord_x, float coord_y);
	void			DrawKum			(sf::RenderWindow & window);
	void			SetIntro		(float coord_x, float coord_y);
	void			DrawIntro		(sf::RenderWindow & window); 
};

Mission::Mission(const std::string file_Kum, const std::string file_Intro) :
	Kumach				({ sf::Image() }),
	Kumach_texture		({ sf::Texture() }),
	Kumach_s			({ sf::Sprite() }),
	Intro				(sf::Image()),
	Intro_texture		(sf::Texture()),
	Intro_s				(sf::Sprite()),
	show_mission_text	(true),
	File_Kum				(file_Kum),
	File_Intro(file_Intro),
	miss_numb			(RUBINS)
{}

Mission::~Mission()
{
	fout << "Mission has destructed" << std::endl;
}

void Mission::SetIntro(float coord_x, float coord_y)
{
	Intro_s.setPosition(coord_x, coord_y);
}

unsigned int Mission::GetCurMission()
{
	return miss_numb;
}

void Mission::DrawKum(sf::RenderWindow & window)
{
	window.draw(Kumach_s);
}

void Mission::DrawIntro(sf::RenderWindow & window)
{
	window.draw(Intro_s);
}

void Mission::SetKum(float coord_x, float coord_y)
{
	Kumach_s.setPosition(coord_x, coord_y);
}


void Mission::SetShow(bool value)
{
	show_mission_text = value;
}

bool & Mission::IsShow()
{
	return show_mission_text;
}

void Mission::LoadMission()
{

	Kumach.loadFromFile("Images/" + File_Kum);

	Kumach_texture.loadFromImage(Kumach);
	Kumach_s.setTexture(Kumach_texture);
	Kumach_s.setTextureRect(sf::IntRect(20, 0, 300, 100));

	Intro.loadFromFile("Images/" + File_Intro);

	Intro_texture.loadFromImage(Intro);
	Intro_s.setTexture(Intro_texture);
	Intro_s.setTextureRect(sf::IntRect(0, 0, 100, 100));

	//Kumach_s.setScale(1.0, 1.0);
}


void Mission::SetCurMission(float coord_x)
{
	//unsigned int mission;
	if (coord_x < RUBINS * 500) {
		miss_numb = RUBINS;
	}
	else
		if (coord_x < LAVA * 500) {
			miss_numb = LAVA;
		}
		else
			if (coord_x < LENIN * 500)
				miss_numb = LENIN;
}

std::string Mission::GetTextMission(unsigned int mission_numb)
{
	std::string text;
	switch (mission_numb)
	{
	case 1:
	{
		text = "Take red rubins\nto create a soviet\nlazer of justice\n";
		break;
	}
	case 2:
	{
		text = "You should avoid\nlava and money to save\ncommunism!\n";
		break;
	}
	case 3:
	{
		text = "Eat red stars\nto provide\nthe spirit of Lenin!\n";
		break;
	}
	default:
	{
		fout << "Wrong mission!" << std::endl;
	}
	}

	return text;

}