#include "cPlayer.h"
#include "cScene.h"
#include "cBicho.h"


#pragma once

//Mesures tipo
#define x0 0
#define x1 33
#define y0 0
#define y1 31




//La imatge es img/nau_alpha.png
#define IMG_WIDTH 128
#define IMG_HEIGHT 128


class cProjectilEnemic
{
public:
	cProjectilEnemic(void);
	~cProjectilEnemic(void);

	bool getActive();
	void setActive(bool act);

	int getDirection();
	void setDirection(int dir);

	void setDamage(int damage);
	int getDamage();

	int getType();
	void setType(int type);

	void getPosition(int *posx, int *posy);
	void setPosition(int x, int y);

	void DrawRect(int tex_id);

	void setDimensions(int w, int h);

	void GetArea(cRect * rc);

	bool canMove();

	bool isCollision(int(*map)[SCENE_HEIGHT][SCENE_WIDTH]);

	bool Collapsed(int x, int y);

private:
	bool active;
	int x, y;
	bool out_map; // 1 = desapareix
	int direction; // 1 = esquerra / 2 = dreta
	int type;	// tipus de projectils
	int w, h; //dimensions
	int delay;
	int damage;
};
