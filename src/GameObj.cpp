#include "GameObj.h"
#include <iostream>
//-----------------------------------------------------
void GameObj::draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}
//-------------------------------------------------------
GameObj::GameObj(const sf::Vector2f& position)
{
	setPositionSprite(position);
}
//------------------------------------------------------
void GameObj::setPositionSprite(const sf::Vector2f& position)
{
	//sf::Vector2f newPosition = position;
	//if (position.y > DOWN_BOUND || position.y < UPPER_BOUND)/////////////////////////////////////////////////
	//	newPosition.y = (UPPER_BOUND + DOWN_BOUND) / 2.0f;
	//if (position.x > RIGHT_BOUND || position.x < LEFT_BOUND)
	//	newPosition.y = (UPPER_BOUND + DOWN_BOUND) / 4.0f;
	m_sprite.setPosition(position);
}
//-----------------------------------------------------
void GameObj::setOrgin()
{
	m_sprite.setOrigin(sf::Vector2f(m_sprite.getLocalBounds().left + m_sprite.getLocalBounds().width / 2u,
		m_sprite.getLocalBounds().height / 2u));
}
//------------------------------------------------------
void GameObj::moveSprite(const sf::Vector2f& diraction, const float& speed)
{
	m_sprite.move(diraction * speed);
}
//---------------------------------------------------------
void GameObj::setTextureRect(const sf::IntRect& Rectangle)
{
	m_sprite.setTextureRect(Rectangle);
}
//-------------------------------------------------------
void GameObj::setTexture(const sf::Texture& texture)
{
	m_sprite.setTexture(texture);
}
//-------------------------------------------------------
void GameObj::setScale(const float& x, const float& y)
{
	m_sprite.setScale(x, y);
}
//-----------------------------------------------------
sf::FloatRect GameObj::getSpriteGlobalBounds() const
{
	return m_sprite.getGlobalBounds();
}
//-----------------------------------------------------
sf::Vector2f GameObj::getPosition() const
{
	return m_sprite.getPosition();
}
//-----------------------------------------------------
const sf::Vector2f& GameObj::getScale() const
{
	return m_sprite.getScale();
}
//---------------------------------------------------
void GameObj::playSound(const sf::SoundBuffer& sound)
{
	m_sound.setBuffer(sound);
	m_sound.play();
}
//---------------------------------------------------
sf::Vector2f GameObj::getGlobalBounds() const
{
	return sf::Vector2f(m_sprite.getGlobalBounds().height, m_sprite.getGlobalBounds().width);
}
//-------------------------------------------------------
void GameObj::setScale(const sf::Vector2f& scale)
{
	m_sprite.setScale(scale);
}
//-------------------------------------------------------
void GameObj::initSprite(const sf::Vector2f& position)
{
	setPositionSprite(position);
}
//-------------------------------------------------------
void GameObj::setOrgin(const sf::Vector2f& orgin)
{
	m_sprite.setOrigin(orgin);
}
//-------------------------------------------------------
const sf::FloatRect& GameObj::getSmallerBounds() const
{
	return sf::FloatRect(sf::Vector2f(m_sprite.getPosition().x - 8, m_sprite.getPosition().y - 8),
		sf::Vector2f(20, 20));
}