#include "cHelper.h"

cHelper::cHelper() {}
cHelper::~cHelper(){}

int cHelper::w_tile, cHelper::h_tile;

int cHelper::transformCToN(FILE *fd) {
	char c;
	int result = 0;
	fscanf(fd, "%c", &c);
	while (c != ',') {
		result = result * 10 + (c - 48);
		fscanf(fd, "%c", &c);
	}
	return result;
}

void cHelper::getXandY(int tile, int w, int h, float *x, float *y) {

	// w / TILE_SIZE
	int num_tiles = w / TILE_SIZE;

	tile = tile - 1;

	(*y) = ((tile/num_tiles) * TILE_SIZE);
	(*x) = ((tile%num_tiles) * TILE_SIZE);

	(*y) = (*y) / float(h);
	(*x) = (*x) / float(w);


}

float cHelper::getDesc(int block_size, int dimen) {
	return float(block_size) / float(dimen);
}


void cHelper::setWandH(int w, int h) {
	cHelper::w_tile = w;
	cHelper::h_tile = h;
}

void cHelper::getWandW(int* w, int* h)
{
	(*w) = cHelper::w_tile;
	(*h) = cHelper::h_tile;
}

