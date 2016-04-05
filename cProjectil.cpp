#include "cProjectil.h"
#include "cTexture.h"
#include "cGame.h"


cProjectil::cProjectil(void)
{
	active = false;
	delay = 0;
}

void cProjectil::setDimensions(int w, int h) {
	this->w = w;
	this->h = h;

}

void cProjectil::GetArea(cRect *rc)
{
	(*rc).left = x;
	(*rc).right = x + w;
	(*rc).bottom = y;
	(*rc).top = y + h;
}

bool cProjectil::canMove() {
	if (delay == 2) {
		delay = 0;
		return true;
	}
	++delay;
	return false;
}

bool cProjectil::Collapsed(int x, int y) {

	cRect Rect;
	GetArea(&Rect);
	if (Rect.left <= x && Rect.right >= x) {
		return true;
	}
	return false;

}


cProjectil::~cProjectil(void)
{
}

bool cProjectil::getActive()
{
	return active;
}
	
void cProjectil::setActive(bool act) 
{
	active = act;
	out_map = false;
}

int cProjectil::getDirection()
{
	return direction;
}

void cProjectil::setDirection(int dir)
{
	direction = dir;
}

int cProjectil::getDamage()
{
	return damage;
}

int cProjectil::getType()
{
	return type;
}

void cProjectil::setType(int type)
{
	this->type = type;
	if(type == 0) this->damage = LIFE_ENEMY_1;
	else if(type == 1) this->damage = LIFE_ENEMY_1 * 3;
	else if(type == 2) this->damage = LIFE_ENEMY_1 * 15;
}

void cProjectil::getPosition(int *posx, int *posy)
{
	*posx = x;
	*posy = y;
}
	
void cProjectil::setPosition(int x, int y)
{
	this->x = x;
	this->y = y;
}

void cProjectil::DrawRect(int tex_id,float xo,float yo,float xf,float yf, bool tail)
{
	//x + WIDTH PLAYER
	int posx = this->x;
	int posy = this->y;
	if(!tail) {
		if(type == 0) {
			posx += 32;	//missil basic
			posy += 5;
		}
		else if(type == 1) {
			posx += 52;
			posy += 0;
		}
		else if(type == 2) {	
			posx += 52;
			posy += 0;
		}
	}
	else {
		posx += 14;
		posy += 2;
	}


	int screen_x, screen_y;

	xo = xo / IMG_WIDTH;
	xf = xf / IMG_WIDTH;

	yo = yo / IMG_HEIGHT;
	yf = yf / IMG_HEIGHT;


	screen_x = posx;
	screen_y = posy + (BLOCK_SIZE - TILE_SIZE);

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, tex_id);
	glBegin(GL_QUADS);
	glTexCoord2f(xo, yf);	glVertex2i(screen_x, screen_y);
	glTexCoord2f(xo, yo);	glVertex2i(screen_x, screen_y + h);
	glTexCoord2f(xf, yo);	glVertex2i(screen_x + w, screen_y + h);
	glTexCoord2f(xf, yf);	glVertex2i(screen_x + w, screen_y);


	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void cProjectil::Draw(int id)
{
	//type = 1;
	if(!out_map) {
		if(type == 0) {
			DrawRect(id, x0_Tipo0, y0_Tipo0, xf_Tipo0, yf_Tipo0, false);
		}
		else if(type == 1) {
			DrawRect(id, x0_Tipo1, y0_Tipo1, xf_Tipo1, yf_Tipo1, false);
		}
		else if(type == 2) {
			DrawRect(id, x0_Tipo2, y0_Tipo2, xf_Tipo2, yf_Tipo2, false);
		}
		else{}
	}
}

bool cProjectil::isCollision(int (*map)[SCENE_HEIGHT][SCENE_WIDTH]) {
	int tile_x, tile_y;
	int j;
	int width_tiles, height_tiles;
   

	tile_x = (x + 32) / TILE_SIZE;
	if (tile_x % TILE_SIZE != 0) tile_x += 1;
	tile_y = y / TILE_SIZE;
	width_tiles = w / TILE_SIZE;
	height_tiles = h / TILE_SIZE;
	if (width_tiles == 0 && tile_x % TILE_SIZE != 0) tile_x -= 1;
	if (height_tiles == 0) height_tiles = 1;

	tile_x += width_tiles;

	for (j = 0; j<height_tiles; j++)
	{
		if ((*map)[tile_y + j][tile_x] != 0)	return true;
	}

	return false;
	
}