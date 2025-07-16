#pragma once 

struct characterInfo
{
	characterInfo() {};
	characterInfo(const std::string& name, const std::string& attack1, const std::string& attack2) :
		m_characterName(name), m_attack1Name(attack1), m_attack2Name(attack2) {};
	std::string m_characterName;
	std::string m_attack1Name;
	std::string m_attack2Name;
};
