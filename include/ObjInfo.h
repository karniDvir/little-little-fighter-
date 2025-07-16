#pragma once
#include <string>

struct ObjInfo
{
	int m_algorithemNum = 0,
		m_statictime = 100,
		m_mana = 400,
		m_act = 0,
		m_waitForAttackTime = 0,
		m_waitTime = 0,
		m_recoveryTime = 100;

	float m_speedDeviation = 0.0f;

	bool m_run = false,
		 m_revers = false,
		m_moving = false;

	int m_currentSate;

};
