#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include "GameObj.h"
#include "ThrowableObj.h"
#include <functional>
#include <algorithm>

typedef std::shared_ptr<ThrowableObj> SharedToObj;
typedef std::function<std::shared_ptr<ThrowableObj>()> functionAttack;
typedef std::unordered_map<std::string, functionAttack> attackMap;
typedef std::vector<std::shared_ptr<ThrowableObj>>::const_iterator ThrowableIter;
typedef std::pair<ThrowableIter, ThrowableIter> ThrowableIterPair;
class AttackManager
{
public:
	std::vector<std::shared_ptr<ThrowableObj>>& getActives();
	static AttackManager& instence();
	AttackManager(const AttackManager&) = delete;
	void operator=(const AttackManager&) = delete;
	const attackMap& getAttackMap();
	void initAttackMap();
	void drawAttacks(sf::RenderWindow& window);
	void addActiveAttack(std::shared_ptr<ThrowableObj> attack);
	void moveAttacks(const sf::Time& deltaTime);
	void sort();
	const ThrowableIterPair getIterAttacks();
private:
	AttackManager() {};
	std::vector<std::shared_ptr<ThrowableObj>> m_ActiveAttacks;
	attackMap m_attackMap;
};
template<typename T>
//-----------------------------------
std::shared_ptr<ThrowableObj> createAttack()
{
	return std::make_shared<T>();
}

