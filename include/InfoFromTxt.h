#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

struct infoFromTxt
{
	sf::Vector2f position;
	std::string name = "";
	float speed = 1;
	float SpeedDeviation = 0;
	bool Enemyteam = true; //  
	std::string weapon = "NONE";
	std::vector<std::string> attacks;
};