class Mission
{
private:
	sf::Image Kumach;
	sf::Texture Kumach_texture;
	sf::Sprite		Kumach_s;
	bool			show_mission_text;
	std::string File;
public:
	Mission(const std::string file_);
	~Mission();
	unsigned int GetCurMission(float coord_x);
	std::string GetTextMission(unsigned int mission_numb);
	void LoadMission();
	bool & IsShow();
	void SetShow(bool value);
	void SetSpr(float coord_x, float coord_y);
	void Draw(sf::RenderWindow & window);
};

Mission::Mission(const std::string file_) :
	Kumach({ sf::Image() }),
	Kumach_texture({ sf::Texture() }),
	Kumach_s({ sf::Sprite() }),
	show_mission_text(true),
	File(file_)
{}

Mission::~Mission()
{
	fout << "Mission has destructed" << std::endl;
}

void Mission::Draw(sf::RenderWindow & window)
{
	window.draw(Kumach_s);
}

void Mission::SetSpr(float coord_x, float coord_y)
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

	Kumach.loadFromFile("Images/" + File);

	Kumach_texture.loadFromImage(Kumach);
	Kumach_s.setTexture(Kumach_texture);
	Kumach_s.setTextureRect(sf::IntRect(20, 0, 300, 100));
	//Kumach_s.setScale(1.0, 1.0);
}


unsigned int Mission::GetCurMission(float coord_x)
{
	unsigned int mission;
	if (coord_x < 500) {
		mission = 1;
	}
	else
		if (coord_x < 1000) {
			mission = 2;
		}
		else
			if (coord_x < 1500)
				mission = 3;

	return mission;

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