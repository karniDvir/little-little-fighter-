#include "ThrowableObj.h"
ThrowableObj::ThrowableObj() : m_lifeTime(0), m_throwTime(0), m_ballOver(false)
{}
//this function will init the throwable according to the next parameters:
// position, scale, the attack name and which team is the throwable is part of
//------------------------------------------------
void ThrowableObj::initThrowable(const sf::Vector2f& position, const sf::Vector2f& scale, 
					const std::string& attackName , bool enemy_team)
{
	setTexture(DataManager::instence().getTexture(attackName));
	initRectangle(RECTANGLE_ROWS, RECTANGLE_COLS);
	setScale(scale);
	auto diraction = scale;
	diraction.y = 0;
	setDiraction(diraction);
	sf::Vector2f newPosition = position;
	newPosition.x += diraction.x * 40;
	setPositionSprite(newPosition);
	setEnemyTeam(enemy_team);
	rand() % 2 ? playSound(DataManager::instence().getGameMusic().throwAttack1) : 
		playSound(DataManager::instence().getGameMusic().throwAttack2);
}
//this function will return if the throawable is still active
//------------------------------------------------
bool ThrowableObj::IsTimeLeft() const
{
	return m_lifeTime > m_throwTime;
}
//this function will handle the animation of the throawble
//------------------------------------------------
void ThrowableObj::handleRectable(const sf::Time& deltaTime)
{
	static bool revers;
	if (deltaTime.asMilliseconds() < 100)
		return;
	if (getRectangle().left <= 0)
	{
		AddLeftRectangle(getTileWidth());
		revers = false;
	}
	else if (getRectangle().left >= getTileWidth() * 3)
	{
		if (getRectangle().top != 0)
			m_ballOver = true;
		AddLeftRectangle(-getTileWidth());
		revers = true;
	}
	else if (!revers)
		AddLeftRectangle(getTileWidth());
	else if (revers)
		AddLeftRectangle(-getTileWidth());
	setTextureRect(getRectangle());

}
//this function will handle the move of the throwable
//-------------------------------------------------
void ThrowableObj::move(const sf::Time& deltaTime)
{
	handleRectable(deltaTime);
	m_throwTime++;
	if (m_lifeTime <= m_throwTime + 30)
		ObjectTimeOver();
	moveSprite(getDiraction(), getSpeed());
}

//------------------------------------------------
void ThrowableObj::setLifeTime(const int& time)
{
	m_lifeTime = time;
}
//this function will destroy the ball if its not active anymore
//------------------------------------------------
void ThrowableObj::destroyBall()
{
	SetTopRectangle(HIT*getTileHeight());
	setAttackPower(0);
	setSpeed(0);
}
//------------------------------------------------
void ThrowableObj::ObjectTimeOver()
{
	SetTopRectangle(TIME_OVER * getTileHeight());
}
//this function will add the next parameters to the throwable
//------------------------------------------------
void ThrowableObj::addThrowableParemeters(const int& lifeTime, const int& power, const float& speed)
{
	setLifeTime(lifeTime);
	setAttackPower(power);
	setSpeed(speed);
}
//------------------------------------------------
bool ThrowableObj::isAttackOver() const
{
	return m_ballOver;
}