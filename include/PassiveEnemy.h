#pragma once
#include <SFML/Graphics.hpp>
#include "PassiveObj.h"


class PassiveEnemy : public PassiveObj	
{
public:
	PassiveEnemy() ;
	void move(const sf::Time& deltaTime) {  } override;
private:

};
PassiveEnemy::PassiveEnemy()
{
}

