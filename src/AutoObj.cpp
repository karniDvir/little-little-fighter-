#include "AutoObj.h"
#include"ObjectManager.h"


// all the active objects that move by algo direction
AutoObj::AutoObj()
{}

//We check if all the enemies are dead so that the objects in the player's team
//  will follow him to the end of the level
//---------------------------------------
void AutoObj::move(const sf::Time& deltaTime)
{
	handleTimeing();// Calculates and updates times for operations
	handleRectable(deltaTime);
	if (checkInView())// Checks if it is indeed in the view
	{
		if (!ObjectManager::instence().AreAllEnemiesKilled(areEnemyTeam()) && checkEnemyIndex())
			handleMovment(setDiractionAccordingToEnemy());
		else // ifDead
			handleMovment(FOLLOW_PLAYER); // after Player
	}
	else
		handleWalk(REST);
	if(IsGoodDiraction(getDiraction()))
		moveSprite(getDiraction(), getSpeed());
	SetWeapon(deltaTime);
}
// - Performs the attack algorithm according to the distance calculation
// - Follows the main player for objects in player team
//--------------------------------------------
void AutoObj::handleMovment(int LengthToEnemy)
{
	try {
		if (LengthToEnemy == FOLLOW_PLAYER)
		{
			setCurrentSate(WALK);
			float X_direction = DataManager::instence().getPlayerPosition().x - getPosition().x;
			if (!areEnemyTeam() && abs(X_direction) > 140)
			{
				X_direction /= (X_direction < 0) ? -X_direction : X_direction;
				setDiraction(sf::Vector2f(X_direction, 0.0f));
				setScale(sf::Vector2f(X_direction, 1.0f));
				handleWalk(WALK);
			}
			else
				handleWalk(REST);
			return;
		}
		if (isBlocked()) {
			handleWalk(REST);
			return;
		}
		if (LengthToEnemy > 240) {
			handleWalk(RUN);
			return;
		}
		if (getObjInfo().m_waitTime < 30) {
			handleWalk(WALK);
			getObjInfo().m_waitTime++;
			return;
		}
		getObjInfo().m_waitTime = 0; // Resets clock
		if (getObjInfo().m_algorithemNum == -1)// If an algorithm needs to be changed
			getObjInfo().m_algorithemNum = setNextActiveAlgorithem(LengthToEnemy);
		switch (getObjInfo().m_algorithemNum)
		{
		case PUNCH_ALGO: ActiveAlgorithem1() ? getObjInfo().m_algorithemNum : getObjInfo().m_algorithemNum = -1; break;
		case COMBINES_ALGO: ActiveAlgorithem2() ? getObjInfo().m_algorithemNum : getObjInfo().m_algorithemNum = -1; break;
		case SHOOTING_ALGO: ActiveAlgorithem3() ? getObjInfo().m_algorithemNum : getObjInfo().m_algorithemNum = -1; break;
		default: getObjInfo().m_algorithemNum = setNextActiveAlgorithem(LengthToEnemy);
		}
	}
	catch (const std::exception& ex) {}//
}

// Short range attack algorithm
//--------------------------------------------
bool AutoObj::ActiveAlgorithem1()
{
	switch (getObjInfo().m_act)
	{
	case 0: if (!createThrowAttack(getstrAttacks(0))) { handleWalk(WALK); }		break;
	case 1: getObjInfo().m_mana > 100 ? handleWalk(PUNCH3) : handleWalk(WALK);		break;
	case 2: getObjInfo().m_mana > 100 ? handleWalk(PUNCH2) : handleWalk(REST);		break;
	case 3: getObjInfo().m_mana > 100 ? handleWalk(JUMP_PUNCH) : handleWalk(WALK); break;
	case 4: getObjInfo().m_mana > 200 ? handleWalk(PUNCH3) : handleWalk(PUNCH2);	break;
	case 5: if (!createThrowAttack(getstrAttacks(1))) { handleWalk(REST); }
		  getObjInfo().m_act = 0; return false;
	}
	getObjInfo().m_act++;
	return true;
}
//Medium distance attack algorithm
//---------------------------------------------------------------
bool AutoObj::ActiveAlgorithem2()
{
	switch (getObjInfo().m_act)
	{
	case 0: getObjInfo().m_mana > 100 ? handleWalk(JUMP_PUNCH) : handleWalk(PUNCH); break;
	case 1: if (!createThrowAttack(getstrAttacks(0))) { handleWalk(WALK); }		 break;
	case 2: getObjInfo().m_mana > 100 ? handleWalk(JUMPKICK) : handleWalk(WALK);	 break;
	case 3: getObjInfo().m_mana > 200 ? PrefromAttack(0) : handleWalk(PUNCH2);		 break;
	case 4: getObjInfo().m_mana > 100 ? handleWalk(JUMPKICK) : handleWalk(REST);	 break;
	case 5: if (!createThrowAttack(getstrAttacks(1))) { handleWalk(JUMP_PUNCH); }
		  getObjInfo().m_act = 0; return false;
	}
	getObjInfo().m_act++;
	return true;
}
//Long distance attack algorithm
//---------------------------------------------------------------
bool AutoObj::ActiveAlgorithem3()
{
	getObjInfo().m_mana = 300;
	switch (getObjInfo().m_act)
	{
	case 0: getObjInfo().m_mana > 200 ? PrefromAttack(0) : handleWalk(PUNCH2);		break;
	case 1: handleWalk(JUMPKICK); break;
	case 2: if (!createThrowAttack(getstrAttacks(0))) { handleWalk(PUNCH2); }	break;
	case 3: getObjInfo().m_mana > 100 ? handleWalk(JUMP_PUNCH) : handleWalk(WALK); break;
	case 4: if (!createThrowAttack(getstrAttacks(0))) { handleWalk(WALK); }		break;
	case 5: getObjInfo().m_mana > 100 ? handleWalk(PUNCH) : handleWalk(REST);
		getObjInfo().m_act = 0; return false;
	}
	getObjInfo().m_act++;
	return true;
}
// set the algorithem index
//----------------------------------------------------
int AutoObj::setNextActiveAlgorithem(int LengthToEnemy)
{
	if (LengthToEnemy > 0)
	{
		if (LengthToEnemy < 20)
			return PUNCH_ALGO;
		if (LengthToEnemy < 100)
			return COMBINES_ALGO;
		else
			return SHOOTING_ALGO;
	}
	return SHOOTING_ALGO;
}