#include "DataManager.h"
//--------------------------------------
DataManager& DataManager::instence()
{
	static auto manger = DataManager();
	return manger;
}
//-------------------------------------
DataManager::DataManager()
	:
	m_level_status(CURRENT_LEVEL),
	m_backroundIndex(0)
{}
//--------------------------------------
void DataManager::LoadObj()
{
	m_textures.loadTexture();
	initSpacielAttackMap();
	initTextureMap();
	initcharacterInfoMap();
	m_music.initMusic();
}
//--------------------------------------------------
void DataManager::setWindowPosition(const sf::Vector2i& position)
{
	m_windowPosition = position;
}
//----------------------------------
sf::Vector2i DataManager::getWindowPosition() const
{
	return m_windowPosition;
}
//----------------------------------

GameTexture& DataManager::getGameTexture()
{
	return m_textures;
}

//-----------------------------------
MusicManager& DataManager::getGameMusic()
{
	return m_music;
}
//-----------------------------------

sf::Texture* DataManager::getLevelTexture()
{
	return m_textures.m_backround;
}
//-----------------------------------
int DataManager::getBackroundIndex() const
{
	if (m_backroundIndex > 0 && m_backroundIndex < BACKROUND_SIZE)
		return m_backroundIndex;
	return 0;
}
//-----------------------------------
void DataManager::setBackroundIndex(const int& new_index)
{
	if (new_index > 0 && new_index < BACKROUND_SIZE)
		m_backroundIndex = new_index;
}
//-----------------------------------
sf::Vector2f DataManager::getPlayerPosition()
{
	return m_playerPosition;
}
//-----------------------------------
void DataManager::setPlayerPosition(const sf::Vector2f& position)
{
	m_playerPosition.x = position.x;
	m_playerPosition.y = position.y;
}
//-----------------------------------
void DataManager::initSpacielAttackMap()
{
	m_SpacielattackMap.insert(std::make_pair(ICE_HAMMER,SpaceilAttackStats(300,150,30, &m_textures.m_hammer, ICE_HAMMER)));
	m_SpacielattackMap.insert(std::make_pair(NORMAL_BOW, SpaceilAttackStats(300, 150, 30, &m_textures.m_bow, NORMAL_BOW)));
	m_SpacielattackMap.insert(std::make_pair("Demon", SpaceilAttackStats(300, 150, 30, &m_textures.m_demon, "Demon")));
	m_SpacielattackMap.insert(std::make_pair(FIRE_HAMMER,SpaceilAttackStats(300, 100, 30, &m_textures.m_fireHammer, FIRE_HAMMER)));
	m_SpacielattackMap.insert(std::make_pair(ELECTRIC_HAMMER, SpaceilAttackStats(300, 100, 30, &m_textures.m_electricHammer, ELECTRIC_HAMMER)));
	m_SpacielattackMap.insert(std::make_pair(AXE, SpaceilAttackStats(300, 100, 30, &m_textures.m_axe, AXE)));
	m_SpacielattackMap.insert(std::make_pair(SOWRD ,SpaceilAttackStats(300, 100, 30, &m_textures.m_sowrd, SOWRD)));
	m_SpacielattackMap.insert(std::make_pair(LIGHT_BOW,SpaceilAttackStats(300, 100, 30, &m_textures.m_lightBow, LIGHT_BOW)));
	m_SpacielattackMap.insert(std::make_pair(BOX_ATTACK, SpaceilAttackStats(300, 100, 30, &m_textures.m_Box, BOX_ATTACK)));
	m_SpacielattackMap.insert(std::make_pair(WING_ATTACK, SpaceilAttackStats(300, 100, 30, &m_textures.m_wing, WING_ATTACK)));
	m_SpacielattackMap.insert(std::make_pair(KAMEAMA, SpaceilAttackStats(300, 100, 30, &m_textures.m_kmeama, KAMEAMA)));
}
//------------------------------------
void DataManager::initcharacterInfoMap()
{
	m_characterInfo.insert(std::make_pair(BAT, characterInfo(BAT, FIRE_ATTACK, ICE_ATTACK)));
	m_characterInfo.insert(std::make_pair(JULIAN, characterInfo(JULIAN, SKULL_ATTACK, MAGIC_ATTACK)));
	m_characterInfo.insert(std::make_pair(LOUIS, characterInfo(LOUIS, SKULL_ATTACK, FIRE_ATTACK)));
	m_characterInfo.insert(std::make_pair(DEEP, characterInfo(DEEP, FIRE_ATTACK, BAT_ATTACK)));
	m_characterInfo.insert(std::make_pair(DENNIS, characterInfo(DENNIS, BAT_ATTACK, MAGIC_ATTACK)));
}
//------------------------------------
characterInfo& DataManager::getCharecterInformation(const std::string& str)
{
	if (m_characterInfo.find(str) == m_characterInfo.end())
	{
		throw std::out_of_range("Object key not found in the map");
		//characterInfo temp("NONE", "NONE", "NONE");
	}
	return m_characterInfo[str];
}
//------------------------------------
const SpaceilAttackStats& DataManager::getSpacielAttackInfo(const std::string& str)
{
	if (m_SpacielattackMap.find(str) == m_SpacielattackMap.end())
		throw std::out_of_range("Object key not found in the map");
	//return SpaceilAttackStats(-1, -1, -1, nullptr, "NONE"); //exetption
	return m_SpacielattackMap[str];
}
//------------------------------------
const sf::Texture& DataManager::getTexture(const std::string& str) const 
{
	try
	{
		if (m_textureMap.find(str) == m_textureMap.end())
			throw std::out_of_range(str); //-------------------------
		return *m_textureMap.at(str);
	}
	catch (const std::out_of_range& ex) {
		if (ex.what()[0] >= 'a' && ex.what()[0] <= 'z')
		{
			//std::cout << ex.what() << "\n";//---------------------
			std::string modifiedName = ex.what();
			modifiedName[0] = std::toupper(modifiedName[0]);
			m_textureMap.find(modifiedName);
			return *m_textureMap.at(modifiedName);
		}
		else
			return  *m_textureMap.at(BAT);
	}
}
//------------------------------------
LevelType DataManager::getLevelStatus()
{
	return m_level_status;
}
//-----------------------------------
void DataManager::setLevelStatus( LevelType status)
{
	m_level_status = status;
}

//------------------------------------
void DataManager::initTextureMap()
{
	m_textureMap.insert(std::make_pair(BAT, &m_textures.m_batTexture));
	m_textureMap.insert(std::make_pair(LOUIS, &m_textures.m_louis));
	m_textureMap.insert(std::make_pair(DEEP, &m_textures.m_deep));
	m_textureMap.insert(std::make_pair(JULIAN, &m_textures.m_julian));
	m_textureMap.insert(std::make_pair(DENNIS, &m_textures.m_dennis));
	////////////////////////////////////////////////////////////
	m_textureMap.insert(std::make_pair("Cow", &m_textures.m_cow));
	m_textureMap.insert(std::make_pair("Troll", &m_textures.m_troll));
	m_textureMap.insert(std::make_pair("Monkey", &m_textures.m_monkey));
	m_textureMap.insert(std::make_pair("Dragon", &m_textures.m_dragon));
	//////////////////////////////////////////////////////////////
	m_textureMap.insert(std::make_pair(AXE, &m_textures.m_axeIcon));
	m_textureMap.insert(std::make_pair(BOX_ATTACK, &m_textures.m_boxIcon));
	m_textureMap.insert(std::make_pair(ELECTRIC_HAMMER, &m_textures.m_electricHammerIcon));
	m_textureMap.insert(std::make_pair(FIRE_HAMMER, &m_textures.m_fireHammerIcon));
	m_textureMap.insert(std::make_pair(ICE_HAMMER, &m_textures.m_iceHammerIcon));
	m_textureMap.insert(std::make_pair(KAMEAMA, &m_textures.m_kamehameaIcon));
	m_textureMap.insert(std::make_pair(LIGHT_BOW, &m_textures.m_lightBowIcon));
	m_textureMap.insert(std::make_pair(NORMAL_BOW, &m_textures.m_normalBowIcon));
	m_textureMap.insert(std::make_pair(SOWRD, &m_textures.m_sowrdIcon));
	m_textureMap.insert(std::make_pair(WING_ATTACK, &m_textures.m_wingIcon));
	//////////////////////////////////////////////////////////////
	m_textureMap.insert(std::make_pair(ICE_ATTACK, &m_textures.m_iceBall));
	m_textureMap.insert(std::make_pair(MAGIC_ATTACK, &m_textures.m_magicBall));
	m_textureMap.insert(std::make_pair(FIRE_ATTACK, &m_textures.m_fireBall));
	m_textureMap.insert(std::make_pair(SKULL_ATTACK, &m_textures.m_skullAttack));
	m_textureMap.insert(std::make_pair(BAT_ATTACK, &m_textures.m_batAttack));
}