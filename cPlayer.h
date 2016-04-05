#pragma once

#include "cBicho.h"

#define PLAYER_START_CX		3
#define PLAYER_START_CY		2

//nau-alpha.png
#define IMG_WIDTH_PLAYER 532
#define IMG_HEIGHT_PLAYER 372

// nau-alpha2.png
#define IMG_WIDTH_PLAYER1 269
#define IMG_HEIGHT_PLAYER1 269

class cPlayer: public cBicho
{
public:
	cPlayer();
	~cPlayer();

	void Draw(int tex_id);
	void Shoot(int type);
	void Advance();

	int getLives();
	void setLives(int lives);

	bool isAdvancing;

private:
	int lives;
	float steps;
	

};
