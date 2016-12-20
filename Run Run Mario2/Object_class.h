#ifndef _CLASS_H_
#define _CLASS_H_

#include "ObjectData.h"
//#include "../freeglut/glut.h"
//#include <GL/glut.h>
#include <gl/freeglut.h>
/****************************************************************************************************/
// MARIO CLASS
/****************************************************************************************************/
class MarioClass
{
private:

	int							m_attackStrength;		 //�����O
	int							m_healthPoint;			 //��q
	int							m_life;					 //�ͩR��
	int							m_carSpeed;
	int							m_upPower;
	int							m_coin;//ch
	Coordinates					m_position;				 //�y��	
	marioDirectionState			m_direction;		 
	marioActionState			m_actState;				 //���ʤ覡
	marioPositionState			m_posState;				 //���B��m
	marioMoveStateX				m_movStateX;			 //X�b���ʳt��marioMoveSpeedX				m_SpeedX;				 //X�b���ʳt��
	marioMoveStateY				m_movStateY;			 //Y�b���ʳt��marioMoveSpeedY				m_SpeedY;				 //Y�b���ʳt��
	marioPocket					m_Item;					 //�D����
	
public:

	MarioClass();
	~MarioClass(){};

	GLfloat					getPositionX()			{return m_position.X;};
	GLfloat					getPositionY()			{return m_position.Y;};
	marioActionState		getAction()				{return m_actState;};
	marioPositionState		getPosition()			{return m_posState;};
	marioPocket				getPocket()				{return m_Item;};
	marioMoveStateX			getMovingX()			{return m_movStateX;};//marioMoveSpeedX			getSpeedX()				{return m_SpeedX;};
	marioMoveStateY			getMovingY()			{return m_movStateY;};//marioMoveSpeedY			getSpeedY()				{return m_SpeedY;};
	marioDirectionState		getDirection()			{return m_direction;};
	int						getCoins()				{return m_coin;};//ch	
	int						getlife()				{return m_life;};
	int						getCarSpeed()			{return m_carSpeed;};
	int						getmarioATKStrength()	{return m_attackStrength;};
	int						getUpPower()			{return m_upPower;};	

	// SET DATA
	void setCoin(int _c)								{m_coin += _c;};//ch
	void setDirection(marioDirectionState _direction)	{m_direction = _direction;};
	void setPositionY(GLfloat _y)						{m_position.Y		= _y;};
	void setPositionX(GLfloat _x)						{m_position.X		= _x;};
	void setAction(marioActionState _act)				{m_actState			= _act;};
	void setPosition(marioPositionState _pos)			{m_posState			= _pos;};
	void setPocket(marioPocket _item)					{m_Item				= _item;};
	void setMovingX(marioMoveStateX _mov)				{m_movStateX		= _mov;};//void setMovingX(marioMoveSpeedX _mov)			{m_SpeedX			= _mov;};//
	void setMovingY(marioMoveStateY _mov)				{m_movStateY		= _mov;};//void setMovingY(marioMoveSpeedY _mov)			{m_SpeedY			= _mov;};//
	void setlife(int _life)								{m_life				= _life;};
	void setAttack(int _atk)							{m_attackStrength	= _atk;};
	void setCarSpeed(int _speed)						{m_carSpeed			= _speed;};
	void setupPower(int _up)							{m_upPower			= _up;};

	// ACTION METHODS
	void Move();
	void Move(marioDirectionState);
	void Move(marioDirectionState, GLfloat);
	void Jump();
	void Rush();
	void Air();
	void Ground();

};
/****************************************************************************************************/
// TURTLE CLASS
/****************************************************************************************************/
class TurtleClass
{
private:
	int							t_attackStrength;		 //�����O
	int							t_life;					 //�ͩR��
	Coordinates					t_position;				 //�y��			 
	turtleActionState			t_actState;				 //���ʤ覡
	turtlePositionState			t_posState;				 //���B��m
	turtleMoveStateX			t_movStateX;			 //X�b���ʳt��
	turtleMoveStateY			t_movStateY;			 //Y�b���ʳt��
	turtleDirectionState		t_direction;			 //�K�Ϥ�V
	turtleColor					t_color;                 //�Q�t�C��

public:
	TurtleClass();
	~TurtleClass(){};

	GLfloat					getPositionX()			{return t_position.X;};
	GLfloat					getPositionY()			{return t_position.Y;};
	turtleActionState		getAction()				{return t_actState;};
	turtlePositionState		getPosition()			{return t_posState;};
	turtleMoveStateX		getMovingX()			{return t_movStateX;};
	turtleMoveStateY		getMovingY()			{return t_movStateY;};
	int						getlife()				{return t_life;};
	int						getATKStrength()		{return t_attackStrength;}; // mixed
	turtleColor             getColor()				{return t_color;};
	turtleDirectionState	getDirection()			{return t_direction;};

	// SET DATA
	void setPositionY(GLfloat _y)					{t_position.Y		= _y;};
	void setPositionX(GLfloat _x)					{t_position.X		= _x;};
	void setAction(turtleActionState _act)			{t_actState			= _act;};
	void setPosition(turtlePositionState _pos)		{t_posState			= _pos;};
	void setMovingX(turtleMoveStateX _mov)			{t_movStateX		= _mov;};
	void setMovingY(turtleMoveStateY _mov)			{t_movStateY		= _mov;};
	void setlife(int _life)							{t_life				= _life;};
	void setAttack(int _atk)						{t_attackStrength	= _atk;};
	void setColor(turtleColor _col)					{t_color			= _col;};
	void setDirection(turtleDirectionState _dir)	{t_direction        = _dir;};

	// ACTION METHODS
	void Jump();
	void Air();
	void Ground();
	void Initialize(GLfloat _x, GLfloat _y, turtleColor _color, turtleDirectionState _dir );
	void Initialize(GLfloat, GLfloat);
	void Move();
};

/****************************************************************************************************/
// PLANT CLASS
/****************************************************************************************************/
class PlantClass
{
private:
	int							p_attackStrength;		 //�����O
	int							p_life;					 //�ͩR��
	Coordinates					p_position;				 //�y��			 
	plantActionState			p_actState;				 //���ʤ覡
	plantPositionState			p_posState;				 //���B��m
	plantMoveStateX				p_movStateX;			 //X�b���ʳt��
	plantMoveStateY				p_movStateY;			 //Y�b���ʳt��
	plantColor					p_color;                 //�Ӫ��C��

public:
	PlantClass();
	~PlantClass(){};

	GLfloat					getPositionX()			{return p_position.X;};
	GLfloat					getPositionY()			{return p_position.Y;};
	plantActionState		getAction()				{return p_actState;};
	plantPositionState		getPosition()			{return p_posState;};
	plantMoveStateX		    getMovingX()			{return p_movStateX;};
	plantMoveStateY		    getMovingY()			{return p_movStateY;};
	int						getlife()				{return p_life;};
	int						getATKStrength()	    {return p_attackStrength;};// mixed
	plantColor              getColor()				{return p_color;};

	// SET DATA
	void setPositionY(GLfloat _y)					{p_position.Y		= _y;};
	void setPositionX(GLfloat _x)					{p_position.X		= _x;};
	void setAction(plantActionState _act)			{p_actState			= _act;};
	void setPosition(plantPositionState _pos)		{p_posState			= _pos;};
	void setMovingX(plantMoveStateX _mov)			{p_movStateX		= _mov;};
	void setMovingY(plantMoveStateY _mov)			{p_movStateY		= _mov;};
	void setlife(int _life)							{p_life				= _life;};
	void setAttack(int _atk)						{p_attackStrength	= _atk;};
	void setColor(plantColor _col)					{p_color			= _col;};

	// ACTION METHODS
	void Jump();
	void Air();
	void Ground();
	void UnderGround();
	void Initialize(GLfloat _x, GLfloat _y, plantColor _color);
	void Initialize(GLfloat, GLfloat);
	void Move();
};
/****************************************************************************************************/
// FISH CLASS
/****************************************************************************************************/
class FishClass
{
private:
	int							f_attackStrength;		 //�����O
	int							f_life;					 //�ͩR��
	Coordinates					f_position;				 //�y��			 
	fishActionState			    f_actState;				 //���ʤ覡
	fishPositionState			f_posState;				 //���B��m
	fishMoveStateX				f_movStateX;			 //X�b���ʳt��
	fishMoveStateY				f_movStateY;			 //Y�b���ʳt��
	fishDirectionState			f_direction;

public:
	FishClass();
	~FishClass(){};

	GLfloat					getPositionX()			{return f_position.X;};
	GLfloat					getPositionY()			{return f_position.Y;};
	fishActionState 		getAction()				{return f_actState;};
	fishPositionState		getPosition()			{return f_posState;};
	fishMoveStateX		    getMovingX()			{return f_movStateX;};
	fishMoveStateY		    getMovingY()			{return f_movStateY;};
	int						getlife()				{return f_life;};
	int						getATKStrength()		{return f_attackStrength;};// mixed
	fishDirectionState		getDirection()			{return f_direction;};

	// SET DATA
	void setPositionY(GLfloat _y)					{f_position.Y		= _y;};
	void setPositionX(GLfloat _x)					{f_position.X		= _x;};
	void setAction(fishActionState _act)			{f_actState			= _act;};
	void setPosition(fishPositionState _pos)		{f_posState			= _pos;};
	void setMovingX(fishMoveStateX _mov)			{f_movStateX		= _mov;};
	void setMovingY(fishMoveStateY _mov)			{f_movStateY		= _mov;};
	void setlife(int _life)							{f_life				= _life;};
	void setAttack(int _atk)						{f_attackStrength	= _atk;};
	void setDirection(fishDirectionState _dir)		{f_direction        = _dir;};

	// ACTION METHODS
	void Jump();
	void Air();
	void Ground();
	void UnderGround();
	void Initialize(GLfloat _x, GLfloat _y, fishDirectionState _dir );
	void Initialize(GLfloat, GLfloat);
	void Move();
};
/****************************************************************************************************/
// BLOCK CLASS
/****************************************************************************************************/
class BlockClass
{
private:
	// DATA
	int				b_attackStrength;
	Coordinates		b_Position;

public:

	// CONSTRUCTOR & DESTRUCTOR
	BlockClass();
	~BlockClass() {};

	// GET DATA
	GLfloat getblockAttack(void)	{return b_attackStrength;}
	GLfloat	getblockPositionX(void)	{return b_Position.X;};
	GLfloat getblockPositionY(void)	{return b_Position.Y;};

	// SET DATA & ACTION METHODS
	void Initialize(GLfloat, GLfloat);
};

/****************************************************************************************************/
// SPEED UP BOARD CLASS
/****************************************************************************************************/
class SpeedUpBoardClass
{

private:
	// DATA
	int				s_attackStrength;
	Coordinates		s_Position;

public:
	// CONSTRUCTOR & DESTRUCTOR
	SpeedUpBoardClass();
	~SpeedUpBoardClass() {};

	// GET DATA
	GLfloat getSpeedUpBoardAttack(void)	{return s_attackStrength;}
	GLfloat	getSpeedUpBoardPositionX(void)	{return s_Position.X;}
	GLfloat getSpeedUpBoardPositionY(void)	{return s_Position.Y;}

	// SET DATA & ACTION METHODS
	void Initialize(GLfloat, GLfloat);
};

/****************************************************************************************************/
// Nitrogen CLASS
/****************************************************************************************************/
class NitrogenClass
{

private:
	// DATA
	int				n_attackStrength;
	Coordinates		n_Position;
	nitrogenState   n_state;//ch

public:
	// CONSTRUCTOR & DESTRUCTOR
	NitrogenClass();
	~NitrogenClass() {};

	// GET DATA
	GLfloat getNitrogenAttack(void)	{return n_attackStrength;}
	GLfloat	getNitrogenPositionX(void)	{return n_Position.X;}
	GLfloat getNitrogenPositionY(void)	{return n_Position.Y;}
	nitrogenState getNitrogenState(void){return n_state;}

	// SET DATA & ACTION METHODS
	void Initialize(GLfloat, GLfloat);
	void setNitrogenState(nitrogenState _n);//ch
};

/****************************************************************************************************/
// COIN CLASS
/****************************************************************************************************/
class CoinClass
{
private:
	// DATA
	int				c_attackStrength;
	Coordinates		c_Position;
	coinState		c_state; //ch

public:
	// CONSTRUCTOR & DESTRUCTOR
	CoinClass();
	~CoinClass() {};

	// GET DATA
	GLfloat getCoinAttack(void)	{return c_attackStrength;}
	GLfloat	getCoinPositionX(void)	{return c_Position.X;};
	GLfloat getCoinPositionY(void)	{return c_Position.Y;};
	coinState	getCoinState(void)	{return c_state;};//ch

	// SET DATA & ACTION METHODS
	void Initialize(GLfloat, GLfloat);
	void setCoinState(coinState _c);//ch
};


#endif