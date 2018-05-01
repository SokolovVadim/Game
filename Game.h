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






enum ENGINE
{
	HEALTH = 100,
	SPEED = 0,
	XPOS = 495,
	YPOS = 310,
	SETDIR = 10
};


#include "Engine.h"
#include "Map.h"

std::ofstream fout("LOG.txt");

#define asserted || fout << "WARNING! ASSERT WAS CALLED ON LINE %d\n" << __LINE__;


void PlayKotik();

