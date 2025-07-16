#include "Board.h"
//---------------------------------------------------------
Board::Board()
{ 
	srand((unsigned)time(NULL));
	m_player = std::make_shared<Player>();
	ObjectManager::instence().addPlayer(m_player); // creat the main object
}

//Initializes the board's variables
//Creates the objects from the file and puts them into vectors
// also update the size of the window 
//------------------------------------------------------------
void Board::initBoard()
{
	try
	{
		if (m_level.ReadNewLevel())
			m_backround.initBackround();
	}
	catch (std::exception& ex) { }
}

//The main move func that moves all objects on the board 
//  And Checking which collisions were in the move
//-------------------------------------------------------------
void Board::moveObj(const sf::Time& deltaTime)
{
	try {
		AttackManager::instence().moveAttacks(deltaTime);
		ObjectManager::instence().moveObjects(deltaTime);
		ObjectManager::instence().handleCollision();
	}
	catch (const std::out_of_range& ex)
	{
		//std::cout << ex.what() << "\n"; // debug
	}
	catch (const std::exception& ex)
	{
		if (strcmp(ex.what(), "GameOver") == 0) {}
			//throw std::exception(ex);
	}
}
//The main object drawing function
// Goes through all the moving members in the board and prints them
//  according to their y coordinates so that they are not displayed sloppily
//-------------------------------------------------------------
void Board::draw(sf::RenderWindow& window)
{
	m_backround.draw(window);
	int arr[3] = { -1 };
	AttackManager::instence().sort();
	ObjectManager::instence().sort();
	auto pair1 = AttackManager::instence().getIterAttacks();
	auto pair2 = ObjectManager::instence().getItersEnemyObj();
	auto pair3 = ObjectManager::instence().getItersPlayerObj();
	while ((pair1.first != pair1.second) || (pair2.first != pair2.second) || (pair3.first != pair3.second))
	{
		arr[0] = (pair1.first != pair1.second)? pair1.first->get()->getPosition().y : -1;
		arr[1] = (pair2.first != pair2.second)? pair2.first->get()->getPosition().y : -1;
		arr[2] = (pair3.first != pair3.second)? pair3.first->get()->getPosition().y : -1;
		int max = UpdateDrawArray(arr);
		switch (max)
		{
		case 0: pair1.first->get()->draw(window); pair1.first++; break;
		case 1: if (pair2.first->get()->checkInView()) { pair2.first->get()->draw(window); } pair2.first++;  break;
		case 2: if (pair3.first->get()->checkInView()) { pair3.first->get()->draw(window); } pair3.first++;  break;
		}
	}
}



// called from the controller when need up to the next level
//  or just clear the vectors according the leveltype
//-------------------------------------------------
void Board::changelevel()
{
	m_player->UpdateNextLevel();
	ObjectManager::instence().UpdatePleyerTeamPosition();
	DataManager::instence().setLevelStatus(CURRENT_LEVEL);
	DataManager::instence().setPlayerPosition(m_player->getPosition());
	if (m_level.ReadNewLevel())
		m_backround.initBackround();
}
//-----------------------------------------------------
int Board::UpdateDrawArray(const int arr[])
{
	int max = 999;
	int maxIndex = 0;
	for (int i = 0; i < 3; i++)
	{
		if (arr[i] < max && arr[i] != -1)
		{
			max = arr[i];
			maxIndex = i;
		}
	}
	return maxIndex;
}

//----------------------------------------------------
void Board::GameOver()
{
	ObjectManager::instence().EndGame();
}
//----------------------------------------------------
const std::shared_ptr <Player>& Board::getPLayer()
{
	return m_player;
}