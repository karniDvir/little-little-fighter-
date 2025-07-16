#include "PassiveObj.h"
#include "ObjectManager.h"
//--------------------------------------------------
PassiveObj::PassiveObj() : m_timeForAutoAttack(0), m_howLongForAttack(0)
{
	setLife(300);
	setAttackPower(20);
	initLifeBar();
}
// this function will be responseble of the passive object movment and attacks
//---------------------------------------------------
void PassiveObj::move(const sf::Time & deltaTime)
{
	if (IsTimeForAttack())
	{
		resetTimeForAttack();
		ResetLeftRectngle();
		SetTopRectangle(ATTACK_MON * getTileHeight());
		setSpeed(m_attackSpeed);
		setAttackPower(30);
	}
	if (getRectangle().top != DEAD_MON * getTileHeight() && getRectangle().top != HURT_MON * getTileHeight())
		MovingObj::move(deltaTime);
	handleRectable(deltaTime);
	m_timeForAutoAttack++;
}
// this function will be resposeble of the passiveObj animation
//---------------------------------------------------
void PassiveObj::handleRectable(const sf::Time& deltaTime)
{
	if (deltaTime.asMilliseconds() < 100)
		return;
	if (getRectangle().left <= 0)
		AddLeftRectangle(getTileWidth());
	else if (getRectangle().left >= getTileWidth() *7)
	{
		if (getRectangle().top != 0)
		{
			if (getRectangle().top == DEAD_MON * getTileHeight())
			{
				setOutOfTheGame();
				return;
			}
			SetTopRectangle(WALK_MON * getTileHeight());
			setSpeed(m_baseSpeed);
			setAttackPower(20);
		}
		ResetLeftRectngle();
	}
	else 
		AddLeftRectangle(getTileWidth());

	setTextureRect(getRectangle());
}
// this function will return the cooldown of the passive Obj attacks
//---------------------------------------------------
void PassiveObj::setHowLongForAttack(const int& time)
{
	m_howLongForAttack = time;
}
//---------------------------------------------------
bool PassiveObj::IsTimeForAttack() const
{
	return m_timeForAutoAttack > m_howLongForAttack;
}
//---------------------------------------------------
void PassiveObj::resetTimeForAttack()
{
	m_timeForAutoAttack = 0;
}
//this part will initlaize the rectangle of the passive obj
//---------------------------------------------------
void PassiveObj::initPassive()
{
	initRectangle(ROW_TEXTURE_SIZE, COL_TEXTURE_SIZE);
}
//------------------------------------------
void PassiveObj::setBaseSpeed(const float& speed)
{
	m_baseSpeed = speed;
}
// this function will be resposeble of the information from the txt file
//--------------------------------------------
void PassiveObj::readInfo(const infoFromTxt& info)
{
	MovingObj::readInfo(info);
	initPassive();
	setBaseSpeed(info.speed);
	m_attackSpeed = info.SpeedDeviation;
	setHowLongForAttack(300);

}
// this function will hurt the passive Obj
//--------------------------------------
void PassiveObj::getHurt(const int& demage)
{
	MovingObj::getHurt(demage);
	setAttackPower(-1);
	PlayHurtAnimation();
}
//--------------------------------------
void PassiveObj::PlayHurtAnimation()
{
	ResetLeftRectngle();
	setSpeed(0);
	if (isDead())
		SetTopRectangle(DEAD_MON * getTileHeight());
	else
		SetTopRectangle(HURT_MON * getTileHeight());
}
//--------------------------------------
void PassiveObj::draw(sf::RenderWindow& window)
{
	GameObj::draw(window);
	drawLifeBar(window);
}