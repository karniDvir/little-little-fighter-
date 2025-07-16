#pragma once
#include "DynamicObj.h"
#include <SFML/Graphics.hpp>
const int RECTANGLE_ROWS = 3;
const int RECTANGLE_COLS = 4;
enum 
{
	NORMAL_THROW,
	HIT,
	TIME_OVER
};

enum AttackPower
{
	MAGIC_POWER = 20,
	FIRE_POWER = 25,
	ICE_POWER = 15,
	BAT_POWER = 15,
	SKULL_POWER = 22
};

class ThrowableObj : public DynamicObj
{
public:
	ThrowableObj();
	void addThrowableParemeters(const int& lifeTime, const int& power, const float& speed);
	virtual void move(const sf::Time& deltaTime);
	void initThrowable(const sf::Vector2f& , const sf::Vector2f& , const std::string& , bool);
	bool IsTimeLeft() const;
	void handleRectable(const sf::Time& deltaTime) override;
	void setLifeTime(const int& time);
	void destroyBall();
	void ObjectTimeOver();
	bool isAttackOver() const;
private:
	int m_lifeTime;
	int m_throwTime;
	bool m_ballOver;
};

