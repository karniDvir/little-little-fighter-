#include "MusicManager.h"
#include <SFML/Audio.hpp>
//---------------------------------------
void MusicManager::loadMusic()
{
	m_music.openFromFile("GameMusic.ogg");
	m_transitionMusic.openFromFile("transitionMusic.ogg");
	spacielAttack1.loadFromFile("Spacielattack.ogg");
	spacielAttack2.loadFromFile("Spacielattack2.ogg");
	normalAttack1.loadFromFile("005.wav");
	normalAttack2.loadFromFile("006.wav");
	normalAttack3.loadFromFile("004.wav");
	hurtSound.loadFromFile("001.wav");
	byebyeSound.loadFromFile("byebye.wav");
	throwAttack1.loadFromFile("002.wav");
	throwAttack2.loadFromFile("003.wav");
	m_win.openFromFile("WinMusic.ogg");
}
//----------------------------------------------
void MusicManager::initMusic()
{
	loadMusic();
	m_music.setLoop(true);
	m_music.setVolume(80);
	m_transitionMusic.setLoop(true);
	m_transitionMusic.setVolume(80);
}
//-----------------------------------------------
void MusicManager::startGameMusic()
{
	m_music.play();
}
//-----------------------------------------------
void MusicManager::stopGameMusic()
{
	m_music.stop();
}
//------------------------------------------------
void MusicManager::stopTransitionMusic()
{
	m_transitionMusic.stop();
}
//-----------------------------------------------
void MusicManager::startTrasitionMusic()
{
	if(m_transitionMusic.getStatus() != sf::SoundSource::Playing)
		m_transitionMusic.play();
}
//------------------------------------------------
void MusicManager::stopWinMusic()
{
	m_win.play();
}
//------------------------------------------------
void MusicManager::startWinMusic()
{
	m_win.stop();
}
//------------------------------------------------
void  MusicManager::endAllMusic()
{
	if (m_transitionMusic.getStatus() != sf::SoundSource::Stopped)
		stopTransitionMusic();
	if (m_music.getStatus() != sf::SoundSource::Stopped)
		stopGameMusic();
	if (m_win.getStatus() != sf::SoundSource::Stopped)
		stopWinMusic();
}