#include "Object_class.h"

/****************************************************************************************************/
// MARIO CLASS
/****************************************************************************************************/

MarioClass::MarioClass()
{
	m_position.X		= 100.0f;
	m_position.Y		= 40.0f;
	m_actState			= normal;    
	m_posState			= GROUND;
	m_movStateX			= X_normal;//m_SpeedX			= S_X_normal;
	m_movStateY			= Y_normal;//m_SpeedY			= S_Y_normal;//
	m_attackStrength	= 1;
	m_healthPoint		= 1;
	m_life				= 5;
	m_carSpeed			= 3;
	m_Item				= empty;
	m_coin				= 0;//ch
}

void MarioClass::Move()
{
	m_position.X += m_carSpeed ;
	m_position.Y += (m_upPower ) * m_direction;
}

void MarioClass::Move(marioDirectionState _d)
{
	if (m_posState == GROUND)
	{
		if(m_actState == rush)
		{
			m_movStateX = X_rushing;
			m_movStateY = Y_rushing;
		}
		else
		{
			m_movStateX = X_normal;
			m_movStateY = Y_normal;
		}
		m_direction = _d;
		
	}
	else if (m_posState == AIR)
	{
		if(m_actState == jump_rush)
		{
			m_movStateX = X_jump_rush;
			m_movStateY = Y_jump_rush;
		}
		else
		{
			m_movStateX = X_jumping;
			m_movStateY = Y_jumping;
		}
		m_direction = _d;

	}
}

void MarioClass::Air()
{
	m_posState = AIR;
	if(m_movStateY == Y_normal) m_movStateY = Y_jumping;
	if(m_movStateY == Y_rushing) m_movStateY = Y_jump_rush;

}

void MarioClass::Ground()
{
	m_posState = GROUND;
	if( m_movStateY == Y_jumping) m_movStateY = Y_normal;
	if( m_movStateY == Y_jump_rush) m_movStateY = Y_rushing;
	
}

void MarioClass::Jump()
{
	if(m_actState == normal) m_actState = jump;//if(m_movStateY == Y_normal) m_movStateY = Y_jumping;
	if(m_actState == rush) m_actState = jump_rush;//if(m_movStateY == Y_rushing) m_movStateY = Y_jump_rush;

	/*
				FalingDisable = true;
				EnergyDisable = false;
				InjuredDisable = false;

				if (CommonFrameCount < 47)
				{
					if (CommonFrameCount <= 24)	Rockman.Move(UP,	(1.0f / CommonFrameCount) * 25.0f );
					else						Rockman.Move(DOWN,	(1.0f / (49 - CommonFrameCount)) * 25.0f);
					Rockman.Move();

					if (CommonFrameCount % 6 == 0) CommonFrame++;
					CommonFrameCount++;
				}
				else MovingCheck();

	*/
}

void MarioClass::Rush()
{
	if(m_Item == Nitrogen)
	{
		if(m_actState == normal) m_actState = jump;//if(m_movStateY == Y_normal) m_movStateY = Y_jumping;
	    if(m_actState == rush) m_actState = jump_rush;//if(m_movStateY == Y_rushing) m_movStateY = marioMoveStateY(Y_jump_rush);
		m_Item = empty;
	}
}

/****************************************************************************************************/
// TURTLE CLASS
/****************************************************************************************************/
TurtleClass::TurtleClass()
{

	t_attackStrength		= 10;					 //攻擊力
	t_life					= 1;					 //生命值
	t_position.X			= 150.0f;				 //座標		
	t_position.Y			= 40.0f;				 //座標	
	t_actState				= t_normal;				 //移動方式
	t_posState				= t_GROUND;				 //身處位置
	t_movStateX				= t_X_normal;			 //X軸移動速度
	t_movStateY				= t_Y_normal;			 //Y軸移動速度
	t_color					= t_Color_Green;
	t_direction				= t_left;
}

void TurtleClass::Move()
{
	t_position.X += MOVING_X_SPEED[t_movStateX] * t_direction;
	t_position.Y += MOVING_Y_SPEED[t_movStateY];
}

void TurtleClass::Initialize(GLfloat _x, GLfloat _y, turtleColor _color, turtleDirectionState _dir )
{
	t_position.X	 = _x;
	t_position.Y	 = _y;
	t_color			 = _color;
	t_direction		 = _dir;
	t_attackStrength = 1;
}

void TurtleClass::Initialize(GLfloat _x, GLfloat _y)
{
	t_position.X = _x;
	t_position.Y = _y;
	t_attackStrength = 1;
}

void TurtleClass::Jump()
{
	if(t_movStateY == t_Y_normal) t_movStateY = t_Y_jumping;
}
/****************************************************************************************************/
// PLANT CLASS
/****************************************************************************************************/
PlantClass::PlantClass()
{

	p_attackStrength		= 10;					 //攻擊力
	p_life					= 1;					 //生命值
	p_position.X			= 250.0f;				 //座標		
	p_position.Y			= 40.0f;				 //座標	
	p_actState				= p_normal;				 //移動方式
	p_posState				= p_GROUND;				 //身處位置
	p_movStateX				= p_X_normal;			 //X軸移動速度
	p_movStateY				= p_Y_normal;			 //Y軸移動速度
	p_color					= p_Color_Red;

}

void PlantClass::Move()
{
	p_position.X += MOVING_X_SPEED[p_movStateX];
	p_position.Y += MOVING_Y_SPEED[p_movStateY];
}

void PlantClass::Initialize(GLfloat _x, GLfloat _y, plantColor _color)
{
	p_position.X	 = _x;
	p_position.Y	 = _y;
	p_color			 = _color;
	p_attackStrength = 1;
}

void PlantClass::Initialize(GLfloat _x, GLfloat _y)
{
	p_position.X = _x;
	p_position.Y = _y;
	p_attackStrength = 1;
}

void PlantClass::Jump()
{
	if(p_movStateY == p_Y_normal) p_movStateY = p_Y_jumping;
}

/****************************************************************************************************/
// FISH CLASS
/****************************************************************************************************/
FishClass::FishClass()
{

	f_attackStrength		= 10;					 //攻擊力
	f_life					= 1;					 //生命值
	f_position.X			= 350.0f;				 //座標		
	f_position.Y			= 40.0f;				 //座標	
	f_actState				= f_normal;				 //移動方式
	f_posState				= f_GROUND;				 //身處位置
	f_movStateX				= f_X_normal;			 //X軸移動速度
	f_movStateY				= f_Y_normal;			 //Y軸移動速度
	f_direction				= f_left;
}

void FishClass::Move()
{
	f_position.X += MOVING_X_SPEED[f_movStateX] * f_direction;
	f_position.Y += MOVING_Y_SPEED[f_movStateY];
}

void FishClass::Initialize(GLfloat _x, GLfloat _y)
{
	f_position.X = _x;
	f_position.Y = _y;
	f_attackStrength = 1;
}

void FishClass::Initialize(GLfloat _x, GLfloat _y, fishDirectionState _dir )
{
	f_position.X	 = _x;
	f_position.Y	 = _y;
	f_direction		 = _dir;
	f_attackStrength = 1;
}

void FishClass::Jump()
{
	if(f_movStateY == f_Y_normal) f_movStateY = f_Y_jumping;
}

/****************************************************************************************************/
// BLOCK CLASS
/****************************************************************************************************/
BlockClass::BlockClass()
{
	b_Position.X = 100;
	b_Position.Y = 200;
	b_attackStrength = 100;
}

void BlockClass::Initialize(GLfloat _x, GLfloat _y)
{
	b_Position.X = _x;
	b_Position.Y = _y;
	b_attackStrength = 100;
}

/****************************************************************************************************/
// SPEED UP BOARD CLASS
/****************************************************************************************************/
SpeedUpBoardClass::SpeedUpBoardClass()
{
	s_Position.X = 300;
	s_Position.Y = 0;
	s_attackStrength = 100;
}

void SpeedUpBoardClass::Initialize(GLfloat _x, GLfloat _y)
{
	s_Position.X = _x;
	s_Position.Y = _y;
	s_attackStrength = 100;
}

/****************************************************************************************************/
// Nitrogen CLASS
/****************************************************************************************************/
NitrogenClass::NitrogenClass()
{
	n_Position.X = 630;
	n_Position.Y = 240;
	n_attackStrength = 100;
}

void NitrogenClass::Initialize(GLfloat _x, GLfloat _y)
{
	n_Position.X = _x;
	n_Position.Y = _y;
	n_attackStrength = 100;
	n_state = n_nohave;//ch
}

void NitrogenClass::setNitrogenState(nitrogenState _n)//ch
{
	n_state = _n;
}

/****************************************************************************************************/
// COIN CLASS
/****************************************************************************************************/
CoinClass::CoinClass()
{
	c_Position.X = 450;
	c_Position.Y = 250;
	c_attackStrength = 0;
}

void CoinClass::Initialize(GLfloat _x, GLfloat _y)
{
	c_Position.X = _x;
	c_Position.Y = _y;
	c_attackStrength = 0;
	c_state = nohave;//ch
}

void CoinClass::setCoinState(coinState _c){//ch
		c_state = _c;
}