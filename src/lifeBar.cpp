#include "lifeBar.h"

//-------------------------------------------
void lifeBar::initLifeBar(const bool& IsEnemy)
{
	if (IsEnemy)
		m_lifeBar.setTexture(DataManager::instence().getGameTexture().m_enemyLifeBar);
	else
		m_lifeBar.setTexture(DataManager::instence().getGameTexture().m_PlayerLifeBar);
	m_lifeBar.setOrigin(35, 2.5);
	m_recTexture.height = BAR_HEIGHT;
	m_recTexture.width = BAR_LEN;
	m_recTexture.top = 0;
	m_recTexture.left = 0;
	m_lifeBar.setTextureRect(m_recTexture);
}
//-------------------------------------------
void lifeBar::setMaxLife(int life)
{
	m_maxLife = life;
}
//-------------------------------------------
void lifeBar::setPosition(const sf::Vector2f& position)
{
	m_lifeBar.setPosition(position);
}
//-------------------------------------------
void lifeBar::setLifeBar(float life)
{
	float temp = 560 - m_recTexture.left;
	float currentLife = life / m_maxLife;
	float currentBarPlace = temp / 560.f;
	if (currentLife < currentBarPlace)
		UpdateBar();
}
//------------------------------------------
void lifeBar::draw(sf::RenderWindow& window)
{
	window.draw(m_lifeBar);
}

//-------------------------------------------
void lifeBar::UpdateBar()
{
	if (m_recTexture.left < 490)
		m_recTexture.left += BAR_LEN;
	m_lifeBar.setTextureRect(m_recTexture);
}
//-------------------------------------------
const int& lifeBar::getMaxLife() const
{
	return m_maxLife;
}
