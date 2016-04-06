#include "cBoss.h"


cBoss::cBoss(void)
{
	this->dead = false;
	this->animAct = 0;
	this->delayAnim = 0;
	this->lastShot = 0;
	this->dirAnim = true;
	this->up = true;
	this->numIterUp = 0;
}

int calculeFinalOffset(int w, int anim, int type)
{
	if(anim == 0) return 0;
	if(type == 1) return (anim)*162;
	if(type == 2) return (anim)*65;
}

void cBoss::setType1(int type)
{
	this->type = type;
	posTexture p;
	seqEnemy = vector<posTexture>(1);

	if(type == 1) {	
		p.xo = 350;
		p.xf = 512;
		p.yo = 1710;
		p.yf = 1916;
	}
	else if(type == 2) {
		p.xo = 130;
		p.xf = 195;
		p.yo = 1;
		p.yf = 49;
	}
	seqEnemy[0] = p;
}

void cBoss::Draw1(int id) 
{
	float x, y, w, h;
	float offset;

	x = this->x;
	y = this->y;
	w = this->w;
	h = this->h;

	int transSpeed = 0;
	if(type == 1) {
		transSpeed = BOSS1_TRANSITION_SPEED;
	}
	else if(type == 2) {
		transSpeed = BOSS2_TRANSITION_SPEED;
	}

	if (this->delayAnim == transSpeed) {
		this->delayAnim = 0;
		//++animAct;
		
		if (this->animAct == 2 && dirAnim == true) {
			dirAnim = false;
			//this->animAct--;
		}
		else if(this->animAct == 0 && dirAnim == false) {
			dirAnim = true;
		}
		else if(!dirAnim) --animAct;
		else if(dirAnim) ++animAct;
		
	}
	else this->delayAnim++;

	offset = calculeFinalOffset(this->w, this->animAct, this->type);

	float xo, yo, xf, yf;

	if (this->type == 1) {

		offset /= IMG_WIDTH_BOSS1;

		xo = this->seqEnemy[0].xo / IMG_WIDTH_BOSS1;
		xf = this->seqEnemy[0].xf / IMG_WIDTH_BOSS1;
		yo = this->seqEnemy[0].yo / IMG_HEIGHT_BOSS1;
		yf = this->seqEnemy[0].yf / IMG_HEIGHT_BOSS1;

		glEnable(GL_TEXTURE_2D);
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glBindTexture(GL_TEXTURE_2D, id);
		glBegin(GL_QUADS);
			glTexCoord2f(xo - offset, yf);	glVertex2d(x, y);
			glTexCoord2f(xo - offset, yo);	glVertex2d(x, y + h);
			glTexCoord2f(xf - offset, yo);	glVertex2d((x + w), (y + h));
			glTexCoord2f(xf - offset, yf);	glVertex2d((x + w), y);
			
			/*glTexCoord2f(xo - offset, yf);	glVertex2d(150, 115);
			glTexCoord2f(xo - offset, yo);	glVertex2d(150, 115 + h);
			glTexCoord2f(xf - offset, yo);	glVertex2d((150 + w), (115 + h));
			glTexCoord2f(xf - offset, yf);	glVertex2d((150 + w), 115)^*/
		glEnd();
		glDisable(GL_TEXTURE_2D);
	}

	if (this->type == 2) {

		offset /= IMG_WIDTH_BOSS2;

		xo = this->seqEnemy[0].xo / IMG_WIDTH_BOSS2;
		xf = this->seqEnemy[0].xf / IMG_WIDTH_BOSS2;
		yo = this->seqEnemy[0].yo / IMG_HEIGHT_BOSS2;
		yf = this->seqEnemy[0].yf / IMG_HEIGHT_BOSS2;

		glEnable(GL_TEXTURE_2D);
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glBindTexture(GL_TEXTURE_2D, id);
		glBegin(GL_QUADS);
			glTexCoord2f(xo - offset, yf);	glVertex2d(x, y - h);
			glTexCoord2f(xo - offset, yo);	glVertex2d(x, y);
			glTexCoord2f(xf - offset, yo);	glVertex2d((x + w), (y));
			glTexCoord2f(xf - offset, yf);	glVertex2d((x + w), y - h);
			glEnd();
		glDisable(GL_TEXTURE_2D);
	}

}

void cBoss::setUp(bool up)
{
	this->up = up;
}

bool cBoss::getUp()
{
	return this->up;
}

void cBoss::setNumIterUp(int num)
{
	this->numIterUp = num;
}

int cBoss::getNumIterUp()
{
	return this->numIterUp;
}

cBoss::~cBoss(void)
{
}
