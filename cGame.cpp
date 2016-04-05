#include "cGame.h"
#include "Globals.h"

bool buttonA = false; // true -> boto 'A' apretat

cGame::cGame(void)
{
	level = 0;
	buttonA = false;
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

bool cGame::isVisible(int x)
{
	
	int offset = 20;
	//if(x < GAME_WIDTH+cScene.velocitat+offset && x > cScene.velocitat - 5000 ) return true;
	if(x < GAME_WIDTH+Scene.velocitat+offset) return true;
	else return false;
}

bool cGame::isVisibleLeft(int x) {
	return !((x) < Scene.velocitat);
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
			

			res = generateEnemies(1);
			if(!res) return false;
		}
		else if(level == 2) {
			

			res = generateEnemies(2);
			if(!res) return false;
		}
	}

	startTimeProj = 0;
	lastArrowTime = 0;


	Player.SetWidthHeight(48,11*2);

	//Scene initialization
	res = Data.LoadImage(IMG_TILES_001,"img/level1/tiles.png",GL_RGBA);
	if(!res) return false;
	res = Data.LoadImage(IMG_SPACE, "img/level1/level01.png", GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_TILES_002, "img/level0/RockTile.png", GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_SPACE_2, "img/level0/background.png", GL_RGBA);
	if (!res) return false;

	if (level == 2) 
		res = Scene.LoadLevel(2);
	else res = Scene.LoadLevel(1);
	
	if(!res) return false;

	//Projectil initialization
	res = Data.LoadImage(IMG_MISSILE, "img/nau-alpha.png", GL_RGBA);
	if(!res) return false;

	//Enemies initialization
	res = Data.LoadImage(IMG_ENEMY1,"img/enemies/enemy1.png",GL_RGBA);
	if(!res) return false;

	res = Data.LoadImage(IMG_ENEMY2,"img/enemies/enemy2.png",GL_RGBA);
	if(!res) return false;

	res = Data.LoadImage(IMG_ENEMY3,"img/enemies/enemy3.png",GL_RGBA);
	if(!res) return false;

	if(level == 0) {
		res = PlaySound(TEXT("sound/Intro.wav"),NULL,SND_LOOP |SND_ASYNC);
		if (res == false) return res;
	}
	else if(level == 1) {
		res = PlaySound(TEXT("sound/Stage1.wav"),NULL,SND_LOOP |SND_ASYNC);
		if (res == false) return res;
	}
	else if(level == 2) {
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
		if(level == 0) RenderMenu();
		else  Render();
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

	
	//Avancem jugador
	Player.Advance();


	if (keys[GLUT_KEY_UP])			Player.MoveUp(&Scene.map);
	else if (keys[GLUT_KEY_LEFT])	Player.MoveLeft(&Scene.map);
	else if (keys[GLUT_KEY_RIGHT])	Player.MoveRight(&Scene.map);
	else if (keys[GLUT_KEY_DOWN])   Player.MoveDown(&Scene.map);
	else {
		Player.Stop();

			
	}

	
	
	if (keys[KEY_SPACE] && (glutGet(GLUT_ELAPSED_TIME) - startTimeProj) > DELAY_PROJ) {
		int x,y;
		Player.GetPosition(&x,&y);
		startTimeProj = glutGet(GLUT_ELAPSED_TIME);
		ActivateProjectil(x,y,0);
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
			if(diff > 0 && diff < TIME_MEDIUM_SHOT) {
				ActivateProjectil(x,y,0);
				Player.Shoot(0);
			}
			else if(diff > TIME_MEDIUM_SHOT && diff < TIME_STRONG_SHOT) { // atac semi fort
				ActivateProjectil(x,y,1);
				Player.Shoot(1);
			}
			else {	// atac fort
				ActivateProjectil(x,y,2);
				Player.Shoot(2);
			}
		}
	}
	
	// MISSILES
	for (int i = 0; i < NUM_MISSILES; ++i) {
		if (projectils[i].getActive()) {
			if (projectils[i].canMove()) {
				int x, y;
				projectils[i].getPosition(&x, &y);
				if(!this->isVisible(x)) projectils[i].setActive(false);	// missile not visible
				else {
					if (!projectils[i].isCollision(&Scene.map)) {
						x = x + SPEED_PROJ;
						projectils[i].setPosition(x, y);
						for (int j = 0; j < NUM_ENEMIES; ++j) {
							if (!enemies[j].isDead()) {
								cRect cRect;
								projectils[i].GetArea(&cRect);
								if (enemies[j].Collides(&cRect)) {
									//Enemies life
									enemies[j].setHurted(true);
									int life = enemies[i].getLife() - projectils[i].getDamage();
									if (life <= 0) {
										enemies[j].setDead(true);
									}
									else enemies[j].setLife(life);
									projectils[i].setActive(false);

								}
							}
						}
					}
					else projectils[i].setActive(false);
				}
			}
		}
	}

	// ENEMIES
	for (int i = 0; i < NUM_ENEMIES; ++i) {
		if(!enemies[i].isDead()) {
			if(1) {	// can move?
				//if (!enemies[i].isCollision(&Scene.map)) {
					int x, y;
					enemies[i].getPosXY(&x, &y);
					if (!this->isVisible(x)) {}
					else if (!isVisibleLeft(x)) {
						enemies[i].setDead(true);
					}
					else {
						//Comprova si el jugador a xocat
						cRect cRect;
						Player.GetArea(&cRect);
						if (enemies[i].Collides(&cRect)) {

							//Posar que la vida es resti
							Player.setLives(Player.getLives() - 1);
							enemies[i].setDead(true);
						}

						if(enemies[i].getType() == 1) {
							x -= SPEED_ENEMY1;
							enemies[i].setPosXY(x, y);
						}
						else if(enemies[i].getType() == 2) {
							x -= SPEED_ENEMY2;
							enemies[i].setPosXY(x, y);
						}
						else if(enemies[i].getType() == 3) {
							int xPlayer, yPlayer;
							Player.GetPosition(&xPlayer, &yPlayer);
							//Seguira al player
							//L'enemic 3 segueix al Player y acelera quan esta a la seva altura
							int w, h;
							enemies[i].getWidthHeight(&w, &h);
							if (yPlayer == (y - h)) x -= SPEED_ENEMY3;
							else if (yPlayer > (y - h)) {
								y += SPEED_ENEMY3 - 1;
								x -= 1;
							}
							else {
								x -= 1;
								y -= (SPEED_ENEMY3 - 1);
							}

							enemies[i].setPosXY(x, y);
						}
						
					}
			}
		}
	}

	return res;
}

void printString(void* font, const char* string)
{
	int len = strlen(string);
	for (int i = 0; i < len; i++) glutBitmapCharacter(font, string[i]);
}


void cGame::RenderGUI()
{
	int id = Data.GetID(IMG_PLAYER);
	int w, h;
	posTexture p;
	int screen_x, screen_y;
	int text_y;

	p.xo = 166.0f / IMG_WIDTH_PLAYER;
	p.yo = 1.0f / IMG_HEIGHT_PLAYER;
	p.xf = 199.0f / IMG_WIDTH_PLAYER;
	p.yf = 16.0f / IMG_HEIGHT_PLAYER;

	Player.GetWidthHeight(&w, &h);
	screen_x = 25;
	screen_y = -20;

	glLoadIdentity();
	glEnable(GL_TEXTURE_2D);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, id);
	glBegin(GL_QUADS);	
		glTexCoord2f(p.xo,p.yf);	glVertex2d(screen_x * 0.8,(screen_y - h) * 0.8);
		glTexCoord2f(p.xf,p.yf);	glVertex2d((screen_x + w) * 0.8,(screen_y - h) * 0.8);
		glTexCoord2f(p.xf,p.yo);	glVertex2d((screen_x + w) * 0.8, screen_y * 0.8);
		glTexCoord2f(p.xo,p.yo);	glVertex2d(screen_x * 0.8, screen_y * 0.8);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	// LIVES
	string s;
	stringstream out;
	out << Player.getLives();
	s = out.str();

	char second[32];
	strcpy(second, s.c_str());
	char first[32];
	strcpy (first,"x");
	strcat(first,second);

	text_y = (screen_y-h) + 12;
	glRasterPos2f(60, text_y);
	printString(GLUT_BITMAP_9_BY_15, first);

	// LOADING SHOT
	stringstream out1;
	int time_shot;
	double time_converted;

	if(!buttonA) time_shot = 0;
	else time_shot = timeButtonAFinal - timeButtonAInitial;
	if(time_shot < 0 ) time_shot = 0;

	time_converted =  (double) time_shot / TIME_STRONG_SHOT * 100;
	time_shot = time_converted;
	if(time_shot > 100) time_shot = 100;

	out1 << time_shot;
	s = out1.str();

	strcpy(second, s.c_str());
	strcpy (first,"");
	strcat(first,second);
	strcpy (second,"%");
	strcat(first,second);

	glRasterPos2f(120, text_y);
	printString(GLUT_BITMAP_9_BY_15, "Shot:");

	if(time_shot < 30) glColor4f(1.0, 0.0, 0.0, 1.0);
	else if (time_shot < 70) glColor4f(1.0, 0.64, 0.0, 1.0);
	else if (time_shot < 100) glColor4f(1.0, 1.0, 0.0, 1.0);
	else if (time_shot == 100) glColor4f(0.0, 1.0, 0.0, 1.0);

	glRasterPos2f(170, text_y);
	printString(GLUT_BITMAP_9_BY_15, first);
	glColor4f(1.0, 1.0, 1.0, 1.0);
}

void cGame::RenderEnemies(int id1, int id2, int id3)
{
	for(int i = 0; i < NUM_ENEMIES; ++i) {
		if(!enemies[i].isDead()) {
			int x, y;
			enemies[i].getPosXY(&x, &y);
			if(this->isVisible(x)) {	// draw only if alive and visible
				if(enemies[i].getType() == 1) {
					enemies[i].Draw(id1);
				}
				else if(enemies[i].getType() == 2) {
					enemies[i].Draw(id2);
				}
				else if(enemies[i].getType() == 3) {
					enemies[i].Draw(id3);
				}
			}
		}
	}
}

//Output
void cGame::Render()
{
	if (level != 0) {

		glClear(GL_COLOR_BUFFER_BIT);



		glLoadIdentity();

		

		if (level == 2) {

			Scene.DrawBackground(Data.GetID(IMG_SPACE));
			Scene.Draw(Data.GetID(IMG_TILES_001));
		}
		else {
			Scene.DrawBackground(Data.GetID(IMG_SPACE_2));
			Scene.Draw(Data.GetID(IMG_TILES_002));
		}


		RenderEnemies(Data.GetID(IMG_ENEMY1), Data.GetID(IMG_ENEMY2), Data.GetID(IMG_ENEMY3));
		Player.Draw(Data.GetID(IMG_PLAYER));
		RenderProjectils(Data.GetID(IMG_MISSILE));
		

		RenderGUI();

		glutSwapBuffers();
	}
}

void cGame::ActivateProjectil(int x, int y, int type)
{
	bool found = false;

	for(int i = 0; i < NUM_MISSILES && !found; ++i) {
		if(!projectils[i].getActive()) { // posicio disponible
			projectils[i].setActive(true);
			projectils[i].setType(type);	
			projectils[i].setPosition(x,y);
			found = true;
		}
	}
}

void cGame::RenderProjectils(int textId)
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
			if (!projectils[i].isCollision(&Scene.map))
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
						this->level = 1;
						Init();
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


void cGame::RenderMenu()
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

int getInfoMonster(FILE *fd)
{
	int e = 0;
	char c;
	fscanf(fd,"%c",&c);
	while(c != ' ') {
		e = e * 10;
		e += (c - 48);
		fscanf(fd,"%c",&c);
	}
	return e;
}

bool cGame::generateEnemies(int level)
{
	bool res = true;
	FILE *fd;
	int x, y, type;
	char c;

	if(this->level == 1)
		fd=fopen("txt/enemiesLVL1.txt","r");
	else if(this->level == 2)
		fd=fopen("txt/enemiesLVL2.txt","r");
	//if(fd==NULL) return false;

	for(int i = 0; i < NUM_ENEMIES; ++i) {
		x = 0, y = 0, type = 0;
		x = getInfoMonster(fd);
		y = getInfoMonster(fd);
		type = getInfoMonster(fd);

		fscanf(fd,"%c",&c); //pass enter

		cEnemy enemy(x, y, type);
		if(type == 1) {
			enemy.setType(1);
			enemy.setWidthHeight(33*1.2,25*1.2);
			enemy.setLife(LIFE_ENEMY_1);
			
		}
		else if(type == 2) {
			enemy.setType(2);
			enemy.setWidthHeight(34*2.0,26*2.0);
			enemy.setLife(LIFE_ENEMY_2);
		}
		else if(type == 3) {
			enemy.setType(3);
			enemy.setWidthHeight(34*2.0,26*2.0);
			enemy.setLife(LIFE_ENEMY_1);
		}
		enemies[i] = enemy;

	}
	fclose(fd);
	return res;
}

cPlayer cGame::getPlayer() {
	return Player;
}


