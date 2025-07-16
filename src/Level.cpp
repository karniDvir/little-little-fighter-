#include "Level.h"
#include "InfoFromTxt.h"

Level::Level()
{
	//if (!SetNextLevelFile())
	//	std::cout << "c-tor Level can't reat file";
}
//-----------------------------
Level::~Level()
{
	/*if (m_file.is_open())
		m_file.close();
	if(m_playlist.is_open())
		m_playlist.close();*/
}
//--------------------------------
bool Level::ReadNewLevel()
{
	 // to read the string of the next level
	if (SetNextLevelFile() && m_file.is_open())
	{
		readFromFile(); //read the existing file		
		m_file.close();
		ObjectManager::instence().setNumOfEnemies();
		return true;
	}
	return false;
}
//------------------------------
bool Level::SetNextLevelFile()
{
	if (!m_playlist.is_open())
		m_playlist.open("Playlist.txt");
	if (m_playlist.is_open())
	{
		std::string temp;
		if (!m_playlist.eof() && getline(m_playlist, temp))
		{
			m_file.open(temp);
			std::cout << "File " << temp << " open  \n";//-----------------------------------
			return true;
		}
		DataManager::instence().setLevelStatus(WIN_GAME);
		if(!m_file.is_open())
			m_file.close();
		m_playlist.close();
		return false;
	}
	return false;
}
//-------------------------------
void Level::readFromFile()
{
	if (m_file.is_open())
	{
		int index = 0;
		std::string temp;
		while (!m_file.eof() && getline(m_file, temp))
		{
			if (temp == "Backround" && !m_file.eof())
			{
				m_file >> index;
				DataManager::instence().setBackroundIndex(index);
				continue;
			}
			else if (temp == "Enemies" && !m_file.eof())
				while (!m_file.eof() && getline(m_file, temp) && temp != "Players")
					creatNewObject(temp, true);

			if (temp == "Players" && !m_file.eof())
				while (!m_file.eof() && getline(m_file, temp))
					creatNewObject(temp, false);
		}
	}
}
//----------------------------------
// read the name of the Obj the posotion 
void Level::creatNewObject(const std::string& object_info, bool is_enemies_obj)
{
	try
	{
		std::istringstream iss(object_info);
		std::string tempStr;     //exeptions
		//iss >> tempStr;  //exeptions
		if (!(iss >> tempStr))
		{
			throw std::invalid_argument("Invalid object_info format");
		}
		tempStr[0] = std::toupper(tempStr[0]);
		float tempFloat;
		auto temp = ObjectManager::instence().getObjectMap().find(tempStr);
		if (temp == ObjectManager::instence().getObjectMap().end())
			throw std::out_of_range("Object key not found in the map");

		infoFromTxt tempInfo;
		tempInfo.Enemyteam = is_enemies_obj;
		auto obj = temp->second();
		tempInfo.name = tempStr; //1. Object name
		if (!(iss >> tempInfo.position.x) || !(iss >> tempInfo.position.y)) {
			throw std::invalid_argument("Invalid position format");
		}
		if (iss >> tempFloat)
			tempInfo.speed = tempFloat; // speed
		if (iss.eof() && is_enemies_obj)
		{
			obj->readInfo(tempInfo);
			ObjectManager::instence().addToEnemyObject(obj); // 
			return;
		}
		if (iss >> tempFloat)
			tempInfo.SpeedDeviation = tempFloat; // 
		if (iss >> tempStr)
			tempInfo.weapon = tempStr;
		while (!iss.eof() && iss >> tempStr)
			tempInfo.attacks.push_back(tempStr);
		obj->readInfo(tempInfo);
		if (is_enemies_obj)
			ObjectManager::instence().addToEnemyObject(obj);
		else
			ObjectManager::instence().addToPlayerObject(obj); // 
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << "\n";
	}
	/*catch (const std::invalid_argument& ex)
	{
		std::cout << ex.what() << "\n";
	}
	catch (const std::invalid_argument& ex) {}*/

}

