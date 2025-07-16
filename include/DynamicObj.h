#pragma once
#include "GameObj.h"
#include <SFML/Graphics.hpp>

class DynamicObj : public GameObj
{
public:
	DynamicObj();
	int getAttackPower() const;
	void setAttackPower(const int& power);
	virtual void move(const sf::Time& ) {};
	sf::Vector2f getDiraction() const;
	float getSpeed() const;
	sf::IntRect getRectangle() const;
	void initRectangle(const int& rowSize,const int& colSize);
	~DynamicObj() = default;
	void setSpeed(float speed);
	void setBlocked(const bool& isBlocked);
	bool isBlocked() const;
	bool areEnemyTeam() const;
protected:
	void setLeftRectngle(int row);
	void setRectangleSize(int height, int width);
	virtual void handleRectable(const sf::Time& deltaTime) = 0;
	void setDiraction(const sf::Vector2f& diraction);
	void setRecTangle();
	void SetTopRectangle(int col);
	void AddLeftRectangle(int row);
	void AddTopRectangle(int col);
	void ResetLeftRectngle();
	int getTileHeight() const;
	int getTileWidth() const;
	void setEnemyTeam(bool);
private:
	sf::Vector2f m_diraction;
	sf::IntRect m_recTexture;
	bool m_blocked;
	float m_speed;
	int m_attackPower;
	bool m_enemyTeam;
};