#include "SpacielAttack.h"

//------------------------------------------------
SpacielAttack::SpacielAttack()
	:m_isActive(false)	 
{}
//this os the constractor of the spaciel attack, its recive a struct of infomation and 
// init the class paremeters according to the struct
//------------------------------------------------
SpacielAttack::SpacielAttack(const SpaceilAttackStats& attack)
{
	setAttackPower(attack.m_Attack);
	m_manaRequierd = attack.m_requiredMana;
	m_cooldown = attack.m_cooldownForAttack * 5;
	m_timeForColdown = m_cooldown;
	m_attackName = attack.m_attackName;
	setTexture(*attack.m_texture);
	m_isActive = false;
	initRectangle(2,7);
	setOrgin(sf::Vector2f(160, getRectangle().height * 0.50 + 25));
}
//this function will handle the animation of the spaciel attack
//------------------------------------------------
void SpacielAttack::handleRectable(const sf::Time& deltaTime)
{
	if (deltaTime.asMilliseconds() < 100)
		return;
	if (getRectangle().left >= getRectangle().width * 6)
	{
		ResetLeftRectngle();
		AddTopRectangle(getRectangle().height);
	}
	else
		AddLeftRectangle(getRectangle().width);
	if (getRectangle().top >= getRectangle().height * 2)
		m_isActive = false;
	setRecTangle();
	setOrgin(sf::Vector2f(160, getRectangle().height * 0.50 + 25));
}
//-----------------------------------------------
void SpacielAttack::ResertRectangle()
{
	ResetLeftRectngle();
	SetTopRectangle(0);
}
//-----------------------------------------------
void SpacielAttack::setActive(const bool& isActive)
{
	m_isActive = isActive;
}
//-----------------------------------------------
bool SpacielAttack::getActive() const
{
	return m_isActive;
}
//-----------------------------------------------
bool SpacielAttack::isHit() const
{
	return getRectangle().top == getRectangle().height;
}
//------------------------------------------------
int SpacielAttack::getRequierdMana() const
{
	return m_manaRequierd;
}
//this function will update the time need to do this attack again
//------------------------------------------------
void SpacielAttack::incTimeForColdown()
{
	if (m_cooldown > m_timeForColdown)
	{
		m_timeForColdown++;
	}
}
//this function will return if the attack is usable currently
//------------------------------------------------
bool SpacielAttack::canUse()
{
	if (!m_isActive)
	{
		if (m_cooldown <= m_timeForColdown)
		{
			m_timeForColdown = 0;
			return true;
		}
	}
	return false;
}
//--------------------------------------------------
const std::string& SpacielAttack::getAttackName() const
{
	return m_attackName;
}
//this function will add 5 attack to this spaceil attack
//--------------------------------------------------
void SpacielAttack::incAttack()
{
	setAttackPower(getAttackPower() + 5);
}
//this function will return the ratio between the cooldown time passed to the whole cooldown
//--------------------------------------------------
float SpacielAttack::getCooldownRatio()
{
	float tempCoolDown = m_cooldown;
	float tempTime = m_timeForColdown;
	return tempTime / tempCoolDown;
}
//this function will return if the attack used recently
//--------------------------------------------------
bool  SpacielAttack::isUsedRecently() const
{
	return m_timeForColdown < 10;
}