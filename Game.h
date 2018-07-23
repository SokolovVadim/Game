#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <list>
//#include "tinyxml\tinystr.h"
//#include "tinyxml\tinyxml.h"
//#include "TiledMapLoader0.1\level.h"
#include <Windows.h>
#include <sstream>
#include <Mmsystem.h>
#pragma comment(lib, "winmm.lib")



std::ofstream fout("LOG.txt");

enum MAP {
	HEIGHT = 21,
	WIDTH  = 90,
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
	XPOS     =	 WGRASS + 1,
	YPOS     =	 HGRASS + 1,
	SETDIR   =	 10,
	HEROX    =	 95,
	HEROY    =	 100,
	SETBEGIN =	 200,
	MAXSCORE =   3
};



#include "Map.h"
#include "Entity.h"
#include "Player.h"
#include "View.h"
#include "Mission.h"
#include "Text.h"
#include "DragAndDrop.h"
#include "Level.h"
#include "Enemy.h"
#include "Platform.h"
#include "PoolEnemies.h"
//#include "PoolEnemies.cpp"

#define asserted || fout << "WARNING! ASSERT WAS CALLED ON LINE %d\n" << __LINE__;

void PlayKotik();
	
#undef _USE_MATH_DEFINES
