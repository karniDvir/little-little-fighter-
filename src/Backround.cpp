#include "Backround.h"

//Initializes the background texture
//-------------------------------------------

void Backround::initBackround()
{
	//int level = DataManager::instence().getLevel();
	m_barckroundSprite.setTexture(DataManager::instence().getLevelTexture()[DataManager::instence().getBackroundIndex()]);
	m_barckroundSprite.setPosition(sf::Vector2f(0, 200));
}
//------------------------------------
void Backround::draw(sf::RenderWindow& window)
{
	window.draw(m_barckroundSprite);
}
