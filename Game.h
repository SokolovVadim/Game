#pragma once
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <Windows.h>
#include <Mmsystem.h>
#pragma comment(lib, "winmm.lib")



enum MAP {
	HEIGHT = 11,
	WIDTH = 22,
	WGRASS = 48,
	HGRASS = 64

};

enum SCREEN
{
	W = WGRASS * WIDTH,
	H = HGRASS * HEIGHT
};

enum ENGINE
{
	HEALTH = 100,
	BSPEED = 0,
	XPOS = W/2,
	YPOS = H/2,
	SETDIR = 10,
	HEROX = 95,
	HEROY = 100,
	SETBEGIN = 200
};




#include "Engine.h"
#include "Map.h"
#include "View.h"



std::ofstream fout("LOG.txt");

#define asserted || fout << "WARNING! ASSERT WAS CALLED ON LINE %d\n" << __LINE__;


void PlayKotik();

