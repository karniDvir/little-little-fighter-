#pragma once
#include <SFML/Graphics.hpp>
#include "DataManager.h"
#include "SpacielAttack.h"

class Weapon
{
public:
	Weapon();
	virtual ~Weapon() {};
	void setColdownsWeapon();
	int getSizeOfSpacielAttacks() const;
	int getManaforAttack(const int& AttackNum);
	void loadNewAttack(const SpaceilAttackStats& attacks);
	bool PreformSpacielAttack(const int& AttackNum); //karni
	void draw(sf::RenderWindow& window);
	void handleTime(const sf::Time& deltaTime);
	void setSpritePosition(const sf::Vector2f& position);
	virtual void setScale(const sf::Vector2f& scale);
	bool addWeapon(const std::string&); 
	bool IshaveThisWeapon(const std::string&) const; //karni
	std::vector<std::shared_ptr<SpacielAttack>> getActiveAttacks();
	const std::vector<std::shared_ptr<SpacielAttack>>& getSkills() const;
private:
	std::vector<std::shared_ptr<SpacielAttack>> m_attacks;
};
