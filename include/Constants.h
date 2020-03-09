#pragma once


enum MAP {
	HEIGHT = 21,
	WIDTH = 90,
	WGRASS = 48,
	HGRASS = 64
};

enum SCREEN {
	W = WGRASS * WIDTH,
	H = HGRASS * HEIGHT
};




enum ENGINE {
	HEALTH = 100,
	BSPEED = 0,
	XPOS = WGRASS + 1,
	YPOS = HGRASS + 1,
	SETDIR = 10,
	HEROX = 64,
	HEROY = 64,
	SETBEGIN = 200,
	MAXSCORE = 3
};