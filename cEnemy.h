#pragma once

#include "cTexture.h"
#include "Globals.h"
#include "posTexture.h"
#include "cProjectilEnemic.h"
#include "cBicho.h"

#define LIFE_ENEMY_1 100
#define LIFE_ENEMY_2 500

#define IMG_WIDTH_ENEMY1 533
#define IMG_HEIGHT_ENEMY1 36

#define IMG_WIDTH_ENEMY2 398
#define IMG_HEIGHT_ENEMY2 100

#define IMG_WIDTH_ENEMY3 200
#define IMG_HEIGHT_ENEMY3 34

#define TIME_BETWEEN_SHOOTS_EN1 300
#define TIME_BETWEEN_SHOOTS_EN2 500
#define TIME_BETWEEN_SHOOTS_EN3 400

#define NUM_MISSILES 10

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

	void setHurted(bool hurted);
	bool getHurted();

	void Draw(int idText);

	boolean isCollision(int x, int y);

	void GetArea(cRect * rc);

	bool Collides(cRect * rc);

	vector<cProjectilEnemic> projectils;

	int getActiveMissiles();
	void setActiveMissiles(int count);


protected:
	int life;
	bool dead;
	float x, y;
	float w, h;
	int type; // enemy type
	int animAct;	// state of the animation
	int delayAnim;
	int lastShot;
	bool hurted;

	int activeMissiles;


	vector<posTexture> seqEnemy;
};

