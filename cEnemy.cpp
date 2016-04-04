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

void cEnemy::getPosXY(int x, int y)
{
	x = this->x;
	y = this->y;
}

void cEnemy::setWidthHeight(int w, int h)
{
	this->w = w;
	this->y = y;
}

void cEnemy::getWidthHeight(int w, int h)
{
	w = this->w;
	h = this->h;
}

int cEnemy::getLife()
{
	return life;
}

void cEnemy::setLife(int life)
{
	this->life = life;
}

void cEnemy::setType(int type)
{
	this->type = type;
}

int cEnemy::getType()
{
	return this->type;
}

cEnemy::~cEnemy(void)
{
}
