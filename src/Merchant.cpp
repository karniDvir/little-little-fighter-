#include "Merchant.h"
#include "DataManager.h"

Merchant::Merchant()
	: m_page(1)
{}

void Merchant::initMerchnt(sf::RenderWindow& window)
{
	m_exit.setTexture(DataManager::instence().getGameTexture().m_exit);
	m_exit.setPosition(sf::Vector2f(750, 0));
	m_messeges.setFont(DataManager::instence().getGameTexture().m_font);
	m_messeges.setPosition(500, 700);
	m_messeges.setOutlineColor(sf::Color::Black);
	m_messeges.setOutlineThickness(2.0f);
	m_currentMoney.setOutlineThickness(2.f);
	m_currentMoney.setFont(DataManager::instence().getGameTexture().m_font);
	m_currentMoney.setOrigin(sf::Vector2f(130, 22));
	m_currentMoney.setPosition(sf::Vector2f(500, 200));
	m_backround.setTexture(DataManager::instence().getGameTexture().m_merchantBackround);
	m_SpriteRect.height = 610;
	m_SpriteRect.width = 550;
	m_Item.setTexture(DataManager::instence().getGameTexture().m_merchantItem);
	m_Item.setTextureRect(m_SpriteRect);
	//m_Item.scale(sf::Vector2f(1.1f, 1.1f));//--------------------------
	m_Item.setOrigin(sf::Vector2f(m_SpriteRect.width / 2.0f, m_SpriteRect.height / 2.0f));
	m_backround.setOrigin(sf::Vector2f(m_backround.getGlobalBounds().width / 2, m_backround.getGlobalBounds().height / 2));
	m_Item.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
	m_backround.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
	for (int i = 0; i < 5; i++)
	{
		m_bottons.push_back(sf::RectangleShape(sf::Vector2f(260, 42)));
		m_bottons[i].setOrigin(sf::Vector2f(130, 22));
		m_bottons[i].setPosition(sf::Vector2f(500, i * 61 + 295));
		m_bottons[i].setFillColor(sf::Color::Transparent);
	}
	
}

bool Merchant::runMerchant(sf::RenderWindow& window, const std::shared_ptr<Player>& player, Bar& bar)
{
	DataManager::instence().getGameMusic().stopGameMusic();
	DataManager::instence().getGameMusic().startTrasitionMusic();
	while (window.isOpen()) // was true
	{
		window.clear();
		draw(window);
		m_currentMoney.setString("balance: " + (std::to_string(player->getMoney()) + +"$"));
		if (auto event = sf::Event{}; window.waitEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				return false;
			}
			else if (event.type == sf::Event::MouseButtonReleased)
			{
				m_messeges.setString("");
				auto location = window.mapPixelToCoords(
					{ event.mouseButton.x, event.mouseButton.y });
				if (handleClick(location, player, bar))
					break;
			}

		}
		window.display();
	}
	DataManager::instence().getGameMusic().stopTransitionMusic();
	DataManager::instence().getGameMusic().startGameMusic();
	return true;
}
//----------------------------------------
void Merchant::draw(sf::RenderWindow& window)
{
	window.draw(m_backround);
	window.draw(m_Item);
	window.draw(m_currentMoney);
	window.draw(m_exit);
	m_messeges.setOrigin(m_messeges.getGlobalBounds().width / 2, m_messeges.getGlobalBounds().height / 2);
	window.draw(m_messeges);
}
//-----------------------------------------
bool Merchant::handleClick(sf::Vector2f position, const std::shared_ptr<Player>& player, Bar& bar)
{
	int i = 0;
	for (; i < m_bottons.size(); i++)
	{
		if (m_bottons[i].getGlobalBounds().contains(position))
			break;
	}
	if (m_exit.getGlobalBounds().contains(position))
		i = 6;
	if (m_page == 1)
	{
		switch (i)
		{
		case 0: player->getMoney() >= 400 ? playerBought(player, 400, SOWRD,bar) : sendErrorMessage(); break;
		case 1: player->getMoney() >= 300 ? playerBought(player, 300, LIGHT_BOW,bar) : sendErrorMessage(); break;
		case 2: player->getMoney() >= 400 ? playerBought(player, 400, NORMAL_BOW,bar) : sendErrorMessage(); break;
		case 3: player->getMoney() >= 300 ? playerBought(player, 300, WING_ATTACK,bar) : sendErrorMessage(); break;
		case 4: player->getMoney() >= 400 ? playerBought(player, 400, BOX_ATTACK,bar) : sendErrorMessage(); break;
		case 5: m_page = 2;  m_SpriteRect.left = 550; m_Item.setTextureRect(m_SpriteRect); break;
		default: return true;
		}
	}
	else if (m_page == 2)
	{
		switch (i)
		{
		case 0: player->getMoney() >= 400 ? playerBought(player, 400, AXE,bar) : sendErrorMessage(); break;
		case 1: player->getMoney() >= 200 ? playerBought(player, 200, FIRE_HAMMER,bar) : sendErrorMessage(); break;
		case 2: player->getMoney() >= 200 ? playerBought(player, 200, ELECTRIC_HAMMER,bar) : sendErrorMessage(); break;
		case 3: player->getMoney() >= 200 ? playerBought(player, 200, ICE_HAMMER,bar) : sendErrorMessage(); break;
		case 4: player->getMoney() >= 550 ? playerBought(player, 550, KAMEAMA,bar) : sendErrorMessage(); break;
		case 5: m_page = 1; m_SpriteRect.left = 0; m_Item.setTextureRect(m_SpriteRect); break;
		default: return true;
		}
	}
	return false;
}
//--------------------------------------------
void Merchant::playerBought(const std::shared_ptr<Player>& player, int price, const std::string& weaponName, Bar& bar)
{
	if (player->getSpacielAttackNum() > 4 && !player->isHaveThisWeapon(weaponName)) //karni
	{
		m_messeges.setString("Cannot buy, already have 4 skills");
		m_messeges.setFillColor(sf::Color::Red);
		return;
	}
	if (player->addSpacielAttack(weaponName))
	{
		m_messeges.setString("Congratulation, skill purches succsefuly!");
		m_messeges.setFillColor(sf::Color::Green);
		bar.setNewSpacielAttack(weaponName);
	}
	else
	{
		m_messeges.setString("Congratulation, the skill gained additional 5 attack!");
		m_messeges.setFillColor(sf::Color::Magenta);
	}
	player->decMoney(price);
}
//--------------------------------------------
void Merchant::sendErrorMessage()
{
	m_messeges.setString("Not enough money in your balance");
	m_messeges.setFillColor(sf::Color::Red);
}