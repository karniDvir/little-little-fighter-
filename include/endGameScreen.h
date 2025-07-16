#pragma once 
#include <SFML/Graphics.hpp>

class endGameScreen
{
public:
	void initScreen(const bool& isWon);
	void draw(const sf::Time& deltaTime);
	void runEndGame(sf::RenderWindow& window);
private:
	sf::Sprite m_item;
	sf::IntRect m_recForItem;
};