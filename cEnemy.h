#pragma once

#include "cTexture.h"
#include "Globals.h"
#include "posTexture.h"

#define LIFE_ENEMY_1 100
#define LIFE_ENEMY_2 500

#define IMG_WIDTH_ENEMY1 533
#define IMG_HEIGHT_ENEMY1 36

#define IMG_WIDTH_ENEMY2 398
#define IMG_HEIGHT_ENEMY2 100

#define ENEMY1_TRANSITION_SPEED 8

class cEnemy
{
public:
	cEnemy(void);
	cEnemy(int x, int y, int type);
	~cEnemy(void);

	bool isDead();
	void setDead(bool dead);

	void setPosXY(int x, int y);
	void getPosXY(int *x, int *y);

	void setWidthHeight(int w, int h);
	void getWidthHeight(int *w, int *h);

	int getLife();
	void setLife(int life);

	void setType(int type);
	int getType();

	void Draw(int idText);

protected:
	int life;
	bool dead;
	float x, y;
	float w, h;
	int type; // enemy type
	int animAct;	// state of the animation
	int delayAnim;

	vector<posTexture> seqEnemy;
};

