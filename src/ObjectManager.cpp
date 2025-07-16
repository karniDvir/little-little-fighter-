#include "ObjectManager.h"
// instance for singleton
//-----------------------------------
ObjectManager& ObjectManager::instence()
{
	static auto objectmanager = ObjectManager();
	return objectmanager;
}
// the object have a map where the key is a string and its return a pointer to a function 
// that will create the requested object
//------------------------------------
const objectMap& ObjectManager::getObjectMap()
{
	return m_objectMap;
}
//initalize the map
//------------------------------------
void ObjectManager::initObjectMap()
{
	m_objectMap["Julian"] = createObject<AutoObj>;
	m_objectMap["Dennis"] = createObject<AutoObj>;
	m_objectMap["Deep"] = createObject<AutoObj>;
	m_objectMap["Louis"] = createObject<AutoObj>;
	m_objectMap["Bat"] = createObject<AutoObj>;
	m_objectMap["Monkey"] = createObject<PassiveObj>;
	m_objectMap["Cow"] = createObject<PassiveObj>;
	m_objectMap["Dragon"] = createObject<PassiveObj>;
	m_objectMap["Troll"] = createObject<PassiveObj>;

}
// adding enemy object to the enemy vector
//---------------------------------------------------
void ObjectManager::addToEnemyObject(std::shared_ptr<MovingObj> enemy_object)
{
	m_enemyObjects.emplace_back(enemy_object);
}
// adding player teamate object to the player vector
//----------------------------------------------------------
void ObjectManager::addToPlayerObject(std::shared_ptr<MovingObj> player_object)
{
	m_playerObjects.emplace_back(player_object);
}
//this function will move the object of the game, will be responsble to handle 
// the vectors and the vectors objects
//-------------------------------------------------
void ObjectManager::moveObjects(const sf::Time& deltaTime)
{
	try {
		for (int i = 0; i < m_playerObjects.size(); i++)
		{
			if (m_playerObjects[i]->checkInView()) //move only visable objects
				m_playerObjects[i]->move(deltaTime);
		}
		if (m_playerObjects.empty())
		{
			DataManager::instence().setLevelStatus(GAME_OVER);
			throw std::exception("GameOver");
		}
		for (int i = 0; i < m_enemyObjects.size(); i++)
		{
			if (!m_playerObjects.empty()) {
				if (m_enemyObjects[i]->checkInView())
					m_enemyObjects[i]->move(deltaTime);
			}
		}
	}
	catch (const std::out_of_range& ex)
	{
		m_enemyObjects.clear();
	}
	catch (const std::exception& ex)
	{
		if (strcmp(ex.what(), "GameOver") == 0)
		{
			m_enemyObjects.clear();
			m_playerObjects.clear();
			throw std::exception("GameOver");
		}
	}

}
// the drawing of the objects will be based on the y coordinates, so we will sort both of the vectors in this function
// the drawing will use megre algorithm from merge sort therefor we sorting here the vecotrs 
//--------------------------------------------------------
void ObjectManager::sort()
{
	std::sort(m_enemyObjects.begin(), m_enemyObjects.end(), [](const ShardToObj& left, const ShardToObj& right)
		{
			return left->getPosition().y < right->getPosition().y;
		}
	);
	std::sort(m_playerObjects.begin(), m_playerObjects.end(), [](const ShardToObj& left, const ShardToObj& right)
		{
			return left->getPosition().y < right->getPosition().y;
		}
	);
}
//return pair of iterators of the enemy vectors (begin,end)
//-----------------------------------------------------------
const MovingIterPair ObjectManager::getItersEnemyObj()
{
	return std::make_pair(this->m_enemyObjects.begin(), this->m_enemyObjects.end());
}
//return pair of iterators of the player team vectors (begin,end)
//-----------------------------------------------------------
const MovingIterPair ObjectManager::getItersPlayerObj()
{
	return std::make_pair(this->m_playerObjects.begin(), this->m_playerObjects.end());
}
//----------------------------------------------------------
void ObjectManager::addPlayer(std::shared_ptr<MovingObj> player)
{
	m_playerObjects.push_back(player);
}
//return random index of ememy
//---------------------------------------------------------
int ObjectManager::getRnadomPlayerTeamMember()
{
	if (m_playerObjects.size() > 0)
		return rand() % (m_playerObjects.size());
	return -1;
}
//return random index of player team member
//---------------------------------------------------------
int ObjectManager::getRnadomEnemiesTeamMember()
{
	if (m_enemyObjects.size() > 0)
		return rand() % (m_enemyObjects.size());
	return -1;
}
//return position of requested player
//---------------------------------------------------------
const sf::Vector2f& ObjectManager::getPositionPlayerTeamMember(int index) const
{
	if (index >= m_playerObjects.size())
		throw std::out_of_range(" index >= player size");
	return m_playerObjects[index]->getPosition(); //exeption
}
// return position of requested enemy
//---------------------------------------------------------
const sf::Vector2f& ObjectManager::getPositionEnemiesMember(int index) const
{
	if (index >= m_enemyObjects.size())
		throw std::out_of_range("");
	return m_enemyObjects[index]->getPosition(); //exeption
}
// this function will handle all the collitions on the board from player, into passive objects,
// onto spacil attaks and more, will also know how to differ between the objects team 
//---------------------------------------------------------
void ObjectManager::handleCollision()
{
	for (auto it = m_enemyObjects.begin(); it != m_enemyObjects.end(); )
	{
		handlePlayerCollision(*it);
		if ((*it)->OutOfTheGame())
			it = m_enemyObjects.erase(it);
		else
			++it;
	}
	
	for (auto it = m_playerObjects.begin(); it != m_playerObjects.end(); )
	{
		handleEnemyCollision(*it);
		if ((*it)->OutOfTheGame())
			it = m_playerObjects.erase(it); 
		else
			++it;
	}
}
//this function will handle the collistion of the player members with enemy objects
//---------------------------------------------------------
void ObjectManager::handleEnemyCollision(std::shared_ptr<MovingObj> current)
{

	for (auto i : m_enemyObjects)
	{
		if (i->getSpriteGlobalBounds().contains(current->getPosition()))
			processCollision(*i, *current);

	}
	for (auto activeAttack : AttackManager::instence().getActives())
	{
		if (activeAttack->getSpriteGlobalBounds().contains(current->getPosition()))
			processCollision(*activeAttack, *current);
	}
	for (auto activeSpacielAttacks : current->getActiveAttacks())
	{
		for (auto i : m_enemyObjects)
			if (activeSpacielAttacks->getSpriteGlobalBounds().contains(i->getPosition())) //karni
				processCollision(*activeSpacielAttacks, *i);
	}
}
//this function will handle the collistion of the enemies with player team objects
//---------------------------------------------------------
void ObjectManager::handlePlayerCollision(std::shared_ptr<MovingObj> current)
{
	for (auto i : m_playerObjects)
	{
		if (i->getSpriteGlobalBounds().contains(current->getPosition()))
			processCollision(*i, *current);
	}
	for (auto activeAttack : AttackManager::instence().getActives())
	{
		if (activeAttack->getSpriteGlobalBounds().contains(current->getPosition()))
			processCollision(*activeAttack, *current);
	}
	for (auto activeSpacielAttacks : current->getActiveAttacks())
	{
		for (auto i : m_playerObjects)
			if (activeSpacielAttacks->getSpriteGlobalBounds().contains(i->getPosition())) //karni
				processCollision(*activeSpacielAttacks, *i);
	}
}
//----------------------------------------------------
bool ObjectManager::AreAllEnemiesKilled(const bool& enemyTeam) const
{
	if (enemyTeam)
		return m_playerObjects.empty();
	return m_enemyObjects.empty();
}
//will check if the object is dead 
// this function recive the index and the team
//----------------------------------------------------
bool ObjectManager::isDead(const int& index, const bool& in_enemy_team) const
{
	if (!in_enemy_team)
	{
		if (index >= m_enemyObjects.size() || !m_enemyObjects[index]->checkInView())
			return true;
		return m_enemyObjects[index]->isDead();
	}
	if (index >= m_playerObjects.size() || !m_playerObjects[index]->checkInView())
		return true;
	else
		return m_playerObjects[index]->isDead();

	return false;
}
//----------------------------------------------

void ObjectManager::UpdatePleyerTeamPosition()
{
	float teamSize = float(m_playerObjects.size());
	teamSize = 100 / (teamSize);
	float col = 100;
	for (auto i : m_playerObjects)
	{
		i->setPositionSprite(sf::Vector2f(col, i->getPosition().y));
		teamSize += teamSize;
	}
}
//---------------------------------------------
void ObjectManager::setNumOfEnemies( )
{
	m_numLevelEnemies = m_enemyObjects.size();
}
//---------------------------------------------
const int& ObjectManager::getNumOfEnemies() const
{
	return m_numLevelEnemies;
}
//this function cleans the vectors
//---------------------------------------------
void ObjectManager::EndGame()
{
	static bool clean = false;
	if (!clean)
	{
		m_enemyObjects.clear();
		m_playerObjects.clear();
		clean = true;
	}
}