#include "freeglut/glut.h"
//#include <GL/glut.h>
#include <string>
//using namespace std; //it will get "ambiguous error"


const GLfloat	POSITION_FLOOR		= 10.0f;//change

// Texture Size
const GLfloat Mario_AllW			= 814.0f;
const GLfloat Mario_SingleW			= 203.5f;
const GLfloat Coin_AllW				= 360.0f;
const GLfloat Coin_SingleW			= 30.0f;
const GLfloat SpeedUpBoard_AllW		= 280.0f;
const GLfloat SpeedUpBoard_SingleW	= 140.0f;
const GLfloat G_Turtle_AllW			= 300.0f;
const GLfloat G_Turtle_SingleW		= 50.0f;
const GLfloat R_Turtle_AllW			= 200.0f;
const GLfloat R_Turtle_SingleW		= 50.0f;
const GLfloat G_Plant_AllW			= 100.0f;
const GLfloat G_Plant_SingleW		= 50.0f;
const GLfloat R_Plant_AllW			= 100.0f;
const GLfloat R_Plant_SingleW		= 50.0f;
const GLfloat Fish_AllW				= 200.0f;
const GLfloat Fish_SingleW			= 50.0f;
const GLfloat Life_AllW				= 624.0f;
const GLfloat Life_SingleW			= 125.0f;


// Object Number
const int BlockNum = 4;
const int PlantNum = 10;
const int RTurtleNum = 3;
const int GTurtleNum = 3;
const int TurtleNum = RTurtleNum + GTurtleNum;
const int FishNum = 3;
const int SpeedUpBoardNum = 5;
const int CoinNum = 50;
const int NitrogenNum = 5;

/****************************************************************************************************/
// STATE MARIO
/****************************************************************************************************/
enum marioDirectionState		 {none,					up = 1,				down = -1};
enum marioActionState			 {star,					normal,				jump,				rush,				jump_rush,		     dead};
enum marioMoveStateX			 {X_normal,				X_jumping,			X_rushing,			X_jump_rush};
enum marioMoveStateY			 {Y_normal,				Y_jumping,			Y_rushing,			Y_jump_rush};
enum marioMoveSpeedX			 {S_X_normal ,			S_X_jump,			S_X_rush ,			S_X_jump_rush };
enum marioMoveSpeedY			 {S_Y_normal = 0,		S_Y_jump ,			S_Y_rush ,			S_Y_jump_rush };
enum marioPocket				 {empty = 0 ,Nitrogen = 1}; //Nitrogen = ´á®ð
enum marioPositionState		     {GROUND,AIR};

/****************************************************************************************************/
// STATE TURTLE
/****************************************************************************************************/
enum turtleDirectionState		 {t_up = 1,				t_down = -1,		t_left=2,			 t_right=-2};
enum turtleActionState			 {t_normal,				t_jump,				t_falling,		     t_dead};//mixed:dead
enum turtleMoveStateX			 {t_X_normal,			t_X_jumping};
enum turtleMoveStateY			 {t_Y_normal,			t_Y_jumping};
enum turtleMoveSpeedX			 {t_S_X_normal = 10,	t_S_X_jump = 0};
enum turtleMoveSpeedY			 {t_S_Y_normal = 0,		t_S_Y_jump = 5};
enum turtlePositionState		 {t_GROUND,				t_AIR};
enum turtleColor				 {t_Color_Red,			t_Color_Green};

const struct RTurtleData{
	GLfloat X[RTurtleNum];
	GLfloat Y[RTurtleNum];
	GLfloat BOUND_L[RTurtleNum];
	GLfloat BOUND_R[RTurtleNum];
}RTurtleTexture = {
	{	1160.0f,	5800.0f,	9280.0f},
	{	40.0f,	40.0f,	40.0f},
	{	25.0f,	42.0f,	100.0f},
	{	75.0f,	82.0f,	200.0f}
};

// ENEMY MOVING TEXTURE
const struct RTurtleDataMoveTexture{
	GLfloat X[6];
	GLfloat Y[6];
	GLfloat WIDTH[6];
	GLfloat HEIGHT[6];
}TEXTURE_RT_MOVE = {{0.0f,	50.0f,	100.0f,	150.0f,	200.0f,	250.0f},
{	32.0f,	32.0f,	32.0f,	32.0f,	32.0f,	32.0f},
{	50.0f,	50.0f,	50.0f,	50.0f,	50.0f,	50.0f},
{	32.0f,	32.0f,	32.0f,	32.0f,	32.0f,	32.0f}};

const struct GTurtleData{
	GLfloat X[GTurtleNum];
	GLfloat Y[GTurtleNum];
	GLfloat BOUND_L[GTurtleNum];
	GLfloat BOUND_R[GTurtleNum];
}GTurtleTexture = {
	{	2320.0f,	4640.0f,	6960.0f},
	{	40.0f,	40.0f,	40.0f},
	{	25.0f,	42.0f,	100.0f},
	{	75.0f,	82.0f,	200.0f}
};

// ENEMY MOVING TEXTURE
const struct GTurtleDataMoveTexture{
	GLfloat X[6];
	GLfloat Y[6];
	GLfloat WIDTH[6];
	GLfloat HEIGHT[6];
}TEXTURE_GT_MOVE = {{0.0f,	50.0f,	100.0f,	150.0f,	200.0f,	250.0f},
{	32.0f,	32.0f,	32.0f,	32.0f,	32.0f,	32.0f},
{	50.0f,	50.0f,	50.0f,	50.0f,	50.0f,	50.0f},
{	32.0f,	32.0f,	32.0f,	32.0f,	32.0f,	32.0f}};


/****************************************************************************************************/
// STATE PLANT
/****************************************************************************************************/
enum plantDirectionState		 {p_up = 1,				p_down = -1};
enum plantActionState			 {p_normal,				p_jump,				p_falling,		     p_dead};//mixed:dead
enum plantMoveStateX			 {p_X_normal,			p_X_jumping};
enum plantMoveStateY			 {p_Y_normal,			p_Y_jumping};
enum plantMoveSpeedX			 {p_S_X_normal = 10,	p_S_X_jump = 0};
enum plantMoveSpeedY			 {p_S_Y_normal = 0,		p_S_Y_jump = 5};
enum plantPositionState		     {p_GROUND,				p_UnderGround};
enum plantColor					 {p_Color_Red,			p_Color_Green};

const struct PlantData
{
	GLfloat X[10];
	GLfloat Y[10];
	GLfloat WIDTH[10];
	GLfloat HEIGHT[10];
}TEXTURE_P = {{880.0f,	1380.0f,	1880.0f,	2380.0f,	2880.0f,	3380.0f,	3880.0f,	4380.0f,	4880.0f,	5380.0f},
			{  230.0f,	230.0f,		230.0f,		230.0f,		230.0f,		230.0f,		230.0f,		230.0f,		230.0f,		230.0f},
			{	50.0f,	50.0f,		50.0f,		50.0f,		50.0f,		50.0f,		50.0f,		50.0f,		50.0f,		50.0f},
			{	33.0f,	33.0f,		33.0f,		33.0f,		33.0f,		33.0f,		33.0f,		33.0f,		33.0f,		33.0f}};

/****************************************************************************************************/
// STATE FISH
/****************************************************************************************************/
enum fishDirectionState			 {f_up = 1,				f_down = -1,		f_left=2,			 f_right=-2};
enum fishActionState			 {f_normal,				f_jump,				f_falling,		     f_dead};//mixed:dead
enum fishMoveStateX				 {f_X_normal,			f_X_jumping};
enum fishMoveStateY				 {f_Y_normal,			f_Y_jumping};
enum fishMoveSpeedX				 {f_S_X_normal = 10,	f_S_X_jump = 0};
enum fishMoveSpeedY				 {f_S_Y_normal = 0,		f_S_Y_jump = 5};
enum fishPositionState		     {f_GROUND,				f_AIR};

const struct FishData{
	GLfloat X[FishNum];
	GLfloat Y[FishNum];
	GLfloat BOUND_L[FishNum];
	GLfloat BOUND_R[FishNum];
}TextureFish = {
	{	3480.0f,	8120.0f,	10440.0f},
	{	40.0f,	40.0f,	40.0f},
	{	25.0f,	42.0f,	100.0f},
	{	75.0f,	82.0f,	200.0f}};

	// ENEMY MOVING TEXTURE
	const struct FishDataMoveTexture{
		GLfloat X[6];
		GLfloat Y[6];
		GLfloat WIDTH[6];
		GLfloat HEIGHT[6];
	}TEXTURE_F_MOVE = {{0.0f,	50.0f,	100.0f,	150.0f,	200.0f,	250.0f},
	{	32.0f,	32.0f,	32.0f,	32.0f,	32.0f,	32.0f},
	{	50.0f,	50.0f,	50.0f,	50.0f,	50.0f,	50.0f},
	{	32.0f,	32.0f,	32.0f,	32.0f,	32.0f,	32.0f}};
/****************************************************************************************************/
// STATE COIN
/****************************************************************************************************/
enum coinState					 {nohave,				have};//ch

/****************************************************************************************************/
// STATE N2
/****************************************************************************************************/
enum nitrogenState				 {n_nohave,				n_have};//ch
/****************************************************************************************************/
const GLfloat MARIO_CONTECT_WIDTH[]		= { 30.0f,		30.0f,		30.0f,		30.0f};
const GLfloat MARIO_CONTECT_HEIGHT[]	= { 30.0f,		30.0f,		30.0f,		30.0f};
const GLfloat MOVING_X_SPEED[]		    = {	0.0f,		0.0f,		20.0f,		20.0f};
const GLfloat MOVING_Y_SPEED[]			= {	0.0f,		-5.0f,		0.0f,		-5.0f};
const int SPEEDTIME = 50; //½Ä¨ë®É¶¡


//const GLfloat	BLOCK_TEXT_WIDTH[BlockNum]		= {0.0f};//,		96.0f,			45.0f,		0.0f};
//const GLfloat	BLOCK_TEXT_HEIGHT[BlockNum]		= {0.0f};//,		45.0f,			45.0f,		0.0f};



struct Coordinates {
	GLfloat X;
	GLfloat Y;
};





const int BLOCK_HIGHT = 15;
const int BLOCK_WEIGHT = 48;
const int BLOCK_TYPE_NUM = 1;
const std::string	BLOCK_TEXT_FILE[BLOCK_TYPE_NUM] = {"block.bmp"};

const struct BlockData{
	GLfloat X[BlockNum];
	GLfloat Y[BlockNum];
}TEXTURE_B = {{	0.0f,	0.0f,   150.0f, 350.0f},
			  {	0.0f,	450.0f, 350.0f, 200.0f 	}};

const int COIN_HIGHT = 22;
const int COIN_WEIGHT = 30;
const struct CoinData
{
	GLfloat X[CoinNum];
	GLfloat Y[CoinNum];
}TEXTURE_COIN = {{	500.0f,		525.0f,		545.0f,		565.0f,		725.0f,		800.0f,		845.0f,		935.0f,		960.0f,		1025.0f,	1075.0f,	1125.0f,	1160.0f,	1350.0f,	1550.0f,	1580.0f,	1645.0f,	1680.0f,	1725.0f,	1925.0f,	2020.0f,	2845.0f,	2900.0f,	3305.0f,	3345.0f,	3370.0f,	3410.0f,	3620.0f,	3725.0f,	4225.0f,	4325.0f,	4445.0f,	4920.0f,	5525.0f,	6025.0f,	6040.0f,	6145.0f,	6500.0f,	7020.0f,   7055.0f,		7225.0f,	8033.0f,	8145.0f,  8220.0f,	 8300.0f,	9025.0f,	9333.0f,	9545.0f,	 9870.0f,	 10000.0f},
                 {	160.0f,		150.0f,		140.0f,		150.0f,		330.0f,		350.0f,		330.0f,		150.0f,		150.0f,		250.0f,		300.0f,		350.0f,		380.0f,		200.0f,		100.0f,		150.0f,		325.0f,		380.0f,		350.0f,		200.0f,		200.0f,		125.0f,		350.0f,		320.0f,		345.0f,		310.0f,		270.0f,		150.0f,		50.0f,		100.0f,		105.0f,		125.0f,		250.0f,		200.0f,		180.0f,		190.0f,		325.0f,		180.0f,		250.0f,	   320.0f,		100.0f,		290.0f,		260.0f,	  230.0f,	 255.0f,	320.0f,		250.0f,		125.0f,		 225.0f,	 120.0f}};
	 				                                                //5    										                //10            										    //15                        								//20		                            					//25					                            		//30														//35           								               //40		                             		             //45											        	 //50               										                            										                            										                            										                            										                            		
const int N2_HIGHT = 44;
const int N2_WEIGHT = 44;
const struct N2Data
{
	GLfloat X[NitrogenNum];
	GLfloat Y[NitrogenNum];
}TEXTURE_N2 = {{	300.0f,		3500.0f,	5000.0f,	6800.0f,	8000.0f},
				{	240.0f,		380.0f,		240.0f,		180.0f,		300.0f}};

const int SPEEDUPB_HIGHT = 43;
const int SPEEDUPB_WEIGHT = 140;
const struct SpeedUpBoardData
{
	GLfloat X[SpeedUpBoardNum];
	GLfloat Y[SpeedUpBoardNum];
}TEXTURE_SpeedUp = {{	2500.0f,	3900.0f,	5200.0f,	7700.0f,	8500.0f},
					{	330.0f,		440.0f,		220.0f,		150.0f,		300.0f}};
