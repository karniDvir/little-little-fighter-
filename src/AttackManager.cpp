#include "AttackManager.h"

// AttackManager Singleton Instance
//-------------------------------------
AttackManager& AttackManager::instence()
{
	static auto manger = AttackManager();
	return manger;
}
// Initialize Attack Map
//-----------------------------------
void AttackManager::initAttackMap()
{
	m_attackMap["MagicAttack"] = createAttack<ThrowableObj>;
	m_attackMap["FireAttack"] = createAttack<ThrowableObj>;
	m_attackMap["IceAttack"] = createAttack<ThrowableObj>;
	m_attackMap["BatAttack"] = createAttack<ThrowableObj>;
	m_attackMap["SkullAttack"] = createAttack<ThrowableObj>;
}
//-----------------------------------
const attackMap& AttackManager::getAttackMap()
{
	return m_attackMap;
}
// Draw Active Attacks
//-----------------------------------
void AttackManager::drawAttacks(sf::RenderWindow& window)
{
	for (auto i : m_ActiveAttacks)
	{
		i->draw(window);
	}
}
// Add Active Attack
//-----------------------------------
void AttackManager::addActiveAttack(std::shared_ptr<ThrowableObj> attack)
{
	m_ActiveAttacks.emplace_back(attack);
}
// move the attack on the board
//-----------------------------------
void AttackManager::moveAttacks(const sf::Time& deltaTime)
{
	for (int i = 0; i < m_ActiveAttacks.size(); i++)
	{
		m_ActiveAttacks[i]->move(deltaTime);
		if (m_ActiveAttacks[i]->isAttackOver())
			m_ActiveAttacks.erase(m_ActiveAttacks.begin() + i);
	}
}
// sort for drawing by y axis order
//------------------------------------------
void AttackManager::sort()
{
	std::sort(m_ActiveAttacks.begin(), m_ActiveAttacks.end(), [](const SharedToObj& left, const SharedToObj& right)
		{
			return left->getPosition().y < right->getPosition().y;
		}
	);
}
// Get Iterator Pair for Active Attacks
//------------------------------------------
const ThrowableIterPair AttackManager::getIterAttacks()
{
	return std::make_pair(m_ActiveAttacks.begin(),m_ActiveAttacks.end());
}
//----------------------------------------------------
std::vector<std::shared_ptr<ThrowableObj>>& AttackManager::getActives()
{
	return m_ActiveAttacks;
}