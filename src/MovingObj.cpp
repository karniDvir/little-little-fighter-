#include "MovingObj.h"
#include "ObjectManager.h"

//this is one of the base class if the object in the game, will implemets important
// function that the objects will use

//////////////////////////////////////////////////////////

MovingObj::MovingObj() 
	: m_enemyIndex(-1),
	  m_outOfTheGame(false)
{}
//this function will be the basic move of the moving objects
//---------------------------------------------------------
void MovingObj::move(const sf::Time& deltaTime)
{
	auto playerTeamIt = ObjectManager::instence().getItersPlayerObj();
	if (playerTeamIt.first == playerTeamIt.second)
	{
		DataManager::instence().setLevelStatus(GAME_OVER);
		throw std::exception("GameOver");
	}
	if (checkEnemyIndex())
		setDiractionAccordingToEnemy();
	if (!isBlocked()) //make sure to keep the object in the board
		moveSprite(getDiraction(), getSpeed());
}
// this function recive an integere and returns the right diraction of the requsted diraction
//---------------------------------------------------------
const sf::Vector2f& MovingObj::retNewDirection(const int& direction)
{
	switch (direction)
	{
	case (LEFT):	return(sf::Vector2f(-1, 0));
	case(RIGHT):	return(sf::Vector2f(1, 0));
	case (DOWN):	return(sf::Vector2f(0, 1));
	case (UP):		return(sf::Vector2f(0, -1));

	}
}
//return the length of the the enemy, recive x ,y and cuurent position of enemy
//-------------------------------------------------------------
float MovingObj::caculateSIzeFromEnemy(int addToX, int addToY, sf::Vector2f position)
{

	int x = (int)abs(getPosition().x + addToX - position.x);
	int y = (int)abs(getPosition().y + addToY - position.y);
	return (float)sqrt((pow(x, 2) + pow(y, 2)));
}
//this function will return the sortest path to the enemy
//-------------------------------------------------------------
int MovingObj::setDiractionAccordingToEnemy()
{
	sf::Vector2f position;
	if(areEnemyTeam())
		position = ObjectManager::instence().getPositionPlayerTeamMember(m_enemyIndex);
	else
		position = ObjectManager::instence().getPositionEnemiesMember(m_enemyIndex);
	float arr[NUM_OF_DIRECTION] = { 0 };
	arr[DOWN] = caculateSIzeFromEnemy(0, 1, position);
	arr[UP] = caculateSIzeFromEnemy(0, -1, position);
	arr[RIGHT] = caculateSIzeFromEnemy(1, 0, position);
	arr[LEFT] = caculateSIzeFromEnemy(-1, 0, position);
	int lenToEnemy = arr[RIGHT], index = RIGHT;
	for (int i = 0; i < NUM_OF_DIRECTION; i++)
	{
		if (lenToEnemy > arr[i])
		{
			lenToEnemy = arr[i];
			index = i;
		}
	}
	if (lenToEnemy < 25 || !moveTo(index)) // without setting new direction 
		return lenToEnemy;

	sf::Vector2f lastDirection = getDiraction();
	sf::Vector2f nextDirection = retNewDirection(index);
	if (lastDirection.x == -nextDirection.x && lenToEnemy <= 1)
		setScale(sf::Vector2f(1, 1)); // setScale(sf::Vector2f(1, 1)); 
	return lenToEnemy;
}
//this fucntion will set random enemy to the current object
//--------------------------------------------------
int MovingObj::setEnemy()
{
	int index = -1;
	if(areEnemyTeam())
		index = ObjectManager::instence().getRnadomPlayerTeamMember();
	else
		index = ObjectManager::instence().getRnadomEnemiesTeamMember();
	
	if (index >= 0 && ! ObjectManager::instence().isDead(index, areEnemyTeam()))
	{
		m_enemyIndex = index;
		return index;
	}
	m_enemyIndex = -1;
	return -1;
}
//------------------------------------------------
bool MovingObj::checkEnemyIndex()
{
	if (m_enemyIndex == -1 || ObjectManager::instence().isDead(m_enemyIndex, areEnemyTeam()))
	{
		if (setEnemy() < 0)
			return false;
	}
	return true;
}
//set the nect diraction to get to the enemy 
//--------------------------------------------
bool MovingObj::moveTo(int diraction)
{
	sf::Vector2f nextDirection = retNewDirection(diraction);
	if (!IsGoodDiraction(nextDirection))
		return false;

	setDiraction(nextDirection);
	if(diraction != UP && diraction != DOWN) // else the scale will stay
		setScale(retScale(diraction));
	return true;
}
//
//--------------------------------------------
void MovingObj::readInfo(const infoFromTxt& info)
{
	try {
		setTexture(DataManager::instence().getTexture(info.name));
		setSpeed(info.speed);
		setPositionSprite(info.position);
		setEnemyTeam(info.Enemyteam);
		initLifeBar();
	}
	catch (const std::out_of_range& ex) {
		if (info.Enemyteam) {
			if (info.name[0] >= 'a' && info.name[0] <= 'z')
			{
				std::string modifiedName = info.name;
				modifiedName[0] = std::toupper(modifiedName[0]);
				setTexture(DataManager::instence().getTexture(modifiedName));
			}
		}
	}
}
//---------------------------------------------------
int MovingObj::getLife() const
{
	return m_life;
}
//--------------------------------------------------
void MovingObj::getHurt(const int& demage)
{
	m_life -= demage;
}
//--------------------------------------------------
bool MovingObj::isDead()
{
	return m_life < 0; //-----------
}
//--------------------------------------------------
void MovingObj::setOutOfTheGame()
{
	m_outOfTheGame = true;
}
//--------------------------------------------------
bool MovingObj::OutOfTheGame() const
{
	return m_outOfTheGame;
}
//-----------------------------------------------
void MovingObj::setLife(const int& life)
{
	m_life = life;
}
//-----------------------------------------------
std::vector<std::shared_ptr<SpacielAttack>> MovingObj::getActiveAttacks()
{
	std::vector<std::shared_ptr<SpacielAttack>> emptyVec;  // Create an empty vector
	return emptyVec;
}
//-------------------------------------------------------
const sf::FloatRect& MovingObj::getSmallerBounds() const
{
	return sf::FloatRect(getPosition().x - 10, getPosition().y, getRectangle().width / 4, getRectangle().height / 4);
}
//-----------------------------------------------
bool MovingObj::checkInView()
{
	if (((getPosition().x - DataManager::instence().getPlayerPosition().x) > 450) && !m_introduced)// 450
	{
		// set no active
		return false;
	}
	m_introduced = true;
	return true;
}
//-----------------------------------------------
bool MovingObj::IsGoodDiraction(const sf::Vector2f& diraction)
{
	bool rt = true;
	sf::Vector2f temp = getPosition() + diraction;
	if (temp.x + (getRectangle().width / 2) >= RIGHT_BOUND && diraction.x >= 1)
		rt = false;
	else if (temp.x - (getRectangle().width / 2) <= LEFT_BOUND && diraction.x <= -1)
		rt = false;
	else if (temp.y + (getRectangle().height / 2) >= DOWN_BOUND && diraction.y >= 1) // DOWN
		rt = false;
	else if (temp.y + (getRectangle().height / 2) <= UPPER_BOUND && diraction.y <= -1) // UP
		rt = false;

	setBlocked(!rt);
	return rt;
}
//--------------------------------------------
void MovingObj::initLifeBar()
{
	m_lifeBar.setMaxLife(getLife());
	m_lifeBar.initLifeBar(areEnemyTeam());
}
//-------------------------------------------
void MovingObj::drawLifeBar(sf::RenderWindow& window)
{
	m_lifeBar.setLifeBar(getLife());
	m_lifeBar.setPosition(getPosition() + sf::Vector2f(0, getRectangle().height/2 + 15));
	m_lifeBar.draw(window);
}
//--------------------------------------------
sf::Vector2f MovingObj::retScale(int direction)
{
	switch (direction)
	{
	case (LEFT):	return(sf::Vector2f(-1, 1));
	case(RIGHT):	return(sf::Vector2f(1, 1));
	default: return(sf::Vector2f(1, 1));
	}
}
//----------------------------------------------
void MovingObj::addlife(int add) // need to check the life bar updated
{
	if (m_life + add > m_lifeBar.getMaxLife())
		m_life = m_lifeBar.getMaxLife();
	else
		m_life += add;
}