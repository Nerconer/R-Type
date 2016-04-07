#pragma once

#include "cBicho.h"

#define PLAYER_START_CX		3
#define PLAYER_START_CY		2

//nau-alpha.png
#define IMG_WIDTH_PLAYER 166
#define IMG_HEIGHT_PLAYER 86

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

	int getHurted();

	void setHurted(int hurted);

	bool isAdvancing;

	bool getIsKilledByRight();
	void setIsKilledByRight(bool killed);

	bool getBackWindow();
	void setBackWindow(bool b);

	void setNauSelected(int nauSeleted);
	int getNauSelected();

private:
	int lives;
	float steps;
	bool isKilledByRight;
	int hurted;
	bool backWindow;

	int nauSelected;
};
