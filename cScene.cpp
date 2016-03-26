#include "cScene.h"
#include "cData.h"
#include "cHelper.h"
#include "Globals.h"


cScene::cScene(void)
{
	velocitat = 5;
	velocitatBackground = 2;
}

cScene::~cScene(void)
{
}

bool cScene::LoadLevel(int level)
{
	bool res;
	FILE *fd;
	char file[16];
	int i,j,px,py;
	char tile;
	float coordx_tile, coordy_tile;

	int w, h;
	cData cData;

	cData.GetSize(IMG_TILES_001, &w, &h);
	//map2 = vector<vector<int>>(SCENE_WIDTH*5, SCENE_HEIGHT*5); 

	cHelper cHelper;

	cHelper.setWandH(w, h);

	res=true;

	if(level<10) sprintf(file,"%s0%d%s",(char *)FILENAME,level,(char *)FILENAME_EXT);
	else		 sprintf(file,"%s%d%s",(char *)FILENAME,level,(char *)FILENAME_EXT);

	fd=fopen(file,"r");
	if(fd==NULL) return false;

	id_DL_level=glGenLists(1);
	glNewList(id_DL_level,GL_COMPILE);
		glBegin(GL_QUADS);
	
			for(j=SCENE_HEIGHT-1;j>=0;j--)
			{
				vector<int> fila;
				px=TILE_SIZE;
				py=(j*TILE_SIZE);

				for(i=0;i<SCENE_WIDTH;i++)
				{

					int tile;
					float x, y;

					tile = cHelper.transformCToN(fd);
					//Coordenadas tile
					cHelper.getXandY(tile, w, h, &x, &y);

					if(tile != 0 )
					{
						//Tiles = 1,2,3,...
						coordx_tile = x;
						coordy_tile = y;

						float descx = cHelper.getDesc(BLOCK_SIZE, w);
						float descy = cHelper.getDesc(BLOCK_SIZE, h);

						//BLOCK_SIZE = 16, FILE_SIZE = ???
						// 24 / 64 = 0.375
						glTexCoord2f(coordx_tile, coordy_tile + descy);	glVertex2i(px, py);
						glTexCoord2f(coordx_tile + descx, coordy_tile + descy);	glVertex2i(px + BLOCK_SIZE, py);
						glTexCoord2f(coordx_tile + descx, coordy_tile);	glVertex2i(px + BLOCK_SIZE, py + BLOCK_SIZE);
						glTexCoord2f(coordx_tile, coordy_tile);	glVertex2i(px, py + BLOCK_SIZE);
					}
					fila.push_back(tile);
					px+=TILE_SIZE;
				}
				map2.push_back(fila);
			}

		glEnd();
	glEndList();

	cData.GetSize(IMG_SPACE, &w, &h);
	cHelper.setWandH(w, h);

	fclose(fd);
	fd = fopen("background001.txt", "r");
	if (fd == false) return false;
	id_DL_background=glGenLists(1);
	glNewList(id_DL_background, GL_COMPILE);
	glBegin(GL_QUADS);

	int count = 0;

	for (j = SCENE_HEIGHT - 1; j >= 0; j--)
	{
		px = TILE_SIZE;
		py = (j*TILE_SIZE);

		for (i = 0; i<SCENE_WIDTH; i++)
		{

			int tile;
			float x, y;
			
			

			tile = cHelper.transformCToN(fd);
			//Coordenadas tile
			cHelper.getXandY(tile, w, h, &x, &y);

			if (tile != 0)
			{
				//Tiles = 1,2,3,...
				coordx_tile = x;
				coordy_tile = y;

				float descx = cHelper.getDesc(BLOCK_SIZE, w);
				float descy = cHelper.getDesc(BLOCK_SIZE, h);

				//BLOCK_SIZE = 16, FILE_SIZE = ???
				// 24 / 64 = 0.375
				glTexCoord2f(coordx_tile, coordy_tile + descy);	glVertex2i(px, py);
				glTexCoord2f(coordx_tile + descx, coordy_tile + descy);	glVertex2i(px + BLOCK_SIZE, py);
				glTexCoord2f(coordx_tile + descx, coordy_tile);	glVertex2i(px + BLOCK_SIZE, py + BLOCK_SIZE);
				glTexCoord2f(coordx_tile, coordy_tile);	glVertex2i(px, py + BLOCK_SIZE);
			}
			px += TILE_SIZE;
		}
	}

	glEnd();
	glEndList();

	fclose(fd);
	return res;
}

void cScene::Draw(int tex_id)

{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex_id);
	glTranslatef(-velocitat, 0, 0);
	glCallList(id_DL_level);
	//Limite del nivel
	if (velocitat != ((TILE_SIZE*SCENE_WIDTH) - 640)) velocitat += 0.5;
	glDisable(GL_TEXTURE_2D);


}

void cScene::DrawBackground(int tex_id)

{
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex_id);
	glTranslatef(-velocitatBackground, 0, 0);
	glCallList(id_DL_background);
	//Limite del nivel
	if (velocitat != ((TILE_SIZE*SCENE_WIDTH) - 640)) velocitatBackground += 0.2;
	glDisable(GL_TEXTURE_2D);



}
int* cScene::GetMap()
{
	return map;
}

vector<vector<int> > cScene::GetMap2() {
	return map2;
}