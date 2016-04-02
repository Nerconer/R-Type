#include "cGame.h"
#include "Globals.h"

bool buttonA = false; // true -> boto 'A' apretat

cGame::cGame(void)
{
	level = 0;
	fullscreen = false;

	menuAnimation = true;
	posy1 = -1.6;
	posy2 = -1.2;
	blinkAnim = true;
	loopsBlink = 0;

	delayNauMenu = 0;
	delayTextMenu = 0;

	oscilation = 0;
	upMenu = true; // puja
	delayOscilationMenu = 0;

	engineAnimMenu = 0;
	delayEngineAnimMenu = 0;
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
	glOrtho(0,GAME_WIDTH,-PANEL_SIZE,GAME_HEIGHT,0,1);
	glMatrixMode(GL_MODELVIEW);
	
	glAlphaFunc(GL_GREATER, 0.05f);
	glEnable(GL_ALPHA_TEST);

	if(level == 0) {
		//PlaySound();
		res = Data.LoadImage(IMG_MENU_TITOL, "img/titolRtype.png", GL_RGBA);
		if (!res) return false;

		//Player initialization
		res = Data.LoadImage(IMG_PLAYER,"img/nau-alpha.png",GL_RGBA);
		if(!res) return false;

		res = Data.LoadImage(IMG_PLAYER1,"img/nau-alpha2.png",GL_RGBA);
		if(!res) return false;

		//res = Data.LoadImage(IMG_MENU_SELECTED, "img/option_selected.png", GL_RGBA);
		//if (!res) return false;

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

	Player.SetWidthHeight(48,11*2);

	//Scene initialization
	res = Data.LoadImage(IMG_TILES_001,"img/level/tiles.png",GL_RGBA);
	if(!res) return false;
	res = Data.LoadImage(IMG_SPACE, "img/level/level01.png", GL_RGBA);
	if (!res) return false;
	res = Scene.LoadLevel(3);
	if(!res) return false;

	//Projectil iniatilation
	res = Data.LoadImage(IMG_MISSILE, "img/nau-alpha.png", GL_RGBA);
	if(!res) return false;

	if(level == 2) {
		res = PlaySound(TEXT("sound/background-lvl1.wav"),NULL,SND_LOOP |SND_ASYNC);
		if (res == false) return res;
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
		else if(level == 2) Render();
		//else if(level == 2) {}
		//else Render();
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
	if (level != 0) {
		glClear(GL_COLOR_BUFFER_BIT);

		glLoadIdentity();

		Scene.DrawBackground(Data.GetID(IMG_SPACE));
		Scene.Draw(Data.GetID(IMG_TILES_001));
		Player.Draw(Data.GetID(IMG_PLAYER));
		renderProjectils(Data.GetID(IMG_MISSILE));

		glutSwapBuffers();
	}
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

	if(keys[27])	res=false;
	switch(Menu.getTypeMenu()) {
		case MENU_PRINCIPAL:
			Menu.setNumOptions(4);
			if(keys[GLUT_KEY_UP]) {
				Menu.descreaseSO();
				keys[GLUT_KEY_UP] = false;
			}
			else if(keys[GLUT_KEY_DOWN]) {
				Menu.increaseSO();
				keys[GLUT_KEY_DOWN] = false;
			}
			else if(keys[KEY_INTRO]) {
				keys[KEY_INTRO] = false;
				switch(Menu.getSO()){
					case 0:	// Play
						Menu.setTypeMenu(MENU_SELECT_LEVEL);
						Menu.setSO(0);	
						Menu.setNumOptions(3);	// Lvl1, Lvl2, Back
						break;
					case 1:	// Instructions
						Menu.setTypeMenu(MENU_INSTR);
						Menu.setSO(0);	
						break;
					case 2:	// Credits
						Menu.setTypeMenu(MENU_CR);
						Menu.setSO(0);	
						break;
					case 3:	// Fullscreen
						fullscreen = !fullscreen;
						if(fullscreen)
							glutFullScreen(); 
						else {
							int res_x,res_y,pos_x,pos_y;

							res_x = glutGet(GLUT_SCREEN_WIDTH);
							res_y = glutGet(GLUT_SCREEN_HEIGHT);
							pos_x = (res_x>>1)-(GAME_WIDTH>>1);
							pos_y = (res_y>>1)-(GAME_HEIGHT>>1);
							glutReshapeWindow(640, 480);
							glutPositionWindow(pos_x, pos_y);
						}
						Menu.setSO(0);	
						break;
				}
			}
			break;
		case MENU_INSTR:
			if(keys[KEY_INTRO]) {
				keys[KEY_INTRO] = false;
				Menu.setTypeMenu(MENU_PRINCIPAL);
			}
			break;

		case MENU_CR:
			if(keys[KEY_INTRO]) {
				keys[KEY_INTRO] = false;
				Menu.setTypeMenu(MENU_PRINCIPAL);
			}
			break;
		
		case MENU_SELECT_LEVEL:
			//Menu.setNumOptions(3);
			if(keys[GLUT_KEY_UP]) {
				Menu.descreaseSO();
				keys[GLUT_KEY_UP] = false;
			}
			else if(keys[GLUT_KEY_DOWN]) {
				Menu.increaseSO();
				keys[GLUT_KEY_DOWN] = false;
			}
			else if(keys[KEY_INTRO]) {
				keys[KEY_INTRO] = false;
				switch(Menu.getSO()){
					case 0:	// Level 1

						break;
					case 1:	// Level 2
						this->level = 2;
						Init();
						break;
					case 2:	// Back
						Menu.setTypeMenu(MENU_PRINCIPAL);
						Menu.setSO(0);
						break;
				}
			}
			break;
	}
	return res;
}

void printString(void* font, const char* string)
{
	int len = strlen(string);
	for(int i = 0; i < len; i++) glutBitmapCharacter(font, string[i]);
}

void drawOption(int id, float posx, float posy)
{
	glLoadIdentity();
	glEnable(GL_TEXTURE_2D);	
	glBindTexture(GL_TEXTURE_2D, id);
	glBegin(GL_QUADS);
		
	glTexCoord2f(0,1);					glVertex2d(posx, posy);
	glTexCoord2f(1,1);					glVertex2d(posx, posy);
	glTexCoord2f(1 ,0);					glVertex2d(posx, posy);
	glTexCoord2f(0,0);					glVertex2d(posx, posy);

	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void cGame::printOptions()
{	
	int id_selected = Data.GetID(IMG_MENU_SELECTED);
	float posx = -0.66; 
	float posy = 0.15;
	char *options[4];

	options[0] = "Play";
	options[1] = "Instructions";
	options[2] = "Credits";
	options[3] = "Activate fullscreen";

	for(int i = 0; i < sizeof(options)/4; ++i) {
		if(fullscreen) 
			options[3] = "Deactivate fullscreen";
		else
			options[3] = "Activate fullscreen";
		
		if(Menu.getSO() == i) {
			glColor4f(1.0, 1.0, 1.0, 1.0);
			glRasterPos2f(posx+0.005, posy);
			drawOption(IMG_MENU_SELECTED, posx, posy);
			printString(GLUT_BITMAP_9_BY_15,"< ");
			
		}
		else {
			glColor4f(0.0, 0.7, 0.7, 1.0);
			glRasterPos2f(posx, posy);
		}
		
		posy-=0.1;

		printString(GLUT_BITMAP_9_BY_15,options[i]);
		
		if(Menu.getSO() == i)
			printString(GLUT_BITMAP_9_BY_15," >");
	}
}

void printInstructions()
{
	char *explanation[4];
	float posx = -0.66;
	float posy = 0.2;
	float posyBack = -0.5;

	explanation[0] = "A -> Shot";
	explanation[1] = "Hold 'A' button in order to get a stronger shot.";
	explanation[2] = "Use the cursor in order to move the spacecraft.";
	explanation[3] = "Have fun annihilating all enemies!";

	glColor4f(0.0, 0.7, 0.7, 1.0);

	for(int i = 0; i < sizeof(explanation)/4; ++i) {
		glRasterPos2f(posx, posy);
		printString(GLUT_BITMAP_9_BY_15,explanation[i]);
		posy -=0.1;
	}

	glColor4f(1.0, 1.0, 1.0, 1.0);
	glRasterPos2f(posx, posyBack);
	printString(GLUT_BITMAP_9_BY_15,"<Back>");
}

void printCredits()
{
	char *credits[4];
	float posx = -0.66;
	float posy = 0.2;
	float posyBack = -0.5;

	credits[0] = "Created by:";
	credits[1] = "";
	credits[2] = "Esther Monerques Gallego";
	credits[3] = "David Sola Sole";

	glColor4f(0.0, 0.7, 0.7, 1.0);

	for(int i = 0; i < sizeof(credits)/4; ++i) {
		glRasterPos2f(posx, posy);
		printString(GLUT_BITMAP_9_BY_15,credits[i]);
		posy -=0.1;
	}

	glColor4f(1.0, 1.0, 1.0, 1.0);
	glRasterPos2f(posx, posyBack);
	printString(GLUT_BITMAP_9_BY_15,"<Back>");
}

void cGame::selectLevel()
{
	char *textSelect[2];
	char *levels[3];
	float posx = -0.66;
	float posy = 0.2;
	float posyBack = -0.5;

	textSelect[0] = "Select level: ";
	textSelect[1] = "";

	levels[0] = "Level 1";
	levels[1] = "Level 2";
	levels[2] = "Back";

	for(int i = 0; i < sizeof(textSelect)/4; ++i) {
		glColor4f(0.0, 0.7, 0.7, 1.0);
		glRasterPos2f(posx, posy);
		printString(GLUT_BITMAP_9_BY_15,textSelect[i]);
		posy -=0.1;
	}

	for(int i = 0; i < sizeof(levels)/4; ++i) {
		if(Menu.getSO() == i) {
			glColor4f(1.0, 1.0, 1.0, 1.0);
			glRasterPos2f(posx+0.005, posy);
			printString(GLUT_BITMAP_9_BY_15,"< ");
		}
		else {
			glColor4f(0.0, 0.7, 0.7, 1.0);
			glRasterPos2f(posx, posy);
		}
		
		printString(GLUT_BITMAP_9_BY_15,levels[i]);
		if(Menu.getSO() == i)
			printString(GLUT_BITMAP_9_BY_15," >");
		posy -=0.1;
	}

	/*
	glColor4f(1.0, 1.0, 1.0, 1.0);
	glRasterPos2f(posx, posyBack);
	printString(GLUT_BITMAP_9_BY_15,"<Back>");
	*/
}

void cGame::pintaNauMenu(int id, int id1)
{
	++delayOscilationMenu;

	if(delayOscilationMenu >= 10) {
		delayOscilationMenu = 0;
		if(upMenu) {
			this->oscilation+=2;
		}
		else if(oscilation >= 90) this->upMenu = false;
		else if(!upMenu) {
			this->oscilation-=2;
		}
		else if(oscilation <=0) this->upMenu = true;
	}
	
	// NAU
	posTexture p;

	p.xo = 166.0f / IMG_WIDTH_PLAYER;
	p.yo = 1.0f / IMG_HEIGHT_PLAYER;
	p.xf = 199.0f / IMG_WIDTH_PLAYER;
	p.yf = 16.0f / IMG_HEIGHT_PLAYER;


	glLoadIdentity();
	glEnable(GL_TEXTURE_2D);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, id);
	glBegin(GL_QUADS);	
		glTexCoord2f(p.xo,p.yf);	glVertex2d(0.2,-0.08+sin((float) oscilation)*0.01);
		glTexCoord2f(p.xf,p.yf);	glVertex2d(0.5,-0.08+sin((float) oscilation)*0.01);
		glTexCoord2f(p.xf,p.yo);	glVertex2d(0.5,0.12+sin((float) oscilation)*0.01);
		glTexCoord2f(p.xo,p.yo);	glVertex2d(0.2,0.12+sin((float) oscilation)*0.01);
	glEnd();
	glPopMatrix();


	// ANIMACIO MOTOR
	posTexture p1;
	posTexture p2;

	p1.xo = 6.0f / IMG_WIDTH_PLAYER1;
	p1.yo = 97.0f / IMG_HEIGHT_PLAYER1;
	p1.xf = 21.0f / IMG_WIDTH_PLAYER1;
	p1.yf = 105.0f / IMG_HEIGHT_PLAYER1;

	p2.xo = 24.0f / IMG_WIDTH_PLAYER1;
	p2.yo = 92.0f / IMG_HEIGHT_PLAYER1;
	p2.xf = 41.0f / IMG_WIDTH_PLAYER1;
	p2.yf = 108.0f / IMG_HEIGHT_PLAYER1;

	int transSpeed = 15;
	if(this->engineAnimMenu == 0) {
		if(delayEngineAnimMenu == transSpeed) {
			delayEngineAnimMenu = 0;
			this->engineAnimMenu = 1;
		}
		else ++delayEngineAnimMenu;
		
	}
	else if(this->engineAnimMenu == 1) {
		if(delayEngineAnimMenu == transSpeed) {
			delayEngineAnimMenu = 0;
			this->engineAnimMenu = 2;
		}
		else ++delayEngineAnimMenu;
		
		glLoadIdentity();
		glEnable(GL_TEXTURE_2D);
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glBindTexture(GL_TEXTURE_2D, id1);
		glBegin(GL_QUADS);	
			glTexCoord2f(p1.xo,p1.yf);	glVertex2d(0.05,-0.076+sin((float) oscilation)*0.01);
			glTexCoord2f(p1.xf,p1.yf);	glVertex2d(0.21,-0.076+sin((float) oscilation)*0.01);
			glTexCoord2f(p1.xf,p1.yo);	glVertex2d(0.21,0.016+sin((float) oscilation)*0.01);
			glTexCoord2f(p1.xo,p1.yo);	glVertex2d(0.05,0.016+sin((float) oscilation)*0.01);
		glEnd();
		glPopMatrix();
	}
	else if(this->engineAnimMenu == 2) {
		if(delayEngineAnimMenu == transSpeed) {
			delayEngineAnimMenu = 0;
			this->engineAnimMenu = 0;
		}
		else ++delayEngineAnimMenu;
		
		glLoadIdentity();
		glEnable(GL_TEXTURE_2D);
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glBindTexture(GL_TEXTURE_2D, id1);
		glBegin(GL_QUADS);	
			glTexCoord2f(p2.xo,p2.yf);	glVertex2d(-0.05,-0.15+sin((float) oscilation)*0.01);
			glTexCoord2f(p2.xf,p2.yf);	glVertex2d(0.21,-0.15+sin((float) oscilation)*0.01);
			glTexCoord2f(p2.xf,p2.yo);	glVertex2d(0.21,0.1+sin((float) oscilation)*0.01);
			glTexCoord2f(p2.xo,p2.yo);	glVertex2d(-0.05,0.1+sin((float) oscilation)*0.01);
		glEnd();
		glPopMatrix();
	}
}


void cGame::renderMenu()
{
	int id = Data.GetID(IMG_MENU_TITOL);
	int id_player = Data.GetID(IMG_PLAYER);
	int id_player1 = Data.GetID(IMG_PLAYER1);

	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);

	if(posy1 <= 0.5) {
		if(blinkAnim) {
			glLoadIdentity();
			glColor4f(1.0, 1.0, 1.0, 1.0);
			glEnable(GL_TEXTURE_2D);	
			glBindTexture(GL_TEXTURE_2D, id);
			glBegin(GL_QUADS);
		
			glTexCoord2f(0,0.95);				glVertex2d(-0.7,posy1+=0.02);
			glTexCoord2f(1,0.95);				glVertex2d(0.7,posy1+=0.02);
			glTexCoord2f(1 ,0);					glVertex2d(0.7,posy2+=0.02);
			glTexCoord2f(0,0);					glVertex2d(-0.7,posy2+=0.02);

			glEnd();
			glDisable(GL_TEXTURE_2D);
		}
		if(this->loopsBlink == 2) {
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			
			blinkAnim = !blinkAnim;
			loopsBlink = 0;
		}
		++loopsBlink;
		glutSwapBuffers();
	}
	else {	// End title aninmation
		if(delayTextMenu == 30) {
			switch(Menu.getTypeMenu()) {
				case MENU_PRINCIPAL:
					printOptions();
					break;
				case MENU_INSTR:
					printInstructions();
					break;
				case MENU_CR:
					printCredits();
					break;
				case MENU_SELECT_LEVEL:
					selectLevel();
					break;
			}
		}
		if(delayTextMenu < 30) ++delayTextMenu;

		if(delayNauMenu < 30) ++delayNauMenu;
		if(delayNauMenu == 30) {
			if(Menu.getTypeMenu() == MENU_PRINCIPAL) pintaNauMenu(id_player, id_player1);
		}
	
		glLoadIdentity();
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glEnable(GL_TEXTURE_2D);	
		glBindTexture(GL_TEXTURE_2D, id);
		glBegin(GL_QUADS);
		
		glTexCoord2f(0,0.95);				glVertex2d(-0.7,0.5);
		glTexCoord2f(1,0.95);				glVertex2d(0.7,0.5);
		glTexCoord2f(1 ,0);					glVertex2d(0.7,0.9);
		glTexCoord2f(0,0);					glVertex2d(-0.7,0.9);

		glEnd();
		glDisable(GL_TEXTURE_2D);
		glutSwapBuffers();
	}
}

cPlayer cGame::getPlayer() {
	return Player;
}


