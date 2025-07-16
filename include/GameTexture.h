#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
const int BACKROUND_SIZE = 4;
struct GameTexture
{
	sf::Font m_font;
	sf::Texture m_menu;
	//-------------------------------------------------
	sf::Texture m_backround[BACKROUND_SIZE];
	//-------------------------------------------------
	sf::Texture m_batTexture;
	sf::Texture m_dennis;
	sf::Texture m_louis;
	sf::Texture m_julian;
	sf::Texture m_deep;
	//-------------------------------------------------
	sf::Texture m_hammer;
	sf::Texture m_bow;
	sf::Texture m_demon;
	sf::Texture m_fireHammer;
	sf::Texture m_electricHammer;
	sf::Texture m_axe;
	sf::Texture m_sowrd;
	sf::Texture m_lightBow;
	sf::Texture m_Box;
	sf::Texture m_wing;
	sf::Texture m_kmeama;
	//-------------------------------------------------
	sf::Texture m_troll;
	sf::Texture m_dragon;
	sf::Texture m_cow;
	sf::Texture m_monkey;
	//-------------------------------------------------
	sf::Texture m_magicBall;
	sf::Texture m_fireBall;
	sf::Texture m_iceBall;
	sf::Texture m_batAttack;
	sf::Texture m_skullAttack;
	//-------------------------------------------------
	sf::Texture m_enemyLifeBar;
	sf::Texture m_PlayerLifeBar;
	//-------------------------------------------------
	sf::Texture m_merchantBackround;
	sf::Texture m_merchantItem;
	sf::Texture m_exit;
	//-------------------------------------------------
	sf::Texture m_axeIcon;
	sf::Texture m_boxIcon;
	sf::Texture m_electricHammerIcon;
	sf::Texture m_fireHammerIcon;
	sf::Texture m_iceHammerIcon;
	sf::Texture m_kamehameaIcon;
	sf::Texture m_lightBowIcon;
	sf::Texture m_normalBowIcon;
	sf::Texture m_sowrdIcon;
	sf::Texture m_wingIcon;
	sf::Texture m_charectersIcon;
	sf::Texture m_manaBar;
	sf::Texture m_topBrackround;
	//--------------------------------------------------
	sf::Texture m_gameOver;
	sf::Texture m_youWon;
	void loadTexture();
};
//-------------------------------------------
