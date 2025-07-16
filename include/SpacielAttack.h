#pragma once
#include <SFML/Graphics.hpp>
#include "DataManager.h"
#include "DynamicObj.h"

class SpacielAttack : public DynamicObj
{
public:
	SpacielAttack() ;
	SpacielAttack(const SpaceilAttackStats& attack);
	void handleRectable(const sf::Time& deltaTime) override;
	void ResertRectangle();
	int getRequierdMana() const;
	void incTimeForColdown();
	void incAttack();
	void setActive(const bool& isActive);
	bool getActive() const;
	bool canUse();
	bool isHit() const;
	bool isUsedRecently() const;
	float getCooldownRatio();
	const std::string& getAttackName() const;
private:
	std::string m_attackName;
	int m_timeForColdown;
	int m_cooldown;
	int m_manaRequierd;
	bool m_isActive;
};

