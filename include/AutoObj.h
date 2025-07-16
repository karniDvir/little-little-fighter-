#pragma once
#include "ActiveObj.h"
#include <SFML/Graphics.hpp>

class  AutoObj: public ActiveObj
{
public:
	AutoObj() ;
	~AutoObj() = default;
	void move(const sf::Time& deltaTime) override;
private:
	void handleMovment(int LengthToEnemy);
	int setNextActiveAlgorithem(int LengthToEnemy);
	bool ActiveAlgorithem1();
	bool ActiveAlgorithem2();
	bool ActiveAlgorithem3();
};