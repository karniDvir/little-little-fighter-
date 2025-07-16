#include "DynamicObj.h"
#include <iostream>
//----------------------------------------------
DynamicObj::DynamicObj()
	: m_recTexture(sf::IntRect(0, 0, 80, 80)),
	m_speed(1),
	m_blocked(false)
{}
//----------------------------------------------
sf::IntRect DynamicObj::getRectangle() const
{
	return m_recTexture;
}
//-----------------------------------------------
sf::Vector2f DynamicObj::getDiraction() const
{
	return m_diraction;
}
//----------------------------------------------
float DynamicObj::getSpeed() const
{
	return m_speed;
}
//-----------------------------------------------
void DynamicObj::setSpeed(float speed)
{
	m_speed = speed;
}
//----------------------------------------------
void DynamicObj::setDiraction(const sf::Vector2f& diraction)
{
	m_diraction = diraction;
}
//--------------------------------------------
void DynamicObj::setRecTangle()
{
	setTextureRect(getRectangle());
	setOrgin();
}
//--------------------------------------------
void DynamicObj::SetTopRectangle(int col)
{
	m_recTexture.top = col;
}
//--------------------------------------------
void DynamicObj::setLeftRectngle(int row)
{
	m_recTexture.left = row;
}
//--------------------------------------------
void DynamicObj::AddLeftRectangle(int row)
{
	m_recTexture.left += row;
}
//--------------------------------------------
void DynamicObj::AddTopRectangle(int col)
{
	m_recTexture.top += col;
}
//--------------------------------------------
void DynamicObj::ResetLeftRectngle()
{
	m_recTexture.left = 0;
}
//---------------------------------------------
void DynamicObj::setRectangleSize(int height, int width)
{
	m_recTexture.height = height;
	m_recTexture.width = width;
}
//----------------------------------------------
int DynamicObj::getTileHeight() const
{
	return m_recTexture.height;
}
//----------------------------------------------
int DynamicObj::getTileWidth() const
{
	return m_recTexture.width;
}
//----------------------------------------------
void DynamicObj::initRectangle(const int& rowSize, const int& colSize)
{
	sf::Vector2f temp = getGlobalBounds();
	temp.x /= rowSize;
	temp.y /= colSize;
	setRectangleSize(int(temp.x), int(temp.y));
	setRecTangle();
	setOrgin();

}
//----------------------------------------------------
int DynamicObj::getAttackPower() const
{
	return m_attackPower;
}
//----------------------------------------------------
void DynamicObj::setAttackPower(const int& power)
{
	m_attackPower = power;
}
//----------------------------------------------------
void DynamicObj::setBlocked(const bool& isBlocked)
{
	m_blocked = isBlocked;
}
//----------------------------------------------------
bool DynamicObj::isBlocked() const
{
	return m_blocked;
}
//-----------------------------------------------
bool DynamicObj::areEnemyTeam() const
{
	return m_enemyTeam;
}
//----------------------------------------------------
void DynamicObj::setEnemyTeam(bool enemy_team)
{
	m_enemyTeam = enemy_team;
}