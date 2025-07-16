#include "Weapon.h"
//--------------------------------------------------
Weapon::Weapon()
{}
// this function will new attaks into the spaciel attack vector
//---------------------------------------------------
void Weapon::loadNewAttack(const SpaceilAttackStats& attack)
{
	m_attacks.push_back(std::make_shared<SpacielAttack>(attack));
}
// this function will prform the attack that was rqested 
//---------------------------------------------------
bool Weapon::PreformSpacielAttack(const int& AttackNum) 
{
	if (AttackNum < m_attacks.size() && AttackNum >-1)
	{
		if (m_attacks[AttackNum]->canUse())
		{
			m_attacks[AttackNum]->setActive(true);
			m_attacks[AttackNum]->ResertRectangle();
			return true;
		}
	}
	return false;
}
// this function will draw all the active spaceil attaks of this weapon
//--------------------------------------------------
void Weapon::draw(sf::RenderWindow& window)
{
	for (auto i : m_attacks)
	{
		if (i->getActive())
		{
			i->draw(window);
		}
	}
}
//this function will set the attacks position
//-------------------------------------------------
void Weapon::setSpritePosition(const sf::Vector2f& position)
{
	for (auto i : m_attacks)
	{
		i->setPositionSprite(position);
	}
}
//-------------------------------------------------
void Weapon::setScale(const sf::Vector2f& scale)
{
	for (auto i : m_attacks)
	{
		if (!i->getActive())
			i->setScale(scale);
	}
}
//this function will handle the animation of the active objects
//-------------------------------------------------
void Weapon::handleTime(const sf::Time& deltaTime)
{
	for (auto i : m_attacks)
	{
		if (i->getActive())
		{
			i->handleRectable(deltaTime);
		}
	}
}
//this function will return copy of the vector of the active attacks
//---------------------------------------
std::vector<std::shared_ptr<SpacielAttack>> Weapon::getActiveAttacks()
{
	std::vector<std::shared_ptr<SpacielAttack>> rt;
	for (auto i : m_attacks)
	{
		if (i->getActive())
		{
			rt.push_back(i);
		}
	}
	return rt;
}
//this function will add new weapon according to reqeurst string
//----------------------------------------
bool Weapon::addWeapon(const std::string& weapon_name)
{
	SpaceilAttackStats temp = DataManager::instence().getSpacielAttackInfo(weapon_name);
	if (temp.m_Attack != -1)
	{
		for(auto i : m_attacks)
			if (i->getAttackName() == weapon_name)
			{
				i->incAttack(); // we will not add the same attack but we add a power.
				return false;
			}
		m_attacks.push_back(std::make_shared<SpacielAttack>(temp));
		return true;
	}
	return false;
}
//this function will return how much mana the resusted attak require
//----------------------------------------
int Weapon::getManaforAttack(const int& AttackNum)
{
	if (m_attacks.size() > AttackNum)
		return m_attacks[AttackNum]->getRequierdMana(); //else exeption
	return -1; 
}
//---------------------------------------
void Weapon::setColdownsWeapon()
{
	for (auto i : m_attacks)
	{
		i->incTimeForColdown();
	}
}
//---------------------------------------
int Weapon::getSizeOfSpacielAttacks() const
{
	return m_attacks.size();
}
//this function will return const & to the current skills of the weapon
//---------------------------------------
const std::vector<std::shared_ptr<SpacielAttack>>& Weapon::getSkills() const
{
	return m_attacks;
}
//this function will return if the reuested attack is already in this weapon
//---------------------------------------
bool Weapon::IshaveThisWeapon(const std::string& weapon_name) const 
{
	for (auto i : m_attacks)
		if (i->getAttackName() == weapon_name)
			return true;
	return false;
}