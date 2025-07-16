#include "Bar.h"
#include "DataManager.h"

// Initializes the texture of the object's life state
//  according to the team it belongs to
//----------------------------------------------
void Bar::initBar()
{
	m_backroundItem.setTexture(DataManager::instence().getGameTexture().m_topBrackround);
	m_backroundItem.setPosition(0, 0);
	m_character.setTexture(DataManager::instence().getGameTexture().m_charectersIcon);
	m_charecterRect.height = 122;
	m_charecterRect.width = 122;
	m_mana.setTexture(DataManager::instence().getGameTexture().m_manaBar);
	m_mana.setPosition(400, 115);
	m_manaRect.height = 10;
	m_manaRect.width = 100;
	m_character.setPosition(50,50);
	if(!m_isSet)
		setcharacter(BAT_ENUM);
}
//Updates the image of the player on the data bar
//----------------------------------------------
void Bar::setcharacter(int characterNum)
{
	switch (characterNum)
	{
	case CHARACTERS::BAT_ENUM: m_charecterRect.left = 0; break;
	case CHARACTERS::DEEP_ENUM: m_charecterRect.left = 122; break;
	case CHARACTERS::DENNIES_ENUM: m_charecterRect.left = 244; break;
	case CHARACTERS::LOUIS_ENUM: m_charecterRect.left = 366; break;
	case CHARACTERS::JULIAN_ENUM: m_charecterRect.left = 488; break;
	default: m_charecterRect.left = 0;
	}
	m_character.setTextureRect(m_charecterRect);
	m_isSet = true;
}
// Shows in the status bar which special attacks the player has acquired
//-----------------------------------------------------------
void Bar::setNewSpacielAttack(const std::string& str)
{
	m_skills.push_back(sf::Sprite());
	m_skills[m_skills.size() - 1].setTexture(DataManager::instence().getTexture(str));
	m_skills[m_skills.size() - 1].setOrigin(16, 16);
	m_skills[m_skills.size() - 1].setPosition((m_skills.size() - 1) * 40 + 690, 115);
	m_rectForSkills.push_back(sf::IntRect(192, 0, 32, 32));
	m_skills[m_skills.size() - 1].setTextureRect(m_rectForSkills[m_rectForSkills.size() - 1]);
}
// Updates the bar according to new purchases in the store
//-----------------------------------------------------------
void Bar::updateBar(const std::shared_ptr<Player>& player)
{
	float tempRatio;
	if (player->getSkills().size() != m_skills.size() || m_skills.size() != m_rectForSkills.size())
	{
		std::cout << "need exeption here"; //karni
	}
	for (int i = 0; i < m_skills.size(); i++)
	{
		if (player->getSkills()[i]->isUsedRecently())
		{
			m_rectForSkills[i].left = 0;
			m_skills[i].setTextureRect(m_rectForSkills[i]);
			continue;
		}
		tempRatio = m_rectForSkills[i].left / 192.f;
		if (player->getSkills()[i]->getCooldownRatio() > tempRatio)
		{
			m_rectForSkills[i].left += 32;
			m_skills[i].setTextureRect(m_rectForSkills[i]);
		}
	}
	float temp = player->getManaRatio() * 100;
	int tempInt = temp / 10;
	m_manaRect.left = tempInt * 100 - 100;
	if (m_manaRect.left < 0)
		m_manaRect.left = 0;
	m_mana.setTextureRect(m_manaRect);

}
//--------------------------------------
void Bar::draw(sf::RenderWindow& window, float x)
{
	m_backroundItem.setPosition(sf::Vector2f(x, m_backroundItem.getPosition().y));
	m_mana.setPosition(sf::Vector2f(x + MANA_X_POSITION, m_mana.getPosition().y));
	m_character.setPosition(sf::Vector2f(x + CHARACTERS_X_POSITION, m_character.getPosition().y));
	window.draw(m_backroundItem);
	window.draw(m_character);
	window.draw(m_mana);
	for (int i = 0; i < m_skills.size(); i++)
	{
		m_skills[i].setPosition(sf::Vector2f(x + SKILL_X_POSITION[i], m_skills[i].getPosition().y));
		window.draw(m_skills[i]);
	}
}