#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include "collisionHandling.h"
//#include "GameObj.h"
#include <functional>
#include "MovingObj.h"
#include "PassiveObj.h"
#include "ActiveObj.h"
#include "AutoObj.h"


typedef std::shared_ptr<MovingObj> ShardToObj;
typedef std::function<std::shared_ptr<MovingObj>()> functionObject;
typedef std::unordered_map<std::string, functionObject> objectMap;
typedef std::vector<std::shared_ptr<MovingObj>>::const_iterator MovingIter;
typedef std::pair<MovingIter, MovingIter> MovingIterPair;
class ObjectManager
{
public:
	static ObjectManager& instence();
	ObjectManager(const ObjectManager&) = delete;
	void operator=(const ObjectManager&) = delete;
	const objectMap& getObjectMap();
	void initObjectMap();
	void addToEnemyObject(std::shared_ptr<MovingObj> enemy_object);
	void addToPlayerObject(std::shared_ptr<MovingObj> player_object);
	void moveObjects(const sf::Time& deltaTime);
	void addPlayer(std::shared_ptr<MovingObj> player);
	void sort();
	const MovingIterPair getItersEnemyObj();
	const MovingIterPair getItersPlayerObj();
	int getRnadomPlayerTeamMember();
	int getRnadomEnemiesTeamMember();
	const sf::Vector2f& getPositionPlayerTeamMember(int index) const;
	const sf::Vector2f& getPositionEnemiesMember(int index) const;
	void handleCollision();
	bool AreAllEnemiesKilled(const bool& enemyTeam = false) const;
	bool isDead(const int&, const bool&) const;
	void UpdatePleyerTeamPosition();
	void setNumOfEnemies();
	const int& getNumOfEnemies() const;
	void EndGame();
private:
	void handleEnemyCollision(std::shared_ptr<MovingObj> current);
	void handlePlayerCollision(std::shared_ptr<MovingObj> current);
	ObjectManager() {};
	std::vector<std::shared_ptr<MovingObj>> m_enemyObjects;
	std::vector<std::shared_ptr<MovingObj>> m_playerObjects;
	objectMap m_objectMap;
	int m_numLevelEnemies = 0;
};

template<typename T>
//-----------------------------------
std::shared_ptr<MovingObj> createObject()
{
	return std::make_shared<T>();
}

