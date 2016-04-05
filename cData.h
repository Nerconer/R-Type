#pragma once

#include "cTexture.h"
#include "Globals.h"

//Image array size
#define NUM_IMG		15

//Image identifiers
#define IMG_BLOCKS	0
#define IMG_PLAYER	1
#define IMG_PLAYER1 2
#define IMG_MISSILE 3
#define IMG_TAIL_MISSILE 4
#define IMG_SPACE 5
#define IMG_MENU_TITOL 6
#define IMG_MENU_SELECTED 7
#define IMG_TILES_001 8
#define IMG_TILES_002 9
#define IMG_SPACE_2 10
#define IMG_ENEMY1 11
#define IMG_ENEMY2 12
#define IMG_ENEMY3 13
#define IMG_MISSILE_ENEMIC 14

/*
#define IMG_ENEMY1	2
//#define IMG_ENEMY2	3
#define IMG_SHOOT	4
...
*/

class cData
{
public:
	cData(void);
	~cData(void);

	int  GetID(int img);
	void GetSize(int img,int *w,int *h);
	bool LoadImage(int img,char *filename,int type = GL_RGBA);

private:
static cTexture texture[NUM_IMG];
};
