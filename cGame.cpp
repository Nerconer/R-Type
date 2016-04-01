#include "cGame.h"
#include "Globals.h"

bool buttonA = false; // true -> boto 'A' apretat

cGame::cGame(void)
{
	level = 0;
}

cGame::~cGame(void)
{
}

bool cGame::Init()
{
	bool res=true;

	//Graphics initialization
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,GAME_WIDTH,0,GAME_HEIGHT,0,1);
	glMatrixMode(GL_MODELVIEW);
	
	glAlphaFunc(GL_GREATER, 0.05f);
	glEnable(GL_ALPHA_TEST);

	if(level == 0) {
		//PlaySound();
		res = Data.LoadImage(IMG_MENU_TITOL, "img/titolRtype.png", GL_RGBA);
		if (!res) return false;

		// LOADS

		//glDisable(GL_NORMALIZE);
		//glDisable(GL_LIGHTING);
	}
	else {
		if(level == 1) {
		
		}
		else if(level == 2) {
		
		}
	}

	startTimeProj = 0;

	//Scene initialization
	res = Data.LoadImage(IMG_TILES_001,"img/level/tiles.png",GL_RGBA);
	if(!res) return false;
	res = Data.LoadImage(IMG_SPACE, "img/level/level01.png", GL_RGBA);
	if (!res) return false;
	res = Scene.LoadLevel(3);
	if(!res) return false;
	//Player initialization
	res = Data.LoadImage(IMG_PLAYER,"img/nau-alpha.png",GL_RGBA);
	if(!res) return false;

	res = Data.LoadImage(IMG_PLAYER1,"img/nau-alpha2.png",GL_RGBA);
	if(!res) return false;

	Player.SetWidthHeight(48,11*2);

	//Projectil iniatilation
	res = Data.LoadImage(IMG_MISSILE, "img/nau-alpha.png", GL_RGBA);
	if(!res) return false;

	if(level == 1) {
		PlaySound(TEXT("sound/background-lvl1.wav"),NULL,SND_LOOP |SND_ASYNC);
	}
	//Coloca el Jugador
	Player.SetTile(4,10);
	Player.SetWidthHeight(48,11*2);
	//Et diu cap a un mira
	Player.SetState(STATE_LOOKRIGHT);

	for(int i = 0; i < NUM_MISSILES; i++)
		projectils[i].setDimensions(20*0.5,10*0.5);

	return res;
}

bool cGame::Loop()
{
	bool res=true;

	if(level == 0) res = ProcessMenu();
	else res = Process();

	if(res) {
		if(level == 0) renderMenu();
		//else if(level == 1) {}
		//else if(level == 2) {}
		else Render();
	}
	return res;
}

void cGame::Finalize()
{
}

//Input
void cGame::ReadKeyboard(unsigned char key, int x, int y, bool press)
{
	keys[key] = press;
}

void cGame::ReadMouse(int button, int state, int x, int y)
{
}

//Process
bool cGame::Process()
{
	bool res=true;
	
	//Process Input
	if(keys[27])	res=false;

	//Player.Advance();

	if (keys[GLUT_KEY_UP])			Player.MoveUp(Scene.map);
	else if (keys[GLUT_KEY_LEFT])	Player.MoveLeft(Scene.map);
	else if (keys[GLUT_KEY_RIGHT])	Player.MoveRight(Scene.map);
	else if (keys[GLUT_KEY_DOWN])   Player.MoveDown(Scene.map);
	else Player.Stop();
	
	if (keys[KEY_SPACE] && (glutGet(GLUT_ELAPSED_TIME) - startTimeProj) > DELAY_PROJ) {
		int x,y;
		Player.GetPosition(&x,&y);
		startTimeProj = glutGet(GLUT_ELAPSED_TIME);
		activateProjectil(x,y,0);
		Player.Shoot(0);
	}

	if(keys[KEY_A_MAJ] || keys[KEY_A_MIN]) {
		if(!buttonA) {
			buttonA = true;
			timeButtonAInitial = glutGet(GLUT_ELAPSED_TIME);
		}
		else {
			timeButtonAFinal = glutGet(GLUT_ELAPSED_TIME);
		}
	}
	else {	// no apretat
		if(buttonA) {
			buttonA = false;
			int x,y;
			int diff = timeButtonAFinal - timeButtonAInitial;
			Player.GetPosition(&x,&y);
			if(diff > 0 && diff < 200) {
				activateProjectil(x,y,0);
				Player.Shoot(0);
			}
			else if(diff > 200 && diff < 2000) { // atac semi fort
				activateProjectil(x,y,1);
				Player.Shoot(1);
			}
			else {	// atac fort
				activateProjectil(x,y,2);
				Player.Shoot(2);
			}
		}
	}
	
	//Game Logic
	//Player.Logic(Scene.GetMap());
	for (int i = 0; i < NUM_MISSILES; ++i) {
		if (projectils[i].getActive()) {
			if (projectils[i].canMove()) {
				int x, y;

				projectils[i].getPosition(&x, &y);
				x = x + SPEED_PROJ;
				projectils[i].setPosition(x, y);
			}
		}
	}

	return res;
}

//Output
void cGame::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	glLoadIdentity();

	Scene.DrawBackground(Data.GetID(IMG_SPACE));
	Scene.Draw(Data.GetID(IMG_TILES_001));
	Player.Draw(Data.GetID(IMG_PLAYER));
	renderProjectils(Data.GetID(IMG_MISSILE));

	glutSwapBuffers();
}

void cGame::activateProjectil(int x, int y, int type)
{
	bool found = false;

	for(int i = 0; i < NUM_MISSILES && !found; ++i) {
		if(!projectils[i].getActive()) { // posicio disponible
			projectils[i].setActive(true);
			projectils[i].setType(type);	// TEMPORAL
			projectils[i].setPosition(x,y);
			found = true;
		}
	}
}

void cGame::renderProjectils(int textId)
{
	for(int i = 0; i < NUM_MISSILES; ++i) {
		if(projectils[i].getActive()) {
			if(projectils[i].getType() == 0) {
				projectils[i].setDimensions(20*0.5,10*0.5);
			}
			if(projectils[i].getType() == 1) {
				projectils[i].setDimensions(33*1.2,14*1.2);
			}
			if(projectils[i].getType() == 2) {
				projectils[i].setDimensions(81*1.5,18*1.5);
			}

			projectils[i].Draw(textId);
		}
	}
}

bool cGame::ProcessMenu()
{
	bool res = true;

	if(keys[GLUT_KEY_UP]) {}
	else if(keys[GLUT_KEY_DOWN]) {}

	return res;
}

void printString(void* font, const char* string)
{
	int len = strlen(string);
	for(int i = 0; i < len; i++) glutBitmapCharacter(font, string[i]);
}

void cGame::renderMenu()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	int id = Data.GetID(IMG_MENU_TITOL);

	glMatrixMode(GL_PROJECTION);

	glColor4f(1.0, 1.0, 1.0, 1.0);
	glRasterPos2f(0, 0);
	printString(GLUT_BITMAP_9_BY_15,"holaaa");
	
	glLoadIdentity();
	glEnable(GL_TEXTURE_2D);	
	glBindTexture(GL_TEXTURE_2D, id);
	glBegin(GL_QUADS);
		
	glTexCoord2f(0,1 );				glVertex2d(-0.7,0.6);
	glTexCoord2f(1,1);				glVertex2d(0.7,0.6);
	glTexCoord2f(1 ,0);					glVertex2d(0.7,0.9);
	glTexCoord2f(0,0);					glVertex2d(-0.7,0.9);

	glEnd();
	glDisable(GL_TEXTURE_2D);
	glutSwapBuffers();

	
}

cPlayer cGame::getPlayer() {
	return Player;
}


