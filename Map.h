#pragma once



class Map
{
	sf::String TileMap[HEIGHT] = {
		"00000000000000000000000000000000",
		"0                            ww0",
		"0                           www0",
		"0            0     0000000wwwww0",
		"0            0              www0",
		"0   ss       0                 0",
		"0                    000       0",
		"0                      0  BBB  0",
		"0         PNBL         0  BH   0",
		"0                      0  B   D0",
		"00000000000000000000000000000000",
	};

	sf::Image			map_image;
	sf::Texture			map;
	sf::Sprite			map_sprite;
	 
public:
	Map						(sf::Image & image, sf::Texture & texture, sf::Sprite & sprite);
	~Map					();
	void LoadIm				();
	void LoadMap			();
	void SetSprite			();
	void DrawMap			(sf::RenderWindow & window);
	char GetElemMap			(unsigned int first, unsigned int second);
	void SetElemMap			(unsigned int first, unsigned int second, char sym);
	void RandomGenerator	(char src, char dest, unsigned int number_);
	void GenerateInTime(sf::Int64 & timer, sf::Int64 time, sf::Int64 period, char src, char dest, unsigned int number_);


};


void Map::SetElemMap(unsigned int first, unsigned int second, char sym)
{
	TileMap[first][second] = sym;
}


void Map::DrawMap(sf::RenderWindow & window)
{ 
	for (int i(0); i < HEIGHT; ++i)	{
	for (int j(0); j < WIDTH;  ++j) {
		switch (TileMap[i][j])
		{
		case ' ':
		{
			map_sprite.setTextureRect(sf::IntRect(0, 0, WGRASS, HGRASS));
			break;
		}
		case '0':
		{
			map_sprite.setTextureRect(sf::IntRect(WGRASS, 0, WGRASS, HGRASS));
			break;
		}
		case 's':
		{
			map_sprite.setTextureRect(sf::IntRect(WGRASS * 2, 0, WGRASS, HGRASS));
			break;
		}
		case 'w':
		{
			map_sprite.setTextureRect(sf::IntRect(WGRASS * 3 + 4, 0, WGRASS, HGRASS));
			break;
		}
		case 'R':
		{
			map_sprite.setTextureRect(sf::IntRect(WGRASS * 4 + 5, 0, WGRASS, HGRASS)); 
			break;
		}
		case 'P':
		{
			map_sprite.setTextureRect(sf::IntRect(WGRASS * 5 + 5, 0, WGRASS, HGRASS));
			break;
		}
		case 'N':
		{
			map_sprite.setTextureRect(sf::IntRect(WGRASS * 6 + 6, 0, WGRASS, HGRASS));
			break;
		}
		case 'B':
		{
			map_sprite.setTextureRect(sf::IntRect(WGRASS * 7 + 6, 0, WGRASS, HGRASS));
			break;
		}
		case 'L':
		{
			map_sprite.setTextureRect(sf::IntRect(0, HGRASS, WGRASS, HGRASS));
			break;
		}
		case 'H':
		{
			map_sprite.setTextureRect(sf::IntRect(WGRASS + 1, HGRASS, WGRASS, HGRASS));
			break;
		}
		case 'D':
		{
			map_sprite.setTextureRect(sf::IntRect(WGRASS * 3 + 1, HGRASS, WGRASS, HGRASS));
			break;
		}
		}

		map_sprite.setPosition(float(j * WGRASS), float(i * HGRASS));
		window.draw(map_sprite);
	}
	}
}


Map::Map(sf::Image & image, sf::Texture & texture, sf::Sprite & sprite):
	map_image	(image),
	map			(texture),
	map_sprite	(sprite)
{
	TileMap;
	LoadIm		();
	LoadMap		();
	SetSprite	();
	std::cout << "Map was constructed!" << std::endl;
	fout << "Map was constructed!" << std::endl;
}

Map::~Map()
{
	fout << "Map has destructed!" << std::endl;
}

void Map::SetSprite()
{
	map_sprite.setTexture(map);
	fout << "Set sprite" << std::endl;
}


void Map::LoadMap()
{
	if (!map.loadFromImage(map_image)) {
		fout	  << "Map was not loaded from Image!" << std::endl;
	}
}


void Map::LoadIm()
{
	if (!map_image.loadFromFile("Images/map.png")) {
		fout << "Map was not loaded from file!" << std::endl;
	}
}


char Map::GetElemMap(unsigned int first, unsigned int second)
{
	return TileMap[first][second];
}



void Map::RandomGenerator(char src, char dest, unsigned int number_)
{
	int		RandomX(0), RandomY(0);

	srand((unsigned int)time(NULL));
	

	while(number_ > 0)
	{
		RandomX = 1 + rand() % (WIDTH  - 1);
		RandomY = 1 + rand() % (HEIGHT - 1);
		if ((RandomX < WIDTH) && (RandomX >= 1) && (RandomY < HEIGHT) && (RandomY >= 1)) {
			if (TileMap[RandomY][RandomX] == src){
				TileMap[RandomY][RandomX] = dest;
				number_--;
				fout << dest << " has generated on " << RandomX << " " << RandomY << std::endl;

			}
		}
	}
}


void Map::GenerateInTime(sf::Int64 & timer, sf::Int64 time, sf::Int64 period, char src, char dest, unsigned int number_)
{
	timer += time;
	//fout << "time : " << time << "timer: " << timer << std::endl;
	if (timer > period)
	{
		RandomGenerator(' ', 'H', number_);
		timer = 0;
		fout << "Generator succeed!" << std::endl;
	}
}
