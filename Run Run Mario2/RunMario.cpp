#include "freeglut/glut.h"
#include <GL/glut.h>
#include "DefineRunMario.h"
#include <stdio.h>

float	spin;	

void TextureInitial(void)
{
	// LOAD TEXTURES
	MarioTexture    	= KFLoadText(".\\data\\mariocar.bmp",			    GL_RGBA);
	RedTurtleTexture	= KFLoadText(".\\data\\red_turtle.bmp",				GL_RGBA);
	GreenTurtleTexture  = KFLoadText(".\\data\\green_turtle.bmp",			GL_RGBA);
	RedPlantTexture		= KFLoadText(".\\data\\red_eat_plant.bmp",			GL_RGBA);
	GreenPlantTexture	= KFLoadText(".\\data\\green_eat_plant.bmp",		GL_RGBA);
	FishTexture			= KFLoadText(".\\data\\big_fish.bmp",				GL_RGBA);
	NitrogenTexture		= KFLoadText(".\\data\\nitrogen.bmp",				GL_RGBA);
	LifeTexture			= KFLoadText(".\\data\\life.bmp",					GL_RGBA);
	BlockTexture	 	= KFLoadText(".\\data\\block.bmp",					GL_RGBA);
	SpeedUpBoardTexture	= KFLoadText(".\\data\\speedup_board.bmp",			GL_RGBA);
	CoinTexture			= KFLoadText(".\\data\\coin.bmp",					GL_RGBA);
	BackGround			= KFLoadText(".\\data\\background.bmp",				GL_RGB);
	DeadTexture			= KFLoadText(".\\data\\dead.bmp",					GL_RGB);
	WinTexture			= KFLoadText(".\\data\\win.bmp",					GL_RGB);
	FailTexture			= KFLoadText(".\\data\\fail.bmp",					GL_RGB);

	// INITIALIZE BLOCK CLASS
	for (int i = 0; i < counter; i++,blockclasscounter++) 
		Block[blockclasscounter].Initialize(TEXTURE_B.X[0]+i*95, TEXTURE_B.Y[0]);
	
	for (int j = 0; j < counter; j++,blockclasscounter++)
		Block[blockclasscounter].Initialize(TEXTURE_B.X[1]+j*95, TEXTURE_B.Y[1]);
	
	for (int w = 0; w < counter1; w++,blockclasscounter++)
		Block[blockclasscounter].Initialize(TEXTURE_B.X[2]+w*500, TEXTURE_B.Y[2]);

	for (int z = 0; z < counter1; z++,blockclasscounter++)
		Block[blockclasscounter].Initialize(TEXTURE_B.X[3]+z*500, TEXTURE_B.Y[3]);
	
	// INITIALIZE PLANT CLASS
	for (int i = 0; i < PlantNum; i++)
		Plant[i].Initialize(TEXTURE_P.X[i], TEXTURE_P.Y[i]);

	// INITIALIZE COIN CLASS
	for (int i = 0; i < CoinNum; i++)
		Coin[i].Initialize(TEXTURE_COIN.X[i], TEXTURE_COIN.Y[i]);
	
	// INITIALIZE Nitrogen CLASS
	for (int i = 0; i < NitrogenNum; i++)
		N2[i].Initialize(TEXTURE_N2.X[i], TEXTURE_N2.Y[i]);

	// INITIALIZE SpeedUpBoard CLASS
	for (int i = 0; i < SpeedUpBoardNum; i++)
		SpeedUpBoard[i].Initialize(TEXTURE_SpeedUp.X[i], TEXTURE_SpeedUp.Y[i]);

	// INITIALIZE ENEMY CLASS
	for (int i = 0; i < RTurtleNum; i++)
	{
		RTurtle[i].Initialize(RTurtleTexture.X[i], RTurtleTexture.Y[i]);
		//RTurtleFrame[i] = 0;
		//RTurtleFrameCount[i] = 1;
	}

	for (int i = 0; i < GTurtleNum; i++)
	{
		GTurtle[i].Initialize(GTurtleTexture.X[i], GTurtleTexture.Y[i]);
		//GTurtleFrame[i] = 0;
		//GTurtleFrameCount[i] = 1;
	}

	for (int i = 0; i < FishNum; i++)
	{
		Fish[i].Initialize(TextureFish.X[i], TextureFish.Y[i]);
		//FishFrame[i] = 0;
		//FishFrameCount[i] = 1;
	}

}

int InitGL(GLvoid)
{
	glShadeModel(GL_SMOOTH);
	glClearColor(.5f, .5f, .5f, 1.0f);
	glDepthFunc(GL_LEQUAL);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glDisable(GL_LIGHTING);
	//glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	TextureInitial();

	return TRUE;
}


void SetTexParameter()
{
	glTexParameterf ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameterf ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameterf ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	glTexParameterf ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
}


void ChangeSize(int _w, int _h)
{
	GLfloat aspectRatio;

	if (!_h) _h = 1;

	glViewport(0 , 0, _w, _h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(camera_L, camera_R, camera_B, camera_T);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void DrawObject(GLfloat _x1, GLfloat _y1, GLfloat _x2, GLfloat _y2, GLfloat _tex_x1, GLfloat _tex_y1, GLfloat _tex_x2, GLfloat _tex_y2)
{
	glBegin(GL_QUADS);
		glTexCoord2f(_tex_x1, _tex_y2);
		glVertex2f(_x1 , _y2);

		glTexCoord2f(_tex_x1, _tex_y1);
		glVertex2f(_x1 , _y1);

		glTexCoord2f(_tex_x2, _tex_y1);
		glVertex2f(_x2 , _y1);

		glTexCoord2f(_tex_x2, _tex_y2);
		glVertex2f(_x2 , _y2);
	glEnd();
}

void DrawBackGround()
{
	glBindTexture(GL_TEXTURE_2D, BackGround);	
	SetTexParameter();
	spin+=0.001f;
	for (int loop=0; loop<20; loop++)
	{
        glPushMatrix();
		glTranslatef( -spin+loop * 580.0f,2.0f,0.0f);
		DrawObject(	0.0f,
					0.0f,
					window_width * 1.0f,
					window_height * 1.0f,
					0.0f,
					0.0f,
					580.0f /5440.0f,
					1.0f);
		glPopMatrix();		
	}
	glBindTexture(GL_TEXTURE_2D, 0);
}
void GameOver()
{
	if(GetCoinNum > 25 && Mario.getlife() != 0)
	{
		glBindTexture(GL_TEXTURE_2D, WinTexture);
	}
	else if(Mario.getlife()<= 0)
		glBindTexture(GL_TEXTURE_2D, DeadTexture);
	else
	{
		glBindTexture(GL_TEXTURE_2D,FailTexture);
		
	}
	SetTexParameter();
		glPushMatrix();
	DrawObject(	0.0f + camera_L,
				0.0f,
				window_width * 1.0f + camera_L,
				window_height * 1.0f,
				0.0f,
				0.0f,
				1.0f,
				1.0f);
	glPopMatrix();		
	glBindTexture(GL_TEXTURE_2D, 0);
}
void SceneChangeDetect()
{
	GLfloat height = MARIO_CONTECT_HEIGHT[Mario.getAction()] * SCALE / 2.0f /*+ GARVITY_Y_ADJ[Mario.getAction()] * SCALE*/;

	camera_L += Mario.getCarSpeed();
	camera_R += Mario.getCarSpeed();
	
	if(camera_R >= 580 * 19.0f)
	{
		GameOver();		
	}
	camera_T = camera_B + window_height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(camera_L, camera_R, camera_B, camera_T);

}

void MovingCheck()
{

	if (Mario.getAction() == dead || Mario.getAction() == star) ControlDisable = false;

	if(Mario.getPosition() == GROUND){
		 Mario.setMovingX(X_normal);
		 Mario.setMovingY(Y_normal);
	}
	else if(Mario.getPosition() == AIR)
	{
		Mario.Air();
		if(Mario.getMovingX() == X_rushing) 
		{
			Mario.setMovingX(X_jump_rush);
			Mario.setMovingY(Y_jump_rush);
		}
		else 
		{
			Mario.setMovingX(X_jumping);
			Mario.setMovingY(Y_jumping);
		}
	}
	Mario.setDirection(LastDir);
}
void AttackDetect(GLfloat _x, GLfloat _y, GLfloat _w, GLfloat _h, int _l)
{
	
	if(_l >= 0)
	{
		/*for(int i = 0; i < totalBlockNum;i++)
		{
			if( 
				_x + _w >= Block[i].getblockPositionX() - BLOCK_WEIGHT/2&&
				_x - _w <= Block[i].getblockPositionX() - BLOCK_WEIGHT/2 &&
				_y + _h <= Block[i].getblockPositionY() + BLOCK_HIGHT/2 && //
				_y - _h >= Block[i].getblockPositionY() - BLOCK_HIGHT/2 ) //
			{
			
				
				_l--;
				Mario.setlife(_l);
			
			}
		}*/
		for(int i = 0; i< GTurtleNum; i++)
		{
			if( _x - _w <= GTurtle[i].getPositionX() && 
				_x + _w >= GTurtle[i].getPositionX() && 
				_y + _h <= GTurtle[i].getPositionY() + TEXTURE_GT_MOVE.HEIGHT[i] && //
				_y - _h >= GTurtle[i].getPositionY() - TEXTURE_GT_MOVE.HEIGHT[i] && //
				GTurtle[i].getAction() != t_dead)
				if(GTurtle[i].getATKStrength() >= Mario.getmarioATKStrength())
				{
					GTurtle[i].setAction(t_dead);
					_l--;
					Mario.setlife(_l);
					
				}
				else
					GTurtle[i].setAction(t_dead);
	
		}



		for(int i = 0; i< RTurtleNum; i++)
		{
			if( _x - _w <= RTurtle[i].getPositionX() && 
				_x + _w >= RTurtle[i].getPositionX() && 
				_y + _h <= RTurtle[i].getPositionY() + TEXTURE_RT_MOVE.HEIGHT[i] && //
				_y - _h >= RTurtle[i].getPositionY() - TEXTURE_RT_MOVE.HEIGHT[i] && //
				RTurtle[i].getAction() != t_dead)
				if(RTurtle[i].getATKStrength() >= Mario.getmarioATKStrength())
				{
					RTurtle[i].setAction(t_dead);
					_l--;
					Mario.setlife(_l);
				}
				else
					RTurtle[i].setAction(t_dead);
	
		}
		for(int i = 0; i< PlantNum; i++)
		{
			if( _x - _w <= Plant[i].getPositionX() &&
				_x + _w >= Plant[i].getPositionX() &&
				_y + _h <= Plant[i].getPositionY() + TEXTURE_P.HEIGHT[i] && //
				_y - _h >= Plant[i].getPositionY() - TEXTURE_P.HEIGHT[i] && //
				Plant[i].getAction() != t_dead)
				if(Plant[i].getATKStrength() >= Mario.getmarioATKStrength())
				{
					_l--;
					Mario.setlife(_l);
					Plant[i].setAction(p_dead);
				}
				else
					Plant[i].setAction(p_dead);


		}
		for(int i = 0; i< FishNum; i++)
		{
			if( _x - _w <= Fish[i].getPositionX() &&
				_x + _w >= Fish[i].getPositionX() && 
				_y + _h <= Fish[i].getPositionY() + TEXTURE_F_MOVE.HEIGHT[i] && //
				_y - _h >= Fish[i].getPositionY() - TEXTURE_F_MOVE.HEIGHT[i] && //
				Fish[i].getAction() != t_dead)
				if(Fish[i].getATKStrength() >= Mario.getmarioATKStrength())
				{
					_l--;
					Mario.setlife(_l);
					Fish[i].setAction(f_dead);

				}
				else
					Fish[i].setAction(f_dead);
		}

//ch
		for(int i = 0; i< CoinNum; i++)
		{
			if( _x - _w <= Coin[i].getCoinPositionX() && 
				_x + _w >= Coin[i].getCoinPositionX() && 
				_y + _h <= Coin[i].getCoinPositionY() + COIN_HIGHT + 15 && //
				_y - _h >= Coin[i].getCoinPositionY() - COIN_HIGHT - 15 && //
				Coin[i].getCoinState() == nohave)
				{
					Coin[i].setCoinState(have);
					Mario.setCoin(1);

				}
	
		}
//ch
		for(int i = 0; i< SpeedUpBoardNum; i++)
		{
			if( _x - _w <= SpeedUpBoard[i].getSpeedUpBoardPositionX() && 
				_x + _w >= SpeedUpBoard[i].getSpeedUpBoardPositionX() && 
				_y + _h <= SpeedUpBoard[i].getSpeedUpBoardPositionY() + SPEEDUPB_HIGHT + 10 && //
				_y - _h >= SpeedUpBoard[i].getSpeedUpBoardPositionY() - SPEEDUPB_HIGHT - 10 )
				{
					if(speedBoardcheck[i] == 0)
					{
						Mario.setCarSpeed(Mario.getCarSpeed() + 1);
						speedBoardcheck[i] = 1; 
					}

				}
			else
			{
				speedBoardcheck[i] = 0;
			}
		}

//ch
		for(int i = 0; i< NitrogenNum; i++)
		{
			if( _x - _w <= N2[i].getNitrogenPositionX() && 
				_x + _w >= N2[i].getNitrogenPositionX() && 
				_y + _h <= N2[i].getNitrogenPositionY() + N2_HIGHT + 15 && //
				_y - _h >= N2[i].getNitrogenPositionY() - N2_HIGHT - 15 &&
				N2[i].getNitrogenState() == n_nohave)
				{
					N2[i].setNitrogenState(n_have);
					Mario.setPocket(Nitrogen);
				}
		
		}
	}
	else
	{
			Mario.setAction(dead);
	}
}

void CollisionDetect()
{
	if (!GamePause && !CollisionDisable)
	{
		enum ContactState{NONE = 0, ONFLOOR = 1, ONWALL = 2, ONCELLING = 3};
		ContactState contact = NONE;

		GLfloat width	= MARIO_CONTECT_WIDTH[Mario.getAction()]	* SCALE / 2.0f;
		GLfloat height	= MARIO_CONTECT_HEIGHT[Mario.getAction()]	* SCALE / 2.0f;
	    GLfloat floor	= POSITION_FLOOR ;
		//GLfloat celling	= POSITION_CEILING + (Stage == 4 ? 480.0f : 0.0f);

		// ENEMY

		// BLOCK
		for (int i = 0; i < totalBlockNum; i++)
		{
			GLfloat bwidth	= 95.0f;
			GLfloat bheight	= 30.0f;

			if (Mario.getPositionX() + width	>= Block[i].getblockPositionX() && 
				Mario.getPositionX() - width		<= Block[i].getblockPositionX() + bwidth &&
				Mario.getPositionY() + height	>= Block[i].getblockPositionY() &&
				Mario.getPositionY() - height	<= Block[i].getblockPositionY() + bheight)
			{
				GLfloat TDif = -(Mario.getPositionY() - height)	+ (Block[i].getblockPositionY() + bheight);
				GLfloat BDif =  (Mario.getPositionY() + height)	- (Block[i].getblockPositionY());
				GLfloat LDif =  (Mario.getPositionX() + width)	- (Block[i].getblockPositionX());
				GLfloat RDif = -(Mario.getPositionX() - width)	+ (Block[i].getblockPositionX() + bwidth);

				if (TDif <= BDif && TDif <= LDif && TDif <= RDif)
				{
					Mario.setPositionY(Block[i].getblockPositionY() + height + bheight);
					contact = ONFLOOR;
				}
				else if (BDif <= TDif && BDif <= LDif && BDif <= RDif)
				{
					Mario.setPositionY(Block[i].getblockPositionY() - height);
					contact = ONCELLING;
				}
				else if (LDif <= TDif && LDif <= BDif && LDif <= RDif && TDif > 5.5f)
				{

					Mario.setlife(Mario.getlife()-1);
					//dead
				}
				else if (RDif <= TDif && RDif <= BDif && RDif <= LDif && TDif > 11.5f)
				{
					//Mario.setlife(Mario.getlife()-1);
					//dead
				}
			}
		}



		// ONFLOOR
		if (Mario.getPositionY()  - height <= floor)
		{
			Mario.setPositionY(floor + height );
			contact = ONFLOOR;
		}

		// CONACT EVENT PROCESS
		if (contact)
		{
			if (contact != ONCELLING)
			{

				if (contact == ONFLOOR) Mario.Ground();
				else if (Mario.getPosition() == AIR)
				{
					MarioFrame = 0;//change
					MarioFrameCount = 1;//change

				}
			}
			else if (Mario.getMovingY() == Y_jumping)
			{
				MarioFrame = 6;//change
				MarioFrameCount = 25;//change
			}
		}
		
		AttackDetect(Mario.getPositionX(),Mario.getPositionY(),width,height,Mario.getlife());
		SceneChangeDetect();
	}
}

void RenderScene(void)
{	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushAttrib(GL_COLOR_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	DrawBackGround();

	//************************************************************************************************************
	CollisionDetect();
	Coordinates QuadLB, QuadRT;	
		
	//////////////block//////////////

	for (int i = 0; i < totalBlockNum; i++)
	{
		glBindTexture(GL_TEXTURE_2D, BlockTexture);
		glPushMatrix();
		SetTexParameter();
		DrawObject(	Block[i].getblockPositionX(),
					Block[i].getblockPositionY(),
					Block[i].getblockPositionX() + 95,
					Block[i].getblockPositionY() + 30,
					0.0f,
					0.0f,
					1.0f,
					1.0f);
		glPopMatrix();
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	//////////////Red Turtle//////////////	
	for (int i = 0; i < RTurtleNum; i++)
	{
		if(RTurtle[RTurtleNum].getAction() != t_dead)
		{
			QuadLB.Y = RTurtle[i].getPositionY();
			QuadRT.Y = RTurtle[i].getPositionY() + 2* 32.0f;
			QuadLB.X = RTurtle[i].getPositionX();
			QuadRT.X = RTurtle[i].getPositionX() + 2 * 50.0f;

			glBindTexture(GL_TEXTURE_2D, RedTurtleTexture);
			glPushMatrix();
			SetTexParameter();
			//glTranslatef(Turtle[i].getPositionX(), Turtle[i].getPositionY(), 0.0f);//??????

			DrawObject(	QuadLB.X,
				QuadLB.Y,
				QuadRT.X,
				QuadRT.Y,
				R_Turtle_SingleW * RTurtleFrame / R_Turtle_AllW,
				0.0f,
				R_Turtle_SingleW * (RTurtleFrame+1) / R_Turtle_AllW,
				1.0f);

			glPopMatrix();
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
	//////////////Green Turtle//////////////
	for (int i = 0; i < GTurtleNum; i++)
	{
		if(GTurtle[GTurtleNum].getAction() != t_dead)
		{
			QuadLB.Y = GTurtle[i].getPositionY();
			QuadRT.Y = GTurtle[i].getPositionY() + 2* 32.0f;
			QuadLB.X = GTurtle[i].getPositionX();
			QuadRT.X = GTurtle[i].getPositionX() + 2 * 50.0f;

			glBindTexture(GL_TEXTURE_2D, GreenTurtleTexture);
			glPushMatrix();
			SetTexParameter();
			//glTranslatef(Turtle[i].getPositionX(), Turtle[i].getPositionY(), 0.0f);//??????

			DrawObject(	QuadLB.X,
				QuadLB.Y,
				QuadRT.X,
				QuadRT.Y,
				G_Turtle_SingleW * GTurtleFrame / G_Turtle_AllW,
				0.0f,
				G_Turtle_SingleW * (GTurtleFrame+1) / G_Turtle_AllW,
				1.0f);

			glPopMatrix();
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
	
	//////////////Plant//////////////	

	for (int i = 0; i < PlantNum; i++)
	{
		QuadLB.Y = Plant[i].getPositionY();
		QuadRT.Y = Plant[i].getPositionY() + 2 * 33.0f;
		QuadLB.X = Plant[i].getPositionX();
		QuadRT.X = Plant[i].getPositionX() + 2 * 50.0f;
		
		if(Plant[i].getColor() == p_Color_Red)
		{
			glBindTexture(GL_TEXTURE_2D, RedPlantTexture);
			glPushMatrix();
		    //glTranslatef(Plant[i].getPositionX(), Plant[i].getPositionY(), 0.0f);//??????
			DrawObject(	QuadLB.X,
						QuadLB.Y,
						QuadRT.X,
						QuadRT.Y,
						R_Plant_SingleW * RPlantFrame/ R_Plant_AllW,
						0.0f,
						R_Plant_SingleW * (RPlantFrame+1) / R_Plant_AllW,
						1.0f);

		}
		else if(Plant[i].getColor() == p_Color_Green)
		{
			glBindTexture(GL_TEXTURE_2D, GreenPlantTexture);
			//glPushMatrix();
			glTranslatef(Plant[i].getPositionX(), Plant[i].getPositionY(), 0.0f);//??????

			DrawObject(	QuadLB.X,
						QuadLB.Y,
						QuadRT.X,
						QuadRT.Y,
						G_Plant_SingleW * GPlantFrame / G_Plant_AllW,
						0.0f,
						G_Plant_SingleW * (GPlantFrame+1) / G_Plant_AllW,
						1.0f);
		}		
		glPopMatrix();
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	//////////////Fish//////////////			
	
	for (int i = 0; i < FishNum; i++)
	{
		QuadLB.Y = Fish[i].getPositionY();
		QuadRT.Y = Fish[i].getPositionY() + 2 * 39.0f;
		if (Fish[i].getDirection() == f_left)
		{
			QuadLB.X = Fish[i].getPositionX();
			QuadRT.X = Fish[i].getPositionX() + 2 * 50.0f;
		} 
		else if (Fish[i].getDirection() == f_right)
		{
			QuadRT.X = Fish[i].getPositionX() + 2 * 50.0f;
			QuadLB.X = Fish[i].getPositionX();
		}
		glBindTexture(GL_TEXTURE_2D, FishTexture);
		glPushMatrix();
		//glTranslatef(Fish[i].getPositionX(), Fish[i].getPositionY(), 0.0f);//??????
		DrawObject(	QuadLB.X,
					QuadLB.Y,
					QuadRT.X,
					QuadRT.Y,
					Fish_SingleW * FishFrame / Fish_AllW,
					0.0f,
					Fish_SingleW * (FishFrame+1) / Fish_AllW,
					1.0f);	
		glPopMatrix();
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	//////////////speed up board//////////////
	for (int i = 0; i < SpeedUpBoardNum; i++)
	{
		glBindTexture(GL_TEXTURE_2D, SpeedUpBoardTexture);
		glPushMatrix();
		SetTexParameter();
		DrawObject(	SpeedUpBoard[i].getSpeedUpBoardPositionX(),
					SpeedUpBoard[i].getSpeedUpBoardPositionY(),
					SpeedUpBoard[i].getSpeedUpBoardPositionX() + 50,
					SpeedUpBoard[i].getSpeedUpBoardPositionY() + 20,
					SpeedUpBoard_SingleW * SpeedUpBoardFrame / SpeedUpBoard_AllW,
					0.0f,
					SpeedUpBoard_SingleW * (SpeedUpBoardFrame+1) / SpeedUpBoard_AllW,
					1.0f);
		glPopMatrix();
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	//////////////N2//////////////
	for (int i = 0; i < NitrogenNum; i++)
	{
		glBindTexture(GL_TEXTURE_2D, NitrogenTexture);
		glPushMatrix();
		SetTexParameter();
		DrawObject(	N2[i].getNitrogenPositionX(),
					N2[i].getNitrogenPositionY(),
					N2[i].getNitrogenPositionX() + 40,
					N2[i].getNitrogenPositionY() + 40,
					0.0f,
					0.0f,
					1.0f,
					1.0f);
		glPopMatrix();
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	//////////////Coin//////////////
	for (int i = 0; i < CoinNum; i++)
	{
		if(Coin[i].getCoinState()==nohave){
		glBindTexture(GL_TEXTURE_2D, CoinTexture);
		glPushMatrix();
		SetTexParameter();
		DrawObject(	Coin[i].getCoinPositionX(),
					Coin[i].getCoinPositionY(),
					Coin[i].getCoinPositionX() + 25,
					Coin[i].getCoinPositionY() + 25,
					Coin_SingleW * CoinFrame / Coin_AllW,
					0.0f,
					Coin_SingleW * (CoinFrame+1) / Coin_AllW,
					1.0f);
		glPopMatrix();
		glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
	//////////////Life//////////////

	glBindTexture(GL_TEXTURE_2D, LifeTexture);
	glPushMatrix();
	SetTexParameter();
	DrawObject(	10.0f + camera_L,											
				window_height - 40.0f + camera_B,
				10.0f + (Mario.getlife() * 30.0f) + camera_L,				
				window_height - 10.0f + camera_B,
				0.0f / Life_AllW,									
				0.0f,
				Mario.getlife() * Life_SingleW / Life_AllW,				
				1.0f);
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);

	//////////////Mario//////////////	

	glBindTexture(GL_TEXTURE_2D, MarioTexture);
	glPushMatrix();
	SetTexParameter();

	DrawObject(	Mario.getPositionX(),
				Mario.getPositionY(),
				Mario.getPositionX() + 2 * 35.0f,
				Mario.getPositionY() + 2 * 33.0f,
				Mario_SingleW * MarioFrame / Mario_AllW,
				0.0f,
				Mario_SingleW * (MarioFrame+1) / Mario_AllW,
				1.0f);

	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);

	//////////////Pocket//////////////
	
	if(Mario.getPocket() == Nitrogen)
	{
		glBindTexture(GL_TEXTURE_2D, NitrogenTexture);
		glPushMatrix();
		SetTexParameter();
		DrawObject(	window_width - 50.0f + camera_L,				
					0.0f,
					window_width - 10.0f + camera_L,				
					40.0f,
					0.0f,								
					0.0f,
					1.0f,								
					1.0f);
		glPopMatrix();
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	//************************************************************************************************************
		if(camera_R >= 580 * 19.0f||Mario.getlife() < 0)
	{
		GameOver();		
	}
	glPopAttrib();
	glutSwapBuffers();
}


void TimerFunction(int value)
{ 	
	
	if (!GamePause)
	{
		// ACTION DECIDE		
		if		(Mario.getMovingY() == Y_jumping)		Mario.setAction(jump);
		else if (Mario.getMovingX() == X_normal)		Mario.setAction(normal);
		else if (Mario.getMovingX() == X_rushing)		Mario.setAction(rush);
		else if (Mario.getMovingY() == X_jump_rush)		Mario.setAction(jump_rush);
		else if (Mario.getAction() == dead)				Mario.setAction(dead);
		else											Mario.setAction(star);
		
		if (Mario.getlife() >= 0)
		{
			// ROCKMAN EVENT
			switch (Mario.getAction())
			{
			case normal:
				FalingDisable = false;
				if (MarioFrameCount % 5 == 0) MarioFrame++;
				if (MarioFrame >= 4)
				{	
					MarioFrame = 0;
					MarioFrameCount = 1;
				}
				Mario.Move();
				MarioFrameCount++;
				
				//printf("%d",Mario.getUpPower());
				break;

		  case jump:
			//case JUMPSHOT:

				FalingDisable = true;
                //printf("%d\n",Mario.getPosition());
				if (marioJumpFrameCount < 2)
				{
					if (marioJumpFrameCount <=  0)	Mario.Move(up/*,	    (1.0f / marioJumpFrameCount) * 25.0f */);
					else						    Mario.Move(down/*,	(1.0f / (49 - marioJumpFrameCount)) * 25.0f*/);
					//Mario.Move();

					if (marioJumpFrameCount % 6 == 0) marioJumpFrame++;
					marioJumpFrameCount++;
				}
				else MovingCheck();
				if(marioJumpFrameCount >= 2)
					marioJumpFrameCount = 0;
				
				Mario.Move();
				break;

			/*case FALLING:
			//case FALLSHOT:

				FalingDisable = true;
				EnergyDisable = false;
				InjuredDisable = false;

				CommonFrame = 7;
				Rockman.Move();

				break;*/

			case rush:
			//case jump_rush:
			

				FalingDisable = Mario.getPosition() == AIR ? true : false;
				Mario.Move();
				speedTimeCount++;
				marioRushFrameCount++;
				if (marioRushFrameCount < 4)
				{
					if (marioRushFrameCount % 2 == 0) marioRushFrame++;

					if (rushStateCheck && speedTimeCount > 0 && marioRushFrame > 4)
					{
						marioRushFrame = 0;
					}
					else if (marioRushFrame == 3) marioRushFrame++;

					//Mario.Move();
					
				}
				//else 
				MovingCheck();
				if(speedTimeCount >= SPEEDTIME || rushStateCheck == false)
				{
					if(Mario.getAction() == jump_rush)
					{
						Mario.setAction(jump);
					}
					else
					{
						Mario.setAction(normal);
					}
					Mario.setCarSpeed(initSpeed);
					speedTimeCount = 0;
					Mario.setAttack(1);
					jumpStateCheck = false;
				}
				else
				{
					Mario.setAction(rush);
					Mario.setMovingX(X_rushing);
					jumpStateCheck = true;
				}

				
				

				break;

			case dead:
				
				exit(0);



			/*case START:

				FalingDisable = true;
				EnergyDisable = true;
				InjuredDisable = true;

				if (CommonFrame < 17)
				{
					if (Rockman.Position() != GROUND) Rockman.Move(DOWN, 12.5f);
					else if (CommonFrameCount % 4 == 0) CommonFrame++;

					CommonFrameCount++;
				}
				else MovingCheck();

				break;*/
			}
			
			// INJURED COOLDOWN


			

		}

		// ROCKMAN DEAD
		else
		{
			Mario.setCarSpeed(0);
			
			
			
		}
		


/*		// ENEMY FRAME
		if (EnemyMoveCount % 4 == 0) EnemyMoveFrame++;
		if (EnemyMoveFrame > 5) EnemyMoveFrame = 0;
		EnemyMoveCount++;

		// ENEMY EVENT
		for (int i = 0; i < ENEMY_NUM; i++)
		{
			if (Enemy[i].Action() == WALKING) Enemy[i].Move();
			else if(Enemy[i].Action() == VICTORY)
			{
				if (EnemyBreakCount[i] % 4 == 0) EnemyBreakFrame[i]++;
				if (EnemyBreakFrame[i] > 15) Enemy[i].Action(IDLE);
				EnemyBreakCount[i]++;	
			}
		}*/
		////////////////////FISH EVENT///////////////////////
		for(int i = 0; i < FishNum; i++)
		{
			if (FishFrameCount % 30 == 0) FishFrame++;
			if (FishFrame >= 4)
			{	
				FishFrame = 0;
				FishFrameCount = 1;
			}
			FishFrameCount++;
		}
		////////////////RED PLANT EVENT//////////////////
		for(int i = 0; i < PlantNum; i++)
		{
			if (RPlantFrameCount % 30 == 0) RPlantFrame++;
			if (RPlantFrame >= 2)
			{	
				RPlantFrame = 0;
				RPlantFrameCount = 1;
			}
			RPlantFrameCount++;
		}
		////////////////GREEN PLANT EVENT//////////////////
		for(int i = 0; i < PlantNum; i++)
		{
			if (GPlantFrameCount % 30 == 0) GPlantFrame++;
			if (GPlantFrame >= 2)
			{	
				GPlantFrame = 0;
				GPlantFrameCount = 1;
			}
			GPlantFrameCount++;
		}
		////////////////RED TURTLE EVENT//////////////////
		for(int i = 0; i < RTurtleNum; i++)
		{
			if (RTurtleFrameCount % 30 == 0) RTurtleFrame++;
			if (RTurtleFrame >= 2)
			{	
				RTurtleFrame = 0;
				RTurtleFrameCount = 1;
			}
			RTurtleFrameCount++;
		}

		////////////////GREEN TURTLE EVENT////////////////
		for(int i = 0; i < GTurtleNum; i++)
		{
			if (GTurtleFrameCount % 30 == 0) GTurtleFrame++;
			if (GTurtleFrame >= 2 )
			{	
				GTurtleFrame = 0;
				GTurtleFrameCount = 1;
			}
			GTurtleFrameCount++;
		}

		///////////////////COIN EVENT///////////////////
		for(int i = 0; i < CoinNum; i++)
		{
			if (CoinFrameCount % 400 == 0) CoinFrame++;
				if (CoinFrame >= 12)
				{	
					CoinFrame = 0;
					CoinFrameCount = 1;
				}
				CoinFrameCount++;
		}

		//////////////SPEED UP BOARD EVENT///////////////////
		for(int i = 0; i < SpeedUpBoardNum; i++)
		{
			if (SpeedUpBoardFrameCount % 100 == 0) SpeedUpBoardFrame++;
				if (SpeedUpBoardFrame >= 2)
				{	
					SpeedUpBoardFrame = 0;
					SpeedUpBoardFrameCount = 1;
				}
				SpeedUpBoardFrameCount++;
		}
	}
		
	glutPostRedisplay();
	glutTimerFunc(REFRESH_TIMER, TimerFunction, 1);
}
void Keyboard(unsigned char key, int x, int y)
{
	switch (key){

		// ESC DOWN
		case 27:
             
             
             
			//GamePause = !GamePause;
			break;

		// JUMP BUTTON DOWN
		case ' ':
			if(!jumpStateCheck &&  !rushStateCheck){//&& Mario.getPosition() != AIR
				Mario.Jump();
				MarioFrame = 0;
				MarioFrameCount = 1;
				
				if(Mario.getAction()==rush)
				{
					Mario.setAction(jump_rush);
					Mario.setMovingX(X_jump_rush);
					Mario.setMovingY(Y_jump_rush);
				}
				else
				{
					Mario.setAction(jump);
					Mario.setMovingX(X_jumping);
					Mario.setMovingY(Y_jumping);
				}
				
				Mario.setupPower(3);
			}
			jumpStateCheck = true;
			break;

		// CONTINUOUS SHOT BUTTON DOWN
		case 'Z':
		case 'z':
			 
			if(!rushStateCheck && speedTimeCount == 0 && Mario.getPocket() == Nitrogen && !jumpStateCheck){
				if(Mario.getAction() == jump)
				{
					Mario.setAction(jump_rush);
					Mario.setMovingX(X_jump_rush);
					Mario.setMovingY(Y_jump_rush);
				}
				else
				{
					Mario.setAction(rush);
					Mario.setMovingX(X_rushing);
					Mario.setMovingY(Y_rushing);
				}
				initSpeed = Mario.getCarSpeed(); //保存遠使速度
				Mario.Rush();
				Mario.setCarSpeed(MOVING_X_SPEED[X_rushing]);//射為衝刺速度
				Mario.setAttack(3);
				MarioFrame = 0;
				MarioFrameCount = 1;
			}
			rushStateCheck = true;
			break;



	}
}


void KeyboardUp(unsigned char key, int x, int y)
{
	switch (key){

		// JUMP BUTTON UP
		case ' ':
			if(jumpStateCheck){
				//QAQ
			}
			jumpStateCheck = false;
			break;

		case 'Z':
		case 'z':
			if(rushStateCheck){

			}
			rushStateCheck = false;
			break;

		// CONTINUOUS SHOT BUTTON UP
		

		// SHOT BUTTON DOWN
		

		// DASH BUTTON UP


		// NOVA SPRIKE BUTTON UP
		
	}
}

void SpecKeyboard(int key, int x, int y)
{
	switch (key){
		case GLUT_KEY_DOWN:
			break;
		case GLUT_KEY_UP:
			break;

		// ← BUTTON DOWN
		case GLUT_KEY_LEFT:
		
			break;

		// → BUTTON DOWN
		case GLUT_KEY_RIGHT:
		
			break;

		// F1 DOWN
		case GLUT_KEY_F1:
			/*FullScreen = !FullScreen;
			if (FullScreen) glutFullScreen();
			else
			{
				glutReshapeWindow(640, 480);
				glutPositionWindow((GetSystemMetrics(SM_CXSCREEN) - 640) / 2, (GetSystemMetrics(SM_CYSCREEN) - 480) / 2);
			}*/
			break;

		// F5 DOWN
	
	}
}

void SpecKeyboardUp(int key, int x, int y)
{
	switch (key){
		case GLUT_KEY_DOWN:
			break;
		case GLUT_KEY_UP:
			break;

		// ← BUTTON UP
		case GLUT_KEY_LEFT:
	
			break;

		// → BUTTON UP
 		case GLUT_KEY_RIGHT:
	
			break;
	}
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(window_width, window_height);
	glutCreateWindow("GO GO MARIO");
	glutPositionWindow((GetSystemMetrics(SM_CXSCREEN) - window_width) / 2, (GetSystemMetrics(SM_CYSCREEN) - window_height) / 2);
   	
   	
   	glutDisplayFunc(RenderScene);//OpenGL的繪圖動作都寫在它所指定的自定函式(也就是RenderScene)	
	glutReshapeFunc(ChangeSize);
	glutTimerFunc(REFRESH_TIMER, TimerFunction, 1);
	glutKeyboardFunc(Keyboard);
	glutKeyboardUpFunc(KeyboardUp);
	/*glutSpecialFunc(SpecKeyboard);
	glutSpecialUpFunc(SpecKeyboardUp);
*/
	InitGL();
	
	
	glutMainLoop();
	return 0;
}
