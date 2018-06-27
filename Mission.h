#pragma once


unsigned int GetCurMission(float coord_x)
{
	unsigned int mission;
	if (coord_x < 500){
		mission = 1;
	}else
	if (coord_x < 1500) {
		mission = 2;
	}
	else
	if (coord_x < 2000)
		mission = 3;

	return mission;

}

std::string GetTextMission(unsigned int mission)
{
	std::string text;
	switch (mission)
	{
	case 1:
	{
		text = "Take red rubins\n to create a soviet lazer\n of justice\n";
		break;
	}
	case 2:
	{
		text = "You should avoid\nlava and money to save\ncommunism!\n";
		break;
	}
	case 3:
	{
		text = "Eat red stars\n to provide\n the spirit of Lenin!\n";
		break;
	}
	default:
	{
		fout << "Wrong mission!" << std::endl;
	}
	}

	return text;

}