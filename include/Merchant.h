#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Bar.h"

class Merchant
{
public:
	Merchant();
	void initMerchnt(sf::RenderWindow& window);
	bool runMerchant(sf::RenderWindow& window,const std::shared_ptr<Player>& player, Bar& bar);
	void draw(sf::RenderWindow& window);
	bool handleClick(sf::Vector2f position, const std::shared_ptr<Player>& player, Bar& bar);
	void sendErrorMessage();
private:
	void playerBought(const std::shared_ptr<Player>& player, int price, const std::string& weaponName, Bar& bar);
	sf::Sprite m_backround;
	sf::Sprite m_Item;
	sf::Sprite m_exit;
	sf::IntRect m_SpriteRect;
	sf::Text m_currentMoney;
	sf::Text m_messeges;
	std::vector<sf::RectangleShape> m_bottons;
	int m_page;
};

