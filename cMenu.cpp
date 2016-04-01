#include "cMenu.h"


cMenu::cMenu(void)
{
	this->selectedOption = 0;
	this->numOptions = 4;	// first menu
	this->typeMenu = MENU_PRINCIPAL;
}


cMenu::~cMenu(void)
{
}

void cMenu::increaseSO()
{
	this->selectedOption++;
	if(this->selectedOption == this->numOptions) this->selectedOption = 0;
}

void cMenu::descreaseSO()
{
	this->selectedOption--;
	if(this->selectedOption < 0) this->selectedOption = (this->numOptions) - 1;
}

void cMenu::setSO(int num){
	this->selectedOption = num;
}

int cMenu::getSO() 
{
	return this->selectedOption;
}

int cMenu::getTypeMenu()
{
	return this->typeMenu;
}

void cMenu::setTypeMenu(int type)
{
	this->typeMenu = type;
}

void cMenu::setNumOptions(int num)
{
	this->numOptions = num;
}