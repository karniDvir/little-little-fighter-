#pragma once
#include <fstream>
#include <string>
#include "GameObj.h"
#include "ObjectManager.h"
#include <sstream>


class Level
{
public:
	Level();
	~Level();
	bool ReadNewLevel() ;
			
private:
	void creatNewObject(const std::string& temp, bool is_enemies_obj);
	void readFromFile();
	std::ifstream m_file ,
				m_playlist;

	bool SetNextLevelFile() ;

};

