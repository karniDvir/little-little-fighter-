#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "DataManager.h"

const int UPPER_BOUND = 630;
const int LEFT_BOUND = 0;
const int RIGHT_BOUND = 2350;
const int DOWN_BOUND = 790;

class GameObj
{
public:
	GameObj() {};
	GameObj(const sf::Vector2f& position);
	virtual ~GameObj() {};
	virtual void move(const sf::Time& deltaTime) = 0;
	virtual void draw(sf::RenderWindow& window);
	sf::FloatRect getSpriteGlobalBounds() const;
	sf::Vector2f getPosition() const;
	virtual void initSprite(const sf::Vector2f& , const sf::Vector2f& ) {};
	virtual void initSprite(const sf::Vector2f& position);
	void setPositionSprite(const sf::Vector2f& position);
	void setScale(const sf::Vector2f& scale);
	void setTexture(const sf::Texture& texture);
	virtual const sf::FloatRect& getSmallerBounds() const;
protected:
	void playSound(const sf::SoundBuffer& sound);
	sf::Vector2f getGlobalBounds() const;
	void setOrgin();
	void setOrgin(const sf::Vector2f& orgin);
	void moveSprite(const sf::Vector2f& diraction, const float& speed);
	void setTextureRect(const sf::IntRect& Rextangle);
	void setScale(const float&, const float&);
	const sf::Vector2f& getScale() const;
private:
	sf::Sprite m_sprite;
	sf::Sound m_sound;
};