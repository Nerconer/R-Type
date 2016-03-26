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

bool cProjectil::canMove() {
	if (delay == 2) {
		delay = 0;
		return true;
	}
	++delay;
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

int cProjectil::getType()
{
	return type;
}

void cProjectil::setType(int type)
{
	this->type = type;
	if(type == 0) this->damage = 100;
	else if(type == 1) this->damage = 300;
	else if(type == 2) this->damage = 1500;
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


	screen_x = posx + SCENE_Xo;
	screen_y = posy + SCENE_Yo + (BLOCK_SIZE - TILE_SIZE);

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