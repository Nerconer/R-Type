
#include "cPlayer.h"

cPlayer::cPlayer() {
	posTexture p;
	textSeq = vector<posTexture>(5);

	//STATE_LOOKRIGHT
	/*p.xo = 3.0f;
	p.yo = 34.0f;
	p.xf = 28.0f;
	p.yf = 49.0f;*/

	p.xo = 166.0f;
	p.yo = 1.0f;
	p.xf = 199.0f;
	p.yf = 16.0f;


	textSeq[0] = p;

	//STATE_WALKUP (1)
	/*
	p.xo = 38.0f;
	p.yo = 34.0f;
	p.xf = 63.0f;
	p.yf = 49.0f;*/

	p.xo = 199.0f;
	p.yo = 1.0f;
	p.xf = 232.0f;
	p.yf = 16.0f; 


	textSeq[1] = p;
	//STATE_WALKUP (2)
	/*p.xo = 70.0f;
	p.yo = 3.0f;
	p.xf = 95.0f;
	p.yf = 48.0f;*/

	p.xo = 231.0f;
	p.yo = 1.0f;
	p.xf = 265.0f;
	p.yf = 16.0f; 

	textSeq[2] = p;

	//STATE_WALKDOWN (1)
/*	p.xo = 168.0f;
	p.yo = 56.0f;
	p.xf = 193.0f;
	p.yf = 69.0f;*/

	p.xo = 132.0f;
	p.yo = 1.0f;
	p.xf = 166.0f;
	p.yf = 16.0f;


	textSeq[3] = p;

	//STATE_WALKDOWN (2)
	/*
	p.xo = 136.0f;
	p.yo = 56.0f;
	p.xf = 161.0f;
	p.yf = 71.0f;
	*/

	p.xo = 99.0f;
	p.yo = 1.0f;
	p.xf = 133.0f;
	p.yf = 16.0f;

	textSeq[4] = p;

	this->lives = 3;
}
cPlayer::~cPlayer(){}

posTexture p;
int cont = 0;

void cPlayer::Draw(int tex_id)
{	
	//float xo,yo,xf,yf;

	if (stopUp) {
	//	SetWidthHeight(25 * 2, 14 * 2);
		++cont;
		if (cont == FRAME_DELAY) {
			stopUp = false;
			cont = 0;
		}
		p = textSeq[1];
	}
	else if (stopDown) {
		++cont;
		if (cont == FRAME_DELAY) {
			stopDown = false;
			cont = 0;
		}
		p = textSeq[3];
	}
	else {

		switch (GetState())
		{
		case STATE_LOOKRIGHT:
		//	SetWidthHeight(25 * 2, 11 * 2);
			p = textSeq[0];
			break;
		case STATE_WALKUP:
			p = textSeq[1 + GetFrame()];
			if (GetFrame() != 1) {
			//	SetWidthHeight(25 * 2, 11 * 2);
				NextFrame(2);
			}
			//else SetWidthHeight(25 * 2, 16 * 2); 
			break;
		case STATE_WALKDOWN:
			//SetWidthHeight(25 * 2, 14 * 2);
			p = textSeq[3 + GetFrame()];
			if (GetFrame() != 1) NextFrame(2); break;

		}
	}

	/*switch(GetState())
	{
		//1
		case STATE_LOOKLEFT:	xo = 0.2f;	yo = 0.008f;
								break;
		//4
		case STATE_LOOKRIGHT:	xo = 0.2f;	yo = 0.008f;
								break;
		//1..3
		case STATE_WALKLEFT:	xo = 0.2f;	yo = 0.008f;
								//NextFrame(3);
								break;
		//4..6
		case STATE_WALKRIGHT:	xo = 0.2f;	yo = 0.008f;
								//NextFrame(3);
								break;
	}*/
	//xf = xo + 0.045f;
	//yf = yo + 0.040f;

	//DrawRect(tex_id,xo,yo,xf,yf);
	DrawRect(tex_id,p.xo/ IMG_WIDTH_PLAYER,p.yo/ IMG_HEIGHT_PLAYER,p.xf/ IMG_WIDTH_PLAYER,p.yf/ IMG_HEIGHT_PLAYER);
}

void cPlayer::Shoot(int type)
{
	if(type == 0) mciSendString("play sound/Lazer1.1.mp3",NULL,0,NULL);
	else if(type == 1) mciSendString("play sound/Blast3.mp3",NULL,0,NULL);
	else if(type == 2) mciSendString("play sound/LaserFort.aif",NULL,0,NULL);
	else{}
}

void cPlayer::Advance()
{
	//if ()
}

int cPlayer::getLives()
{
	return this->lives;
}

