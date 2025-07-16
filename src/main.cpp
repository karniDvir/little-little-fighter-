#pragma once
#include "Controller.h"
#include "DataManager.h"
#include <iomanip>
#include "Weapon.h"
#include "AttackManager.h"
#include "ObjectManager.h"

int main()
{
	ObjectManager::instence().initObjectMap();
	AttackManager::instence().initAttackMap();
	DataManager::instence().LoadObj();
	auto controller = Controller();
	controller.run();
	return EXIT_SUCCESS;
}
