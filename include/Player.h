#pragma once
#include "ActiveObj.h"
#include <SFML/Graphics.hpp>

const float JUMP_DISTANCE = 100.5f;
const float PUNCH_DISTANCE = 64.5f;
const int ENEMY_PRICE = 400;
const int MAX_LIFE = 800;

class Player : public ActiveObj
{
public:
	Player() : m_money(1000) { initPlayer(BAT); };
	~Player() {};
	int getMoney() const;
	void initPlayer(const std::string charcterName);
	void move(const sf::Time& deltaTime) override;
	void decMoney(int price);
	void UpdateNextLevel();
private:
	void moveToActive(int diraction);
	bool handleKey();
	int m_money;
};