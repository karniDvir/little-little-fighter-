#include "ActiveObj.h"
//defualt constrator for the object
//---------------------------------------------
ActiveObj::ActiveObj()
{
	fillSheetMap();
	setLife(500);
}
//---------------------------------------------
/*
* the object will hold information about the activrObj sprtie, this is the function
* that init this map, the map will be used to accsess the sprite information fast and in effective way
*/
//----------------------------------------------------
void ActiveObj::fillSheetMap()
{
	static bool initial = true;
	if (initial)
	{
		insertIntoSheetMap(WALK, infoPair(sf::Vector2f(240, 0), 5));
		insertIntoSheetMap(REST, infoPair(sf::Vector2f(0, 0), 4));
		insertIntoSheetMap(RUN, infoPair(sf::Vector2f(0, 160), 3));
		insertIntoSheetMap(PUNCH, infoPair(sf::Vector2f(0, 80), 4));
		insertIntoSheetMap(PUNCH2, infoPair(sf::Vector2f(320, 80), 4));
		insertIntoSheetMap(PUNCH3, infoPair(sf::Vector2f(320, 560), 4));
		insertIntoSheetMap(JUMP, infoPair(sf::Vector2f(0, 480), 7));
		insertIntoSheetMap(JUMPKICK, infoPair(sf::Vector2f(0, 560), 5));
		insertIntoSheetMap(SPACIEL_ATTACK, infoPair(sf::Vector2f(0, 640), 7));
		insertIntoSheetMap(JUMP_PUNCH, infoPair(sf::Vector2f(0, 720), 4));
		insertIntoSheetMap(HURT, infoPair(sf::Vector2f(320, 400), 2));
		insertIntoSheetMap(FALL, infoPair(sf::Vector2f(0, 320), 9));
		initial = false;
	}
}
//----------------------------------------------------------------
auto& ActiveObj::getMap()
{
	static spritSheetInfo m_MapSheetInfo;
	return m_MapSheetInfo;
}
//to inset the information to the map
//-----------------------------------------------------------------
void ActiveObj::insertIntoSheetMap(int num, infoPair info)
{
	getMap().insert(std::make_pair(num, info));
}

//---------------------------------------------
void ActiveObj::SetMoving(const bool&& isMoving)
{
	m_objinfo.m_moving = isMoving;
}
/*
* this is how we used the map to controll the object texture and the animation of the object
*/
//--------------------------------------------
void ActiveObj::handleRectable(const sf::Time& deltaTime)
{
	if (deltaTime.asMilliseconds() < 100)
		return;
	if (getRectangle().left <= getMap()[m_objinfo.m_currentSate].first.x)
	{
		AddLeftRectangle(80);
		m_objinfo.m_revers = false;
	}
	else if (getRectangle().left >= (getMap()[m_objinfo.m_currentSate].second - 1) * TILE_SIZE +
		getMap()[m_objinfo.m_currentSate].first.x)
	{
		AddLeftRectangle(-80);
		m_objinfo.m_revers = true;
		if (m_objinfo.m_currentSate != REST && !m_objinfo.m_moving)
		{
			if (isDead())
				setOutOfTheGame();
			setCurrentSate(REST);
			handleWalk(REST);
		}
	}
	else if (!m_objinfo.m_revers)
		AddLeftRectangle(80);
	else if (m_objinfo.m_revers)
		AddLeftRectangle(-80);

	setTextureRect(getRectangle());
}
//----------------------------------------------
void ActiveObj::handleWalk(int move)
{
	m_objinfo.m_statictime++;
	if (move == JUMP || move == JUMPKICK || move == JUMP_PUNCH)
		if (m_objinfo.m_statictime < 100 && IsGoodDiraction(getDiraction()))
			return;
		else
		{
			m_objinfo.m_statictime = 0;
			handleWalk(REST);
		}

	if (m_objinfo.m_currentSate != RUN && m_objinfo.m_currentSate != WALK 
		&& m_objinfo.m_currentSate != REST)
		return;

	switch (move)
	{
	case NONE:        SetMoving(false); break;
	case WALK:        setSpeed(2.5f - m_objinfo.m_speedDeviation); SetMoving(true); setAttackPower(0);
			          (m_objinfo.m_run) ? handleWalk(RUN) : setCurrentSate(WALK); break;
	case RUN:         setCurrentSate(RUN); setSpeed(3.0f - m_objinfo.m_speedDeviation); SetMoving(true);  setAttackPower(0); break;
	case JUMP:        setCurrentSate(JUMP); setSpeed(3.5f - m_objinfo.m_speedDeviation); SetMoving(false); setAttackPower(0); break;
	case JUMPKICK:    setCurrentSate(JUMPKICK); setSpeed(2.5f - m_objinfo.m_speedDeviation); SetMoving(false); setAttackPower(12);
		              playSound(DataManager::instence().getGameMusic().normalAttack2);             break;
	case PUNCH:       setCurrentSate(PUNCH); setSpeed(0.0f); SetMoving(false); setAttackPower(10);
		              playSound(DataManager::instence().getGameMusic().normalAttack1);             break;
	case HURT:        setCurrentSate(HURT); setSpeed(0.5f); SetMoving(false); setAttackPower(-1);  
		              playSound(DataManager::instence().getGameMusic().hurtSound);                 break;
	case FALL:        setCurrentSate(FALL); setSpeed(0.0f); SetMoving(false); setAttackPower(-1); 
		              playSound(DataManager::instence().getGameMusic().hurtSound);                 break;
	case PUNCH2:      setCurrentSate(PUNCH2); setSpeed(0.0f); SetMoving(false); setAttackPower(15); 
		              playSound(DataManager::instence().getGameMusic().normalAttack2);             break;
	case PUNCH3:      if (m_objinfo.m_mana > 100) {
					  setCurrentSate(PUNCH3); 
					  setSpeed(2.4f - m_objinfo.m_speedDeviation);
					  SetMoving(false);
					  setAttackPower(30);
					  m_objinfo.m_mana -= 100; 
					  playSound(DataManager::instence().getGameMusic().normalAttack3);             break;}
					  handleWalk(PUNCH); break;
	case THROW_PUNCH: setCurrentSate(SPACIEL_ATTACK); setSpeed(0.0f); SetMoving(false); setAttackPower(0); break;
	case JUMP_PUNCH:  setCurrentSate(JUMP_PUNCH); setSpeed(2.6f - m_objinfo.m_speedDeviation); 
		              SetMoving(false);   m_objinfo.m_mana -= 100;    setAttackPower(30);
					  playSound(DataManager::instence().getGameMusic().normalAttack3);               break;
	case REST:        setCurrentSate(REST); setSpeed(0.0f); SetMoving(false); setAttackPower(0);     break;
	default: break;
	}
	move == RUN ? m_objinfo.m_run = true : m_objinfo.m_run = false;
}
//------------------------------------------
void ActiveObj::draw(sf::RenderWindow& window)
{
	GameObj::draw(window);
	m_weapon.draw(window);
	drawLifeBar(window);
}
//------------------------------------------
void ActiveObj::SetWeapon(const sf::Time& deltaTime)
{
	m_weapon.handleTime(deltaTime);

	m_weapon.setSpritePosition(getPosition());
	m_weapon.setScale(getScale());
}
//--------------------------------------------
bool ActiveObj::addSpacielAttack(const std::string& weapon_name)
{
	return m_weapon.addWeapon(weapon_name);
}
//------------------------------------------
void ActiveObj::PrefromAttack(const int& AttackNum) // karni
{
	if (m_objinfo.m_mana < m_weapon.getManaforAttack(AttackNum))
		return;
	if (!m_weapon.PreformSpacielAttack(AttackNum))
		return;
	m_objinfo.m_mana -= m_weapon.getManaforAttack(AttackNum);
	rand() % 2 ? playSound(DataManager::instence().getGameMusic().spacielAttack1) :
		playSound(DataManager::instence().getGameMusic().spacielAttack2);
	
}
//--------------------------------------------
bool ActiveObj::createThrowAttack(std::string attackName )//exception
{
	if (m_objinfo.m_waitForAttackTime < 30 || attackName.size() <= 0 ||attackName == "" )
		return false;
	m_objinfo.m_waitForAttackTime = 0;
	int manaUsage = 0;
	auto temp = AttackManager::instence().getAttackMap().find(attackName);
	if (temp != AttackManager::instence().getAttackMap().end())
	{
		auto obj = temp->second();
		obj->initThrowable(getPosition(), getScale(), attackName, areEnemyTeam());
		switch (getAttacksType(attackName))
		{
		case FIRE: obj->addThrowableParemeters(150, FIRE_POWER ,2.3f); manaUsage = 70; break;
		case ICE: obj->addThrowableParemeters(200, ICE_POWER, 2.0f); manaUsage = 60; break;
		case MAGIC: obj->addThrowableParemeters(180, MAGIC_POWER, 2.2f); manaUsage = 60; break;
		case BAT__ATTCK: obj->addThrowableParemeters(300, BAT_POWER, 2.1f); manaUsage = 50; break;
		case SKULL:  obj->addThrowableParemeters(150, SKULL_POWER, 2.2f); manaUsage = 30; break;
		}
		if (m_objinfo.m_mana - manaUsage < 0)
			return false;
		AttackManager::instence().addActiveAttack(obj);
		m_objinfo.m_mana -= manaUsage;
		handleWalk(THROW_PUNCH);
	}
	return true;
}
//-------------------------------------------
void ActiveObj::setCurrentSate(const int& num)
{
	if (m_objinfo.m_currentSate != num)
	{
		m_objinfo.m_currentSate = num;
		SetTopRectangle(getMap()[m_objinfo.m_currentSate].first.y);
		setLeftRectngle(getMap()[m_objinfo.m_currentSate].first.x);
	}
}

//--------------------------------------------
void ActiveObj::staticMove() // maybe need to move player class
{
	if (m_objinfo.m_currentSate == JUMP || m_objinfo.m_currentSate == JUMPKICK
		|| m_objinfo.m_currentSate == PUNCH3 || m_objinfo.m_currentSate == JUMP_PUNCH)
		if(IsGoodDiraction(getDiraction()))
			moveSprite(getDiraction(), getSpeed());
		else
			handleWalk(WALK);
}
//------------------------------------
void ActiveObj::addAttack(const std::string& attack_name)
{
	m_objectAttakcs.emplace_back(attack_name); //exeptions
}
//---------------------------------------------
void ActiveObj::readInfo(const infoFromTxt& info)
{
	// check if the position in the limits
	MovingObj::readInfo(info);
	setRecTangle();
	m_objinfo.m_speedDeviation = info.SpeedDeviation;
	try
	{
		for (auto i : info.attacks)
		{
			addAttack(i);
		}
		const auto& ret = DataManager::instence().getSpacielAttackInfo(info.weapon);
		addSpacielAttack(info.weapon);
	}
	catch (const std::out_of_range& ex) {}
		
}
//-----------------------------------------------------------------

Attacks ActiveObj::getAttacksType(const std::string& str)
{
	if (str == "FireAttack")
		return FIRE;
	if (str == "IceAttack")
		return ICE;
	if (str == "BatAttack")
		return BAT__ATTCK;
	if (str == "SkullAttack")
		return SKULL;
	if (str == "MagicAttack")
		return MAGIC;
	return NONE;
}
//--------------------------------------
void ActiveObj::getHurt(const int& demage)
{
	if (m_objinfo.m_recoveryTime < 50)
		return;
	m_objinfo.m_recoveryTime = 0;
	MovingObj::getHurt(demage);
	if (demage < 25)
		handleWalk(HURT);
	else
		handleWalk(FALL);
	if(isDead() && m_currentSate != "fall")
		handleWalk(FALL);
}
//--------------------------------------
void ActiveObj::handleTimeing()
{
	if (m_objinfo.m_recoveryTime <= 50)
		m_objinfo.m_recoveryTime++;
	if (m_objinfo.m_waitForAttackTime <= 30)
		m_objinfo.m_waitForAttackTime++;
	if (m_objinfo.m_mana < 0) //afek
		m_objinfo.m_mana = 0;
	else if (m_objinfo.m_mana <= 400)
		m_objinfo.m_mana++;
	m_weapon.setColdownsWeapon();
}
//--------------------------------------
std::vector<std::shared_ptr<SpacielAttack>> ActiveObj::getActiveAttacks()
{
	return m_weapon.getActiveAttacks();
}
//-------------------------------------------
const std::string& ActiveObj::getstrAttacks(const int& index)const // exception
{
	std::string str = "";
	if (m_objectAttakcs.empty() == false)
	{
		if (index < m_objectAttakcs.size() && index > 0)
			return m_objectAttakcs[index];
		else
			return m_objectAttakcs[0];
	}
	return str;
}
//--------------------------------------------
ObjInfo& ActiveObj::getObjInfo()
{
	return m_objinfo;
}
//-------------------------------------------
void ActiveObj::clearAttackVector()
{
	m_objectAttakcs.clear();
}
//------------------------------------------
int ActiveObj::getSpacielAttackNum() const
{
	return m_weapon.getSizeOfSpacielAttacks();
}
//---------------------------------------------
const std::vector<std::shared_ptr<SpacielAttack>>& ActiveObj::getSkills()
{
	return m_weapon.getSkills();
}
//---------------------------------------------
float ActiveObj::getManaRatio() const
{
	float tempMana = m_objinfo.m_mana;
	return  m_objinfo.m_mana / 401.f;
}
//-------------------------------------------
const int& ActiveObj::getCurrentState() const
{
	return m_objinfo.m_currentSate;
}
//------------------------------------------
bool ActiveObj::isHaveThisWeapon(const std::string& weaponName) const
{
	return m_weapon.IshaveThisWeapon(weaponName);
}