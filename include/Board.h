#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include <thread>
#include <chrono>
#include "GameObj.h"
#include "Backround.h"
#include "Player.h"
#include "AttackManager.h"
#include "Level.h"

class Board
{
public:
	Board();
	void initBoard();
	void draw(sf::RenderWindow& window);
	void moveObj(const sf::Time& deltaTime);
	void changelevel();
	void GameOver();
	const std::shared_ptr <Player>& getPLayer();
private:
	Backround m_backround;
	Level m_level;
	std::shared_ptr <Player> m_player;
	int UpdateDrawArray(const int arr[]);
};