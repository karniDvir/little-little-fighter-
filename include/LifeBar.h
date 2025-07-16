#pragma once
#include "DataManager.h"
#include <SFML/Graphics.hpp>
const int BAR_HEIGHT = 5;
const int BAR_LEN = 70;

class lifeBar
{
public:
	void initLifeBar(const bool& IsEnemy);
	void setMaxLife(int life);
	void setPosition(const sf::Vector2f& position);
	void setLifeBar(float life);
	void draw(sf::RenderWindow& window);
	const int& getMaxLife() const;
private:
	void UpdateBar();
	int m_maxLife;
	sf::Sprite m_lifeBar;
	sf::IntRect m_recTexture;
};
