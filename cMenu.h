#pragma once


#define MENU_PRINCIPAL 1
#define MENU_INSTR 2
#define MENU_CR 3
#define MENU_SELECT_LEVEL 4


class cMenu
{
public:
	cMenu(void);
	~cMenu(void);

	void increaseSO();
	void descreaseSO();

	int getSO();
	void setSO(int num);

	int getTypeMenu();
	void setTypeMenu(int type);

	void setNumOptions(int num);

private:
	int selectedOption;	// 0 = Play; 1 = Instructions; 2 = Credits
	int numOptions;
	int typeMenu;
};

