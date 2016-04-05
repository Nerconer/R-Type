#pragma once

#include "cScene.h"
#include "cPlayer.h"
#include "cData.h"
#include "cProjectil.h"
#include "cMenu.h"
#include "cEnemy.h"

#define GAME_WIDTH	640
#define GAME_HEIGHT 480

#define PANEL_SIZE 50

#define NUM_MISSILES 252
#define NUM_ENEMIES 52

#define KEY_SPACE 32
#define KEY_A_MAJ 65
#define KEY_A_MIN 97
#define KEY_INTRO 13

#define DELAY_PROJ 200
#define SPEED_PROJ 32
#define TIME_MEDIUM_SHOT 200
#define TIME_STRONG_SHOT 2000
#define TIME_A_BUTTON 3000

#define SPEED_ENEMY1 3
#define SPEED_ENEMY2 1
#define SPEED_ENEMY3 2


class cGame
{
public:
	cGame(void);
	virtual ~cGame(void);

	bool Init();
	bool InitMenu();
	bool InitLevelPlay();
	bool Loop();
	void Finalize();

	//Input
	void ReadKeyboard(unsigned char key, int x, int y, bool press);
	void ReadMouse(int button, int state, int x, int y);
	//Process
	bool Process();
	bool ProcessMenu();
	//Output
	void Render();

	void RenderGUI();

	void ActivateProjectil(int x, int y, int type);

	void RenderProjectils(int textId);

	void RenderMenu();

	void printOptions();

	void selectLevel();

	void pintaNauMenu(int id, int id1);

	bool generateEnemies(int level);

	bool isVisible(int x);

	void RenderEnemies(int id1, int id2, int id3);

	cPlayer getPlayer();

private:
	unsigned char keys[256];
	cScene Scene;
	cPlayer Player;
	cData Data;
	cMenu Menu;
	cProjectil projectils[NUM_MISSILES];
	bool buttonA;
	int startTimeProj;
	int lastArrowTime;
	int timeButtonAInitial;
	int timeButtonAFinal;
	int level;
	bool fullscreen;

	bool menuAnimation;
	float posy1, posy2; // animacio inici titol
	bool blinkAnim;
	int loopsBlink;

	int delayTextMenu;
	int delayNauMenu;

	int oscilation;
	bool upMenu; // nau puja

	int delayOscilationMenu;

	int engineAnimMenu;
	int delayEngineAnimMenu;

	cEnemy enemies[NUM_ENEMIES];

	
};
