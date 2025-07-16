#include "endGameScreen.h"
#include "DataManager.h"
//--------------------------------------------------------
void endGameScreen::initScreen(const bool& isWon)
{
	if (isWon)
	{
		m_item.setTexture(DataManager::instence().getGameTexture().m_youWon);
		DataManager::instence().getGameMusic().startWinMusic();
	}
	else
	{
		m_item.setTexture(DataManager::instence().getGameTexture().m_gameOver);
		DataManager::instence().getGameMusic().startTrasitionMusic();
	}
	m_item.setOrigin(500, 150);
	m_item.setPosition(500, 400);
	m_recForItem.height = 300;
	m_recForItem.width = 1000;
	m_item.setTextureRect(m_recForItem);
}
//--------------------------------------------------------
void endGameScreen::draw(const sf::Time& deltaTime)
{
	if (deltaTime.asMilliseconds() < 100)
		return;
	if (m_recForItem.top >= 1800)
		m_recForItem.top = 0;
	else
		m_recForItem.top += 300;
	m_item.setTextureRect(m_recForItem);
}
//--------------------------------------------------------
void endGameScreen::runEndGame(sf::RenderWindow& window)
{
	DataManager::instence().getGameMusic().stopGameMusic();
	sf::Clock clock;
	window.setView(window.getDefaultView());
	while (true) // was true
	{
		window.clear();
		sf::Time elapsd = clock.getElapsedTime();
		draw(elapsd);
		window.draw(m_item);
		if (auto event = sf::Event{}; window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				return;
			}
		}
		window.display();
		if (elapsd.asSeconds() > 0.1)
			clock.restart();
	}
	DataManager::instence().getGameMusic().endAllMusic();
}