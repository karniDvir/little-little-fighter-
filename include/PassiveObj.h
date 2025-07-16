#pragma once
#include "MovingObj.h"
#include <SFML/Graphics.hpp>
//#ifndef ObjectManager
//#include "ObjectManager.h"
//#define ObjectManager
//#endif

const int ROW_TEXTURE_SIZE = 4;
const int COL_TEXTURE_SIZE = 8;

enum
{
	WALK_MON = 0,
	HURT_MON = 1,
	ATTACK_MON = 2,
	DEAD_MON = 3
};


class PassiveObj : public MovingObj
{
public:
	PassiveObj();
	void getHurt(const int& demage) override;
	void PlayHurtAnimation();
	void draw(sf::RenderWindow& window) override;
	//--------------------------------------------
	void readInfo(const infoFromTxt& info);
	virtual void initObj() { };
	void move(const sf::Time& deltaTime) override;
	void setHowLongForAttack(const int& time);
	void handleRectable(const sf::Time& deltaTime) override;
	bool IsTimeForAttack() const;
	void resetTimeForAttack();
protected:
	void setBaseSpeed(const float& speed);
	void initPassive();
private:
	int m_howLongForAttack;
	int m_timeForAutoAttack;
	float m_baseSpeed;
	float m_attackSpeed;

};