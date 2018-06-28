#pragma once
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <Windows.h>
#include <sstream>
#include <Mmsystem.h>
#pragma comment(lib, "winmm.lib")


std::ofstream fout("LOG.txt");

enum MAP {
	HEIGHT = 11,
	WIDTH  = 32,
	WGRASS = 48,
	HGRASS = 64
};

enum SCREEN {
	W = WGRASS * WIDTH,
	H = HGRASS * HEIGHT
};

enum ENGINE {
	HEALTH   =	 100,
	BSPEED   =	 0,
	XPOS     =	 W/2,
	YPOS     =	 H/2,
	SETDIR   =	 10,
	HEROX    =	 95,
	HEROY    =	 100,
	SETBEGIN =	 200,
	MAXSCORE =   3
};


#include "Map.h"
#include "Actor.h"
#include "View.h"
#include "Mission.h"



#define asserted || fout << "WARNING! ASSERT WAS CALLED ON LINE %d\n" << __LINE__;


void PlayKotik();
