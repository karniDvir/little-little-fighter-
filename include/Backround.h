#pragma once
#include <SFML/Graphics.hpp>
#include "DataManager.h"
#include <vector>
enum {
	sky,
	item,
	base
	
};
class Backround
{
public:
	Backround() {};
	void initBackround();
	void draw(sf::RenderWindow& window);

private:
	sf::Sprite m_barckroundSprite;
};
