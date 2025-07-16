#include "Menu.h"
#include "DataManager.h"
//-------------------------------------------
void Menu::initMenu(sf::RenderWindow& window)
{
	m_currentCharecter = BAT_ENUM;
	m_page = 1;
	m_SpriteRect.height = 550;
	m_SpriteRect.width = 1000;
	m_Item.setTexture(DataManager::instence().getGameTexture().m_menu);
	m_Item.setTextureRect(m_SpriteRect);
	m_Item.setOrigin(sf::Vector2f(m_SpriteRect.width / 2.0f, m_SpriteRect.height / 2.0f));
	m_Item.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
	for (int i = 0; i < 5; i++)
	{
		m_bottons.push_back(sf::RectangleShape(sf::Vector2f(122, 122)));
		m_bottons[i].setOrigin(sf::Vector2f(62.5, 62.5));
		m_bottons[i].setPosition(sf::Vector2f(i * 189 + 125, 400));
		m_bottons[i].setFillColor(sf::Color::Transparent);
		m_bottons[i].setOutlineColor(sf::Color::Green);
		m_bottons[i].setOutlineThickness(2.5);
	}
	m_bottons.push_back(sf::RectangleShape(sf::Vector2f(120, 40)));
	m_bottons[m_bottons.size() - 1].setOrigin(sf::Vector2f(60, 20));
	m_bottons[m_bottons.size() - 1].setPosition(sf::Vector2f(505, 620));

}
//-------------------------------------------

bool Menu::runMenu(sf::RenderWindow& window, const std::shared_ptr<Player>& player, Bar& bar)
{
	DataManager::instence().getGameMusic().startTrasitionMusic();
	static bool first = false;
	while (true)
	{
		window.clear();
		draw(window);
		window.display();
		if (auto event = sf::Event{}; window.waitEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				return false;
			}
			else if (event.type == sf::Event::MouseButtonReleased)
			{
				auto location = window.mapPixelToCoords(
					{ event.mouseButton.x, event.mouseButton.y });
				if (handleClick(location, player, bar))
					break;
			}

		}
	}
	return true;
}
//----------------------------------------
void Menu::draw(sf::RenderWindow& window)
{
	window.draw(m_Item);
	if(m_bottons.size() > m_currentCharecter)
	{
		if (m_page == 1)
			window.draw(m_bottons[m_currentCharecter]);
	}
	else
	{
		//window.draw(m_bottons[BAT_ENUM]);
		throw std::out_of_range("Vector subscreipt is out of range");
	}
}
//----------------------------------------
bool Menu::handleClick(sf::Vector2f position, const std::shared_ptr<Player>& player, Bar& bar)
{
	int i = 0;
	for (; i < m_bottons.size(); i++)
	{
		if (m_bottons[i].getGlobalBounds().contains(position))
			break;
	}
	if (m_page == 1)
	{
		switch (i)
		{
		case 0: player->initPlayer(BAT); bar.setcharacter(BAT_ENUM); m_currentCharecter = BAT_ENUM; break;
			case 1: player->initPlayer(DEEP); bar.setcharacter(DEEP_ENUM); m_currentCharecter = DEEP_ENUM; break;
			case 2: player->initPlayer(DENNIS); bar.setcharacter(DENNIES_ENUM); m_currentCharecter = DENNIES_ENUM; break;
			case 3: player->initPlayer(LOUIS); bar.setcharacter(LOUIS_ENUM); m_currentCharecter = LOUIS_ENUM; break;
			case 4: player->initPlayer(JULIAN); bar.setcharacter(JULIAN_ENUM); m_currentCharecter = JULIAN_ENUM; break;
			case 5:  return true;
		default: m_page = 2;  m_SpriteRect.top = 550; m_Item.setTextureRect(m_SpriteRect); break;
		}
	}
	else if (m_page == 2)
	{
		switch (i)
		{
		case 5:  return true;
		default: m_page = 1;  m_SpriteRect.top = 0; m_Item.setTextureRect(m_SpriteRect); break;
		}
	}
	return false;
}
