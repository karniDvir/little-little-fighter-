#pragma once
#include "Board.h"
#include "Merchant.h"
#include "Menu.h"
#include "Bar.h"
#include "endGameScreen.h"

const int MAX_SIZE_ROW = 800;
const int MAX_SIZE_COL = 1000;

class Controller
{
public:
	void run();
private:
	void initBoardObj();
	void draw( const LevelType& level = CURRENT_LEVEL);
	void GameOver();
	bool handeLevelStatus();
	void changeLevel();
	void WinGame();
	void EndGameWindow(bool Iswin);
	endGameScreen m_endGameScreen;
	sf::RenderWindow m_window;
	Board m_board;
	Merchant m_merchant;
	Menu m_menu;
	Bar m_bar;
};