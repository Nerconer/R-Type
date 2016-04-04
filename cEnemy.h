#pragma once

#include "cTexture.h"
#include "Globals.h"

#define LIFE_ENEMY_1 100
#define LIFE_ENEMY_2 500



class cEnemy
{
public:
	cEnemy(void);
	cEnemy(int x, int y, int type);
	~cEnemy(void);

	bool isDead();
	void setDead(bool dead);

	void setPosXY(int x, int y);
	void getPosXY(int x, int y);

	void setWidthHeight(int w, int h);
	void getWidthHeight(int w, int h);

	int getLife();
	void setLife(int life);

	void setType(int type);
	int getType();

protected:
	int life;
	bool dead;
	int x, y;
	int w, h;
	int type; // enemy type
};

