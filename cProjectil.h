#include "cPlayer.h"
#include "cScene.h"


#pragma once

//Mesures tipo0
#define x0_Tipo0 247
#define xf_Tipo0 261
#define y0_Tipo0 89
#define yf_Tipo0 94

//Mesures tipo1
#define x0_Tipo1 231
#define xf_Tipo1 264
#define y0_Tipo1 119
#define yf_Tipo1 133

//Mesures tipo2
#define x0_Tipo2 183
#define xf_Tipo2 264
#define y0_Tipo2 169
#define yf_Tipo2 186

#define x0_cua0 -1
#define xf_cua0 -1
#define y0_cua0 -1
#define yf_cua0 -1


//La imatge es img/nau_alpha.png
#define IMG_WIDTH 532
#define IMG_HEIGHT 372


class cProjectil
{
public:
	cProjectil(void);
	~cProjectil(void);

	bool getActive();
	void setActive(bool act);

	int getDirection();
	void setDirection(int dir);

	int getType();
	void setType(int type);

	void getPosition(int *posx, int *posy);
	void setPosition(int x, int y);

	void DrawRect(int tex_id,float xo,float yo,float xf,float yf,bool tail);
	void Draw(int id);

	void setDimensions(int w, int h);

	bool canMove();

private:
	bool active;
	int x, y;
	bool out_map; // 1 = desapareix
	int direction; // 1 = esquerra / 2 = dreta
	int type;	// tipus de projectils
	int w, h; //dimensions
	int delay;
	int damage;
};

