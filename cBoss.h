#pragma once
#include "cEnemy.h"

#define LIFE_BOSS_1 5000
#define LIFE_BOSS_2 10000

#define IMG_WIDTH_BOSS1 669
#define IMG_HEIGHT_BOSS1 2085

#define IMG_WIDTH_BOSS2 392
#define IMG_HEIGHT_BOSS2 50

#define TIME_BETWEEN_SHOOTS_BOSS1 300
#define TIME_BETWEEN_SHOOTS_BOSS2 500

#define BOSS1_TRANSITION_SPEED 30
#define BOSS2_TRANSITION_SPEED 8

#define ITERATIONS_UPDOWN 200

class cBoss: public cEnemy
{
public:
	cBoss(void);
	~cBoss(void);

	void Draw1(int id);

	void setType1(int type);

	bool Collides(cRect * rc);

	void setUp(bool up);
	bool getUp();

	void setNumIterUp(int num);
	int getNumIterUp();

private:

	bool dirAnim; // true -> esquerra; false -> dreta
	bool up; // boss 2
	float numIterUp;

};

