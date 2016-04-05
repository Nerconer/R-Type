#include "cEnemy.h"


cEnemy::cEnemy(void)
{
}

cEnemy::cEnemy(int x, int y, int type)
{
	this->x = x;
	this->y = y;
	this->type = type;
	this->dead = false;
	this->animAct = 0;
	this->delayAnim = 0;
	this->lastShot = 0;
}

bool cEnemy::isDead()
{
	return this->dead;
}
void cEnemy::setDead(bool dead)
{
	this->dead = dead;
}

void cEnemy::setPosXY(int x, int y)
{
	this->x = x;
	this->y = y;
}

void cEnemy::getPosXY(int *x, int *y)
{
	*x = this->x;
	*y = this->y;
}

void cEnemy::setWidthHeight(int w, int h)
{
	this->w = w;
	this->h = h;
}

void cEnemy::getWidthHeight(int *w, int *h)
{
	*w = this->w;
	*h = this->h;
}

int cEnemy::getLife()
{
	return life;
}

void cEnemy::setLife(int life)
{
	this->life = life;
}

boolean cEnemy::isCollision(int x, int y) {

	int bottom, top, right, left;

	right = this->x + w;
	left = this->x;
	top = this->y;
	bottom = this->y + h;

	if (x <= right && x >= left)
		if (y >= top && y <= bottom) return true;

	return false;


}


void cEnemy::GetArea(cRect *rc)
{
	(*rc).left = x;
	(*rc).right = x + w;
	(*rc).bottom = y;
	(*rc).top = y + h;
}

bool cEnemy::Collides(cRect *rc)
{
	int left, rigth, top, bottom;
	switch (this->type) {
	case 1:
		bottom = y;
		rigth = w + x;
		top = y + h;
		left = x;
		break;
	case 2:
		bottom = y - h;
		rigth = w + x;
		top = y;
		left = x;
		break;
	case 3:	// CODI INVENTAT PERQUE PETAVA AL DISPARAR AL NO INICIALITZAR 'right' (david)
		bottom = y - h;
		rigth = w + x;
		top = y;
		left = x;
		break;


	}
	return (rc->left < rigth) && (left < rc->right) && (rc->bottom < top) && (bottom < rc->top);
}


void cEnemy::setType(int type)
{
	this->type = type;
	posTexture p;
	if(this->type == 1) {
		seqEnemy = vector<posTexture>(1);	// 8 images
		p.xo = 235;
		p.xf = 268;
		p.yo = 5;
		p.yf = 30;

		/*p.xo = 235;
		p.xf = 257;
		p.yo = 5;
		p.yf = 30;*/
		seqEnemy[0] = p;

	}
	else if(this->type == 2) {
		seqEnemy = vector<posTexture>(1);	// 6 images
		p.xo = 165;
		p.xf = 199;
		p.yo = 1;
		p.yf = 27;
		seqEnemy[0] = p;
	}
	else if(this->type == 3) {
		seqEnemy = vector<posTexture>(1);	// 3 images
		p.xo = 66;
		p.xf = 100;
		p.yo = 0;
		p.yf = 32;
		seqEnemy[0] = p;
	}
}

int cEnemy::getType()
{
	return this->type;
}

int calculeFinalOffset(int w, int anim)
{
	if(anim == 0) return 0;
	return (anim)*33;
}

void cEnemy::Draw(int idText)
{
	float x, y, w, h;
	float offset;

	x = this->x;
	y = this->y;
	w = this->w;
	h = this->h;

	if(this->delayAnim == ENEMY1_TRANSITION_SPEED){
		this->delayAnim = 0;
		++animAct;
		if(this->type == 1) {
			if(this->animAct == 8) animAct = 0;
		}
		else if(this->type == 2) {
			if(this->animAct == 6) animAct = 0;
		}
		else if(this->type == 3) {
			if(this->animAct == 3) animAct = 0;
		}
	}
	else this->delayAnim++;

	offset = calculeFinalOffset(this->w, this->animAct);

	float xo, yo, xf, yf;

	if(this->type == 1) {
		
		offset /= IMG_WIDTH_ENEMY1;

		xo = this->seqEnemy[0].xo / IMG_WIDTH_ENEMY1;
		xf = this->seqEnemy[0].xf / IMG_WIDTH_ENEMY1;
		yo = this->seqEnemy[0].yo / IMG_HEIGHT_ENEMY1;
		yf = this->seqEnemy[0].yf / IMG_HEIGHT_ENEMY1;
		
		glLoadIdentity();
		glEnable(GL_TEXTURE_2D);
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glBindTexture(GL_TEXTURE_2D, idText);
		glBegin(GL_QUADS);
			glTexCoord2f(xo - offset, yf);	glVertex2d(x,		(y + h));
			glTexCoord2f(xf - offset, yf);	glVertex2d((x + w),	(y + h));
			glTexCoord2f(xf - offset, yo);	glVertex2d((x + w),	y);
			glTexCoord2f(xo - offset, yo);	glVertex2d(x,		y);
		glEnd();
		glDisable(GL_TEXTURE_2D);		
	}
	else if(this->type == 2) {
		offset /= IMG_WIDTH_ENEMY2;

		xo = this->seqEnemy[0].xo / IMG_WIDTH_ENEMY2;
		xf = this->seqEnemy[0].xf / IMG_WIDTH_ENEMY2;
		yo = this->seqEnemy[0].yo / IMG_HEIGHT_ENEMY2;
		yf = this->seqEnemy[0].yf / IMG_HEIGHT_ENEMY2;

		glLoadIdentity();
		glEnable(GL_TEXTURE_2D);
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glBindTexture(GL_TEXTURE_2D, idText);
		glBegin(GL_QUADS);
			glTexCoord2f(xo - offset, yo);	glVertex2d(x,		y);
			glTexCoord2f(xf - offset, yo);	glVertex2d((x + w),	y);
			glTexCoord2f(xf - offset, yf);	glVertex2d((x + w),	(y - h));
			glTexCoord2f(xo - offset, yf);	glVertex2d(x,		(y - h));
		glEnd();
		glDisable(GL_TEXTURE_2D);
	}
	else if(this->type == 3) {
		offset /= IMG_WIDTH_ENEMY3;

		xo = this->seqEnemy[0].xo / IMG_WIDTH_ENEMY3;
		xf = this->seqEnemy[0].xf / IMG_WIDTH_ENEMY3;
		yo = this->seqEnemy[0].yo / IMG_HEIGHT_ENEMY3;
		yf = this->seqEnemy[0].yf / IMG_HEIGHT_ENEMY3;

		glLoadIdentity();
		glEnable(GL_TEXTURE_2D);
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glBindTexture(GL_TEXTURE_2D, idText);
		glBegin(GL_QUADS);
			glTexCoord2f(xo - offset, yo);	glVertex2d(x,		y);
			glTexCoord2f(xf - offset, yo);	glVertex2d((x + w),	y);
			glTexCoord2f(xf - offset, yf);	glVertex2d((x + w),	(y - h));
			glTexCoord2f(xo - offset, yf);	glVertex2d(x,		(y - h));
		glEnd();
		glDisable(GL_TEXTURE_2D);
	}

}

cEnemy::~cEnemy(void)
{
}
