#pragma once





class Map
{

	sf::String TileMap[HEIGHT] = {
		"00000000000000000000000000000000",
		"0  BBBB                        0",
		"0         P     R              0",
		"0                              0",
		"0     R       P                0",
		"0                              0",
		"0       wwwwwwwNwwwww          0",
		"0      wwwwwwwwwNwNww          0",
		"0LL     wwwwwwwwwNwNw          0",
		"0LLL   wwwwwwwwwwwwwR          0",
		"00000000000000000000000000000000",
	};

	sf::Image			map_image;
	sf::Texture			map;
	sf::Sprite			map_sprite;
public:
	void LoadIm			();
	void LoadMap		();
	void SetSprite		();
	void DrawMap        (sf::RenderWindow & window);
	Map(sf::Image & image, sf::Texture & texture, sf::Sprite & sprite);


};



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
	LoadIm		();
	LoadMap		();
	SetSprite	();
	std::cout << "Map was constructed!" << std::endl;
	fout << "Map was constructed!" << std::endl;
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
	if (!map_image.loadFromFile("images/map.png")) {
		fout << "Map was not loaded from file!" << std::endl;
	}
}



sf::String TileMap[HEIGHT] = {
	"00000000000000000000000000000000",
	"0  BBBB                        0",
	"0         P     R              0",
	"0                              0",
	"0     R       P                0",
	"0                              0",
	"0       wwwwwwwNwwwww          0",
	"0      wwwwwwwwwNwNww          0",
	"0LL     wwwwwwwwwNwNw          0",
	"0LLL   wwwwwwwwwwwwwR          0",
	"00000000000000000000000000000000",
};