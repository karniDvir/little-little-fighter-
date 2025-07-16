#include "Player.h"
#include "ObjectManager.h"

// this function will be the base of the player move, will call the handle keybord 
// and handle the player attribute 
//--------------------------------------------------
void Player::move(const sf::Time& deltaTime)
{
	handleTimeing();
	handleRectable(deltaTime);
	if (getLife() <= 0)
	{
		DataManager::instence().setLevelStatus(GAME_OVER);
		return;
	}
	if (ObjectManager::instence().AreAllEnemiesKilled())
	{

		if (getPosition().x + (getRectangle().width) >= RIGHT_BOUND)
			DataManager::instence().setLevelStatus(NEXT_LEVEL);
	}
	if(handleKey() && IsGoodDiraction(getDiraction()))
		moveSprite(getDiraction(), getSpeed());
	DataManager::instence().setPlayerPosition(getPosition());
	SetWeapon(deltaTime);
}
// this function will handle keyboard pressed, the function will controll the player movment
// and the skills he uses
//--------------------------------------------------
bool Player::handleKey()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
		handleWalk(RUN);
	// this part resposble for the attacks
	/////////////////////////////////////////////////////////
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) &&
		(IsGoodDiraction(getDiraction() * PUNCH_DISTANCE)))
	{
		auto temp = getCurrentState();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			handleWalk(JUMP_PUNCH);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
			handleWalk(PUNCH2);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
			handleWalk(PUNCH3);
		else
			handleWalk(PUNCH);
		return true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		if (IsGoodDiraction(getDiraction() * JUMP_DISTANCE))
			handleWalk(JUMP);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
		handleWalk(JUMPKICK);
	// this part responseble of the spaciel attacks the user preform
	//////////////////////////////////////////////////////////
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		PrefromAttack(0);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		PrefromAttack(1);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		PrefromAttack(2);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
		PrefromAttack(3);
	//this part responsble of the throwable attacks from user
	//////////////////////////////////////////////////////////
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		bool attack = false;
		std::string attackstr = getstrAttacks(0);
		if (attackstr != "" && attackstr.size() > 0)
			attack = createThrowAttack(attackstr);
		else
			attack = createThrowAttack("MagicAttack");
		if (attack)
			handleWalk(THROW_PUNCH);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		bool attack = false;
		std::string attackstr = getstrAttacks(1);
		if (attackstr != "" && attackstr.size() > 0)
			attack = createThrowAttack(attackstr);
		else
			attack = createThrowAttack("MagicAttack");
		if (attack)
			handleWalk(THROW_PUNCH);
	}
	// this part responsble of the movment
	////////////////////////////////////////////////////////
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		moveToActive(LEFT);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		moveToActive(RIGHT);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		moveToActive(UP);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		moveToActive(DOWN);
	else
	{
		staticMove();
		SetMoving(false);
		return false;
	}
	return true;
}
// this function will init the player attributes
//------------------------------------------
void Player::initPlayer(const std::string charcterName)
{
	std::string tempStr = charcterName;
	characterInfo temp;
	try {
		temp = DataManager::instence().getCharecterInformation(tempStr);
	}
	catch (const std::out_of_range& ex)
	{
		tempStr = BAT;
		temp = DataManager::instence().getCharecterInformation(tempStr);
	}
	setTexture(DataManager::instence().getTexture(temp.m_characterName));
	clearAttackVector();
	addAttack(temp.m_attack1Name);
	addAttack(temp.m_attack2Name);
	setPositionSprite(sf::Vector2f(400, 700));
	setRecTangle();
	setEnemyTeam(false);
	setLife(MAX_LIFE);
	initLifeBar();
}
//-----------------------------------------
int Player::getMoney() const
{
	return m_money;
}
//----------------------------------------
void Player::decMoney(int price)
{
	m_money -= price;
}
//--------------------------------------------
void Player::moveToActive(int diraction)
{
	if (MovingObj::moveTo(diraction))
		handleWalk(WALK);
	else
		handleWalk(REST);
}
// this function will upadte the player infomation for the next level
//-------------------------------------------
void Player::UpdateNextLevel()
{
	addlife(MAX_LIFE);
	initLifeBar();
	decMoney(-(ObjectManager::instence().getNumOfEnemies() * ENEMY_PRICE));// adding money (-)
}
