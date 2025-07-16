#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameTexture.h"
#include <unordered_map>
#include "musicManager.h"
#include "CharacterInfo.h"
#include <iostream>
#include "SpacielAttackStats.h"

const std::string ICE_HAMMER = "Hammer";
const std::string NORMAL_BOW = "Bow";
const std::string FIRE_HAMMER = "FireHammer";
const std::string ELECTRIC_HAMMER = "ElectricHammer";
const std::string AXE = "Axe";
const std::string SOWRD = "SowrdAttack";
const std::string LIGHT_BOW = "LightBow";
const std::string BOX_ATTACK = "BoxAttack";
const std::string KAMEAMA = "Kmeama";
const std::string WING_ATTACK = "WingAttack";
//----------------------------------------
const std::string JULIAN = "Julian";
const std::string LOUIS = "Louis";
const std::string BAT = "Bat";
const std::string DEEP = "Deep";
const std::string DENNIS = "Dennis";
//----------------------------------------
const std::string MAGIC_ATTACK = "MagicAttack";
const std::string FIRE_ATTACK = "FireAttack";
const std::string ICE_ATTACK = "IceAttack";
const std::string BAT_ATTACK = "BatAttack";
const std::string SKULL_ATTACK = "SkullAttack";

const int NUM_OF_ATTACKS = 10;

enum LevelType
{
	CURRENT_LEVEL,
	NEXT_LEVEL,
	RESET_LEVEL,
	GAME_OVER,
	WIN_GAME
};
class DataManager
{
public:
	static DataManager& instence();
	sf::Texture* getLevelTexture();
	DataManager(const DataManager&) = delete;
	void operator=(const DataManager&) = delete;
	void LoadObj();
	GameTexture& getGameTexture();
	MusicManager& getGameMusic();
	void initTextureMap();
	void setWindowPosition(const sf::Vector2i& position);
	sf::Vector2i getWindowPosition() const;
	sf::Vector2f getPlayerPosition();
	void setPlayerPosition(const sf::Vector2f& position);
	void initSpacielAttackMap();
	void initcharacterInfoMap();
	const sf::Texture& getTexture(const std::string&) const;
	const SpaceilAttackStats& getSpacielAttackInfo(const std::string& str);
	characterInfo& getCharecterInformation(const std::string& str);
	int getBackroundIndex() const ;
	void setBackroundIndex(const int& );
	void setLevelStatus(LevelType );
	LevelType getLevelStatus();
private:
	DataManager();
	GameTexture m_textures;
	MusicManager m_music;
	//TimeManager m_time;
	LevelType m_level_status;
	int m_backroundIndex;
	sf::Vector2i m_windowPosition;
	sf::Vector2f m_playerPosition;
	sf::Sprite m_livesSprite;
	std::unordered_map<std::string, characterInfo> m_characterInfo;
	std::unordered_map<std::string, sf::Texture*> m_textureMap;
	std::unordered_map<std::string, SpaceilAttackStats> m_SpacielattackMap;
};