#pragma once
#include "InfoFromTxt.h"
#include "DynamicObj.h"
#include <SFML/Graphics.hpp>
#include "SpacielAttack.h"
#include "LifeBar.h"

const int NUM_OF_DIRECTION = 4;


enum Directon
{
	DOWN,
	UP,
	RIGHT,
	LEFT
};


class MovingObj : public DynamicObj
{
public:
	MovingObj();
	void initLifeBar();
	void drawLifeBar(sf::RenderWindow& window);
	virtual void readInfo(const infoFromTxt& info);
	virtual void move(const sf::Time& deltaTime);
	const sf::Vector2f& retNewDirection(const int& direction);
	float caculateSIzeFromEnemy(int addToX, int addToY, sf::Vector2f position);
	int setDiractionAccordingToEnemy();
	int setEnemy();
	bool checkEnemyIndex();
	bool moveTo(int diraction);
	void setLife(const int& life);
	int getLife() const;
	virtual void getHurt(const int& demage);
	bool isDead();
	void setOutOfTheGame();
	bool OutOfTheGame() const;
	virtual std::vector<std::shared_ptr<SpacielAttack>> getActiveAttacks();
	bool checkInView();
	bool IsGoodDiraction(const sf::Vector2f& diraction);
	const sf::FloatRect& getSmallerBounds() const;
	virtual void addWeapon(const std::string&) {};
	void addlife(int add);
protected:
	sf::Vector2f retScale(int direction);
private:
	bool m_outOfTheGame;
	int m_life;
	int m_enemyIndex;
	bool m_introduced = false;
	lifeBar m_lifeBar;
};

