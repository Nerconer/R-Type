#include "Globals.h"

#pragma once

#define TILE_SIZE		16
#define BLOCK_SIZE		16

class cHelper {

	int static w_tile, h_tile;

public:

	
	cHelper();
	~cHelper();

	int transformCToN(FILE *fd);
	void getXandY(int tile, int w, int h, float *x, float *y);
	float getDesc(int block_size, int dimen);
	void setWandH(int w, int h);
	void getWandW(int *w, int *h);
};