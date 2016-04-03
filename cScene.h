#pragma once

#include "cTexture.h"

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

	int static map[SCENE_HEIGHT][SCENE_WIDTH]; //scene

	float static velocitat;
	float static velocitatBackground;
	

	void DrawBackground(int text_id);

private:
	
	int id_DL_background;								//actual level display list
	int id_DL_level;

	
};
