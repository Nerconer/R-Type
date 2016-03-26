#pragma once

#include "cBicho.h"

#define PLAYER_START_CX		3
#define PLAYER_START_CY		2

//nau-alpha.png
#define IMG_WIDTH_PLAYER 532
#define IMG_HEIGHT_PLAYER 372

class cPlayer: public cBicho
{
public:
	cPlayer();
	~cPlayer();

	void Draw(int tex_id);
	void Shoot(int type);
	void Advance();

};