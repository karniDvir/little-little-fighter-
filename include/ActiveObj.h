#pragma once
#include "MovingObj.h"
#include <SFML/Graphics.hpp>
#include "AttackManager.h"
#include "Objinfo.h"
#include "SpacielAttack.h"
#include "Weapon.h"

const int FOLLOW_PLAYER = -1;
const int TILE_SIZE = 80;
typedef std::pair<sf::Vector2f, int> infoPair;
typedef std::unordered_map<int, infoPair> spritSheetInfo;
enum {
	WALK,
	RUN,
	JUMPKICK,
	PUNCH,
	PUNCH2,
	PUNCH3,
	THROW_PUNCH,
	JUMP_PUNCH,
	JUMP,
	REST,
	HURT,
	FALL,
	SPACIEL_ATTACK
};
enum MoveAlgoNumbers
{
	PUNCH_ALGO,
	COMBINES_ALGO,
	SHOOTING_ALGO
};
enum Attacks {
	MAGIC,
	FIRE,
	ICE,
	BAT__ATTCK,
	SKULL,
	NONE = -1
};

class ActiveObj : public MovingObj
{
public:
	ActiveObj();
	static void fillSheetMap();
	static void insertIntoSheetMap(int, infoPair);
	void readInfo(const infoFromTxt&) override;
	void draw(sf::RenderWindow& window) override;
	virtual void move(const sf::Time&) {};
	Attacks getAttacksType(const std::string& str);
	void handleWalk(int move);
	void getHurt(const int& demage) override;
	std::vector<std::shared_ptr<SpacielAttack>> getActiveAttacks() override;
	bool addSpacielAttack(const std::string& weapon_name);
	int getSpacielAttackNum() const;
	const std::vector<std::shared_ptr<SpacielAttack>>& getSkills();
	float getManaRatio() const;
	const int& getCurrentState() const;
	bool isHaveThisWeapon(const std::string& weaponName) const;
protected:
	void clearAttackVector();
	bool createThrowAttack( std::string attackName = "");
	virtual void handleRectable(const sf::Time& deltaTime) override;
	void SetMoving(const bool&& isMoving);
	void SetWeapon(const sf::Time& deltaTime);
	void PrefromAttack(const int& AttackNum);
	void setCurrentSate(const int&);
	void staticMove();
	void addAttack(const std::string& attack_name);
	void handleTimeing();
	const std::string& getstrAttacks(const int& index)const;
	ObjInfo& getObjInfo();
private:
	bool isGoodJump();
	static auto& getMap();
	Weapon m_weapon;
	std::string m_currentSate;
	std::vector<std::string> m_objectAttakcs; 
	ObjInfo m_objinfo; 
};

