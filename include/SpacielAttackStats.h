#pragma once
#include <SFML/Graphics.hpp>


struct SpaceilAttackStats
{
	SpaceilAttackStats() {};
	SpaceilAttackStats(int mana, int cooldown, int attack, sf::Texture* texture, const std::string& attackName)
		: m_Attack(attack),
		m_cooldownForAttack(cooldown),
		m_requiredMana(mana),
		m_texture(texture),
		m_attackName(attackName)
	{
		
	};
	
	int m_requiredMana = 300 ,
		m_cooldownForAttack = 150,
		m_Attack = 30 ;
	sf::Texture* m_texture;
	std::string m_attackName = "NONE";
};