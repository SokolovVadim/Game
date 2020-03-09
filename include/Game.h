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

#include "MyEnum.h"


#include "Map.h"
#include "Entity.h"
#include "Player.h"
#include "View.h"
#include "Mission.h"
#include "Text.h"
#include "DragAndDrop.h"
#include "Level.h"
#include "Attacked.h"
#include "Enemy.h"
#include "Platform.h"
#include "PoolEnemies.h"
//#include "Bullet.h"



#define asserted || fout << "WARNING! ASSERT WAS CALLED ON LINE %d\n" << __LINE__;

void PlayKotik();
	
#undef _USE_MATH_DEFINES
