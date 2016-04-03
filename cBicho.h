#pragma once

#include "cTexture.h"
#include "Globals.h"
#include "posTexture.h"
#include "cScene.h"

#define FRAME_DELAY		10
#define STEP_LENGTH		4
#define JUMP_HEIGHT		96
#define JUMP_STEP		4

#define STATE_LOOKLEFT		0
#define STATE_LOOKRIGHT		1
#define STATE_WALKUP		2
#define STATE_WALKDOWN		3

#define VELOCITAT_PLAYER	1

class cRect
{
public:
	int left,top,
		right,bottom;
};

class cBicho
{
public:
	cBicho(void);
	cBicho(int x,int y,int w,int h);
	~cBicho(void);

	void SetPosition(int x,int y);
	void GetPosition(int *x,int *y);
	void SetTile(int tx,int ty);
	void GetTile(int *tx,int *ty);
	void SetWidthHeight(int w,int h);
	void GetWidthHeight(int *w,int *h);

	bool Collides(cRect *rc);
	bool CollidesMapWall(int (*map)[SCENE_HEIGHT][SCENE_WIDTH], bool right);
	bool CollidesMapFloor(int (*map)[SCENE_HEIGHT][SCENE_WIDTH], bool up);
	void GetArea(cRect *rc);
	void DrawRect(int tex_id, float xo, float yo, float xf, float yf);

	void MoveRight(int (*map)[SCENE_HEIGHT][SCENE_WIDTH]);
	void MoveLeft(int (*map)[SCENE_HEIGHT][SCENE_WIDTH]);
	void MoveUp(int (*map)[SCENE_HEIGHT][SCENE_WIDTH]);
	void MoveDown(int (*map)[SCENE_HEIGHT][SCENE_WIDTH]);
	void Stop();

	virtual void Shoot();
	//void Logic(int *map);

	int  GetState();
	void SetState(int s);

	void NextFrame(int max);
	int  GetFrame();
	
protected:
	int x,y;
	int w,h;
	int state;

	bool jumping;
	int jump_alfa;
	int jump_y;

	int seq,delay;

	vector<posTexture> textSeq;

	bool stopUp, stopDown;
};
