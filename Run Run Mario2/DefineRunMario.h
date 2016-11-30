#include "Object_class.h"
#include "kglTexture.h"

const int REFRESH_TIMER = 17;

bool GamePause			= false;
int SCALE				= 1.5f;
marioDirectionState LastDir	= none;

//Scene define
int Gravity = 5; //地心引力
int blockPower = 5;//方塊反抗引力的力量
int blockclasscounter=0;	
const int counter=123;
const int counter1=23;
const int totalBlockNum=292;
int GetCoinNum = 0;

// TEXTURE
GLuint MarioTexture;
GLuint RedPlantTexture;
GLuint GreenPlantTexture;
GLuint RedTurtleTexture;
GLuint GreenTurtleTexture;
GLuint FishTexture;
GLuint LifeTexture;
GLuint NitrogenTexture;
GLuint BackGround;
GLuint BlockTexture;
GLuint SpeedUpBoardTexture;
GLuint CoinTexture;
GLuint DeadTexture;
GLuint WinTexture;
GLuint FailTexture;

// CLASS
MarioClass			Mario;
TurtleClass			GTurtle[GTurtleNum];
TurtleClass			RTurtle[RTurtleNum];
PlantClass			Plant[PlantNum];
FishClass			Fish[FishNum];
BlockClass			Block[totalBlockNum];
SpeedUpBoardClass	SpeedUpBoard[SpeedUpBoardNum];
NitrogenClass		N2[NitrogenNum];
CoinClass			Coin[CoinNum];

// FRAME
int MarioFrame					= 0;
int MarioFrameCount				= 1;
int TurtleMoveFrame				= 0;
int TurtleMoveCount				= 1;
int RTurtleFrame				= 0;
int RTurtleFrameCount			= 1;		
int GTurtleFrame				= 0;
int GTurtleFrameCount			= 1;
int RPlantFrame					= 0;
int RPlantFrameCount			= 1;
int GPlantFrame					= 0;
int GPlantFrameCount			= 1;
int CoinFrame					= 0;
int CoinFrameCount				= 1;
int FishFrame					= 0;
int FishFrameCount				= 1;
int SpeedUpBoardFrame			= 0;
int SpeedUpBoardFrameCount		= 1;

int marioNormalFrameCount		= 0;
int marioNormalFrame			= 1;
int marioNormalStep				= 1;

int marioJumpFrameCount				= 0;
int marioJumpFrame					= 1;

int marioRushFrameCount				= 0;
int marioRushFrame					= 1;



int marioCarSpeed = Mario.getCarSpeed();
int initSpeed;							//衝刺前的速度
int speedTimeCount = 0;					//衝刺時間
int speedBoardcheck[SpeedUpBoardNum]; //ch
int DeathCount = Mario.getlife();

bool CollisionDisable	= false;
//Mario's state
bool jumpStateCheck = false;
bool driveCarStateCheck = true;
bool rushStateCheck = false;
bool dieStateCheck = false;
bool FalingDisable		= true;
bool ControlDisable		= true;


GLfloat camera_L				= 0.0f;
GLfloat camera_R				= 640.0f;
GLfloat camera_B				= 0.0f;
GLfloat camera_T				= 480.0f;
GLfloat original_window_ratio	= 640.0f / 480.0f;

// Windows Size
int		window_width			= 640;
int		window_height			= 480;