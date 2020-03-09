#pragma once

#include "Components.h"
#include "Constants.h"

extern std::ofstream fout;

class Map
{
	sf::String TileMap[HEIGHT] = {
		"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
		"B                     LLLLLLLL                                                           B",
		"B                       LLLLLLL                                                          B",
		"BT     TTT               LLLLLL                                                          B",
		"BTT     TT                  LLLLL                                                       wB",
		"BTTT                          LLLLLL                                                  wwwB",
		"BTTTT                            LLLLLLL                                           wwwwwwB",
		"BTTT                              LLLLLL                                       wwwwwwwwwwB",
		"BTT                                 LLLLLL                                   wwwwwwwwww  B",
		"B                                    LLLLL                                    wwwwwwww   B",
		"B                                     LLLLLL                                wwwwwwww     B",
		"B                                      LLLLL                              wwwwwww        B",
		"B                                     LLLL                             wwwwwwwww         B",
		"B                                    LLLLLL                        wwwwwwwwwwwww         B",
		"B                                 LLLLLLL                             wwwwwwwNwww        B",
		"B                               LLLLLLL                                 wwwwwwwwwwww     B",
		"B                              LLLLLLLLL                                   wwwwwwwwwww   B",
		"B                              LLLLLLLL                                      wwwwNNwwww  B",
		"B                               LLLLLLL                                     wwwwwNNNwwwwwB",
		"B                                 LLLLLLL                                  wwwwwwwwwwwwwwB",
		"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
	};

	sf::Image			map_image;
	sf::Texture			map;
	sf::Sprite			map_sprite;
	std::string			File;
	 
public:
	Map						(const std::string file);
	~Map					();
	void LoadIm				();
	void LoadMap			();
	void SetSprite			();
	void DrawMap			(sf::RenderWindow & window);
	char GetElemMap			(unsigned int first, unsigned int second);
	void SetElemMap			(unsigned int first, unsigned int second, char sym);
	void RandomGenerator	(char src, char dest, unsigned int number_);
	void GenerateInTime		(sf::Int64 & timer, sf::Int64 time, sf::Int64 period, char src, char dest, unsigned int number_);


};
