#include "cExplosion.h"


cExplosion::cExplosion(void)
{
}

cExplosion::cExplosion(bool act, int currAnim, float x, float y, int type, int delay)
{
	this->active = act;
	this->currAnim = currAnim;
	this->x = x;
	this->y = y;
	this->type = type; 
	this->setType(type);
	this->delayAnim = delay;
}

void cExplosion::setActive(bool a)
{
	this->active = a;
}

bool cExplosion::getActive()
{
	return this->active;
}

void cExplosion::setCurrAnim(int anim)
{
	this->currAnim = anim;
}

int cExplosion::getCurrAnim()
{
	return this->currAnim;
}

void cExplosion::setType(int type)
{
	this->type = type;
	if(this->type == 1) {
		p.xo = 128;
		p.xf = 160;
		p.yo = 1;
		p.yf = 33;
	}
	//else if(){}
}

int cExplosion::getType()
{
	return this->type;
}

void cExplosion::setPosXY(int x,int y)
{
	this->x = x;
	this->y = y;
}

void cExplosion::getPosXY(int *x, int *y)
{
	*x = this->x;
	*y = this->y;
}

float calculeOffset(int w, int anim)
{
	if(anim == 0) return 0.0f;
	else return (anim) * 33; 
}

void cExplosion::Draw(int id)
{
	float x, y, w, h, offset;

	x = this->x;
	y = this->y;

	w = (this->p.xf) - (this->p.xo);
	h = (this->p.yf) - (this->p.yo);

	if (this->delayAnim == EXPLOSION1_TRANSITION_SPEED) {
		this->delayAnim = 0;
		this->currAnim++;
	}
	else this->delayAnim++;
	
	offset = calculeOffset(w, this->currAnim);

	h*=2;
	w*=2;

	float xo, yo, xf, yf;

	if (this->type == 1) {

			offset /= IMG_WIDTH_EXPLOSION1;
			
			xo = this->p.xo / IMG_WIDTH_EXPLOSION1;
			xf = this->p.xf / IMG_WIDTH_EXPLOSION1;
			yo = this->p.yo / IMG_HEIGHT_EXPLOSION1;
			yf = this->p.yf / IMG_HEIGHT_EXPLOSION1;

			glEnable(GL_TEXTURE_2D);
			glColor4f(1.0, 1.0, 1.0, 1.0);
			glBindTexture(GL_TEXTURE_2D, id);
			glBegin(GL_QUADS);
			glTexCoord2f(xo + offset, yo);	glVertex2d(x, y);
			glTexCoord2f(xf + offset, yo);	glVertex2d((x + w), y);
			glTexCoord2f(xf + offset, yf);	glVertex2d((x + w), (y + h));
			glTexCoord2f(xo + offset, yf);	glVertex2d(x, (y + h));
			glEnd();
			glDisable(GL_TEXTURE_2D);
	}

	
	// type 1; 4 animations
	if(this->type == 1 && this->currAnim == 6) {
		this->active = false;
	}


}

cExplosion::~cExplosion(void)
{
}
