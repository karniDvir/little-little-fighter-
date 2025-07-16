#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Bar.h"

class Menu
{
public:
	void initMenu(sf::RenderWindow& window);
	bool runMenu(sf::RenderWindow& window, const std::shared_ptr<Player>& player, Bar& bar);
	void draw(sf::RenderWindow& window);
	bool handleClick(sf::Vector2f position, const std::shared_ptr<Player>& player, Bar& bar);
private:
	int m_currentCharecter;
	sf::Sprite m_Item;
	std::vector<sf::RectangleShape> m_bottons;
	sf::IntRect m_SpriteRect;
	int m_page;
};