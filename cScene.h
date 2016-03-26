#pragma once

#include "cTexture.h"

#define SCENE_Xo		(2*TILE_SIZE)
#define SCENE_Yo		TILE_SIZE
#define SCENE_WIDTH		300
#define SCENE_HEIGHT	30

#define FILENAME		"level"
#define FILENAME_EXT	 ".txt"

#define TILE_SIZE		16
#define BLOCK_SIZE		16

class cScene
{
public:
	cScene(void);
	virtual ~cScene(void);

	bool LoadLevel(int level);
	void Draw(int tex_id);
	int *GetMap();
	vector<vector<int> > GetMap2();

	void DrawBackground(int text_id);

private:
	int map[SCENE_WIDTH * SCENE_HEIGHT];	//scene
	vector<vector<int> > map2;
	int id_DL_background;								//actual level display list
	int id_DL_level;

	float velocitat;
	float velocitatBackground;
};
