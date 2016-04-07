
#include "cPlayer.h"

cPlayer::cPlayer() {

	this->backWindow = false;
	posTexture p;

	isKilledByRight = false;
	steps = 0;
	hurted = 0;

	nauSelected = 4;


	// NAU DEFAULT

	//STATE_LOOKRIGHT

	p.xo = 67.0f;
	p.yo = 2.0f;
	p.xf = 99.0f;
	p.yf = 16.0f;


	textSeq[0][0] = p;

	//STATE_WALKUP (1)

	p.xo = 99.0f;
	p.yo = 2.0f;
	p.xf = 133.0f;
	p.yf = 16.0f;


	textSeq[0][1] = p;
	//STATE_WALKUP (2)

	p.xo = 134.0f;
	p.yo = 2.0f;
	p.xf = 166.0f;
	p.yf = 16.0f; 

	textSeq[0][2] = p;

	//STATE_WALKDOWN (1)

	p.xo = 33.0f;
	p.yo = 2.0f;
	p.xf = 67.0f;
	p.yf = 16.0f;


	textSeq[0][3] = p;

	//STATE_WALKDOWN (2)

	p.xo = 0.0f;
	p.yo = 1.0f;
	p.xf = 34.0f;
	p.yf = 16.0f;

	textSeq[0][4] = p;


	//NAU 2

	//STATE_LOOKRIGHT

	p.xo = 67.0f;
	p.yo = 18.0f;
	p.xf = 99.0f;
	p.yf = 34.0f;


	textSeq[1][0] = p;

	//STATE_WALKUP (1)

	p.xo = 99.0f;
	p.yo = 18.0f;
	p.xf = 133.0f;
	p.yf = 34.0f;


	textSeq[1][1] = p;
	//STATE_WALKUP (2)

	p.xo = 134.0f;
	p.yo = 18.0f;
	p.xf = 166.0f;
	p.yf = 34.0f;

	textSeq[1][2] = p;

	//STATE_WALKDOWN (1)

	p.xo = 33.0f;
	p.yo = 18.0f;
	p.xf = 67.0f;
	p.yf = 34.0f;


	textSeq[1][3] = p;

	//STATE_WALKDOWN (2)

	p.xo = 0.0f;
	p.yo = 18.0f;
	p.xf = 34.0f;
	p.yf = 34.0f;

	textSeq[1][4] = p;

	//NAU 3

	//STATE_LOOKRIGHT

	p.xo = 67.0f;
	p.yo = 35.0f;
	p.xf = 99.0f;
	p.yf = 51.0f;


	textSeq[2][0] = p;

	//STATE_WALKUP (1)

	p.xo = 99.0f;
	p.yo = 35.0f;
	p.xf = 133.0f;
	p.yf = 51.0f;


	textSeq[2][1] = p;
	//STATE_WALKUP (2)

	p.xo = 134.0f;
	p.yo = 35.0f;
	p.xf = 166.0f;
	p.yf = 51.0f;

	textSeq[2][2] = p;

	//STATE_WALKDOWN (1)

	p.xo = 33.0f;
	p.yo = 35.0f;
	p.xf = 67.0f;
	p.yf = 51.0f;


	textSeq[2][3] = p;

	//STATE_WALKDOWN (2)

	p.xo = 0.0f;
	p.yo = 35.0f;
	p.xf = 34.0f;
	p.yf = 51.0f;

	textSeq[2][4] = p;

	//NAU 4

	//STATE_LOOKRIGHT

	p.xo = 67.0f;
	p.yo = 52.0f;
	p.xf = 99.0f;
	p.yf = 68.0f;


	textSeq[3][0] = p;

	//STATE_WALKUP (1)

	p.xo = 99.0f;
	p.yo = 52.0f;
	p.xf = 133.0f;
	p.yf = 68.0f;


	textSeq[3][1] = p;
	//STATE_WALKUP (2)

	p.xo = 134.0f;
	p.yo = 52.0f;
	p.xf = 166.0f;
	p.yf = 68.0f;

	textSeq[3][2] = p;

	//STATE_WALKDOWN (1)

	p.xo = 33.0f;
	p.yo = 52.0f;
	p.xf = 67.0f;
	p.yf = 68.0f;


	textSeq[3][3] = p;

	//STATE_WALKDOWN (2)

	p.xo = 0.0f;
	p.yo = 52.0f;
	p.xf = 34.0f;
	p.yf = 68.0f;

	textSeq[3][4] = p;

	//NAU 5

	//STATE_LOOKRIGHT

	p.xo = 67.0f;
	p.yo = 69.0f;
	p.xf = 99.0f;
	p.yf = 86.0f;


	textSeq[4][0] = p;

	//STATE_WALKUP (1)

	p.xo = 99.0f;
	p.yo = 69.0f;
	p.xf = 133.0f;
	p.yf = 86.0f;


	textSeq[4][1] = p;
	//STATE_WALKUP (2)

	p.xo = 134.0f;
	p.yo = 69.0f;
	p.xf = 166.0f;
	p.yf = 86.0f;

	textSeq[4][2] = p;

	//STATE_WALKDOWN (1)

	p.xo = 33.0f;
	p.yo = 69.0f;
	p.xf = 67.0f;
	p.yf = 86.0f;


	textSeq[4][3] = p;

	//STATE_WALKDOWN (2)

	p.xo = 0.0f;
	p.yo = 69.0f;
	p.xf = 34.0f;
	p.yf = 86.0f;

	textSeq[4][4] = p;


	this->lives = 3;
}
cPlayer::~cPlayer(){}

void cPlayer::setBackWindow(bool b)
{
	this->backWindow = b;
}

void cPlayer::setNauSelected(int nauSelected)
{
	this->nauSelected = nauSelected;
}

int cPlayer::getNauSelected()
{
	return 0;
}

bool cPlayer::getBackWindow() 
{
	return this->backWindow;
}

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
		p = textSeq[nauSelected][1];
	}
	else if (stopDown) {
		++cont;
		if (cont == FRAME_DELAY) {
			stopDown = false;
			cont = 0;
		}
		p = textSeq[nauSelected][3];
	}
	else {

		switch (GetState())
		{
		case STATE_LOOKRIGHT:
		//	SetWidthHeight(25 * 2, 11 * 2);
			p = textSeq[nauSelected][0];
			break;
		case STATE_WALKUP:
			p = textSeq[nauSelected][1 + GetFrame()];
			if (GetFrame() != 1) {
			//	SetWidthHeight(25 * 2, 11 * 2);
				NextFrame(2);
			}
			//else SetWidthHeight(25 * 2, 16 * 2); 
			break;
		case STATE_WALKDOWN:
			//SetWidthHeight(25 * 2, 14 * 2);
			p = textSeq[nauSelected][3 + GetFrame()];
			if (GetFrame() != 1) NextFrame(2); break;

		}
	}


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

	cScene Scene;
	if (Scene.velocitat < (SCENE_WIDTH*TILE_SIZE - 640)) {
		int xold = x;
		bool advance = true;
		if (steps >= 1) {
			steps = 0;
			x += 1;
			if (CollidesMapWall(&Scene.map, true)) {
				x = xold;
				advance = false;
				//Si xoca
				if (!isKilledByRight) 
					lives -= 1;
				//else isKilledByRight = false;

			}
		}
		if (advance) steps += 0.5;
	}
}

int cPlayer::getLives()
{
	return this->lives;
}


void cPlayer::setLives(int lives)
{
	if (this->lives > lives) hurted = 100;
	this->lives = lives;
}

int cPlayer::getHurted() {
	return hurted;
}
void cPlayer::setHurted(int hurted) {
	this->hurted = hurted;
}

bool cPlayer::getIsKilledByRight()
{
	return isKilledByRight;
}

void cPlayer::setIsKilledByRight(bool killed)
{
	isKilledByRight = killed;
}

