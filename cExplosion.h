#pragma once

#include "posTexture.h"
#include "cTexture.h"
#include "Globals.h"

#define IMG_WIDTH_EXPLOSION1 652
#define IMG_HEIGHT_EXPLOSION1 164

#define EXPLOSION1_TRANSITION_SPEED 3

class cExplosion
{
public:
	cExplosion(void);
	cExplosion(bool act, int currAnim, float x, float y, int type, int delay);
	~cExplosion(void);

	void setActive(bool a);
	bool getActive();

	void setCurrAnim(int anim);
	int getCurrAnim();

	void setType(int type);
	int getType();

	void setPosXY(int x,int y);
	void getPosXY(int *x, int *y);

	void Draw(int id);

private:
	float x, y;
	int type;
	int currAnim;
	bool active;
	posTexture p;
	int delayAnim;
};

