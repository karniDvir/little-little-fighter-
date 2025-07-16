#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

const int CHARACTERS_X_POSITION = 50;
const int MANA_X_POSITION = 400;
const int SKILL_X_POSITION[4] = { 690,730,770,810 };

enum CHARACTERS {
	BAT_ENUM,
	DEEP_ENUM,
	DENNIES_ENUM,
	LOUIS_ENUM,
	JULIAN_ENUM
};
class Bar
{
public:
	Bar() :m_isSet(false) { initBar(); };
	void initBar();
	void draw(sf::RenderWindow& window, float x);
	void setcharacter(int characterNum);
	void setNewSpacielAttack(const std::string& str);
	void updateBar(const std::shared_ptr<Player>& player);
private:
	bool m_isSet;
	sf::Sprite m_backroundItem;
	sf::Sprite m_character;
	sf::IntRect m_charecterRect;
	sf::IntRect m_manaRect;
	std::vector<sf::Sprite> m_skills;
	std::vector<sf::IntRect> m_rectForSkills;
	sf::Sprite m_mana;
};