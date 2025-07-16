#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class MusicManager
{
public:
	void initMusic();
	void startGameMusic();
	void stopGameMusic();
	void stopTransitionMusic();
	void startTrasitionMusic();
	void stopWinMusic();
	void startWinMusic();
	void endAllMusic();
	sf::SoundBuffer spacielAttack1;
	sf::SoundBuffer spacielAttack2;
	sf::SoundBuffer normalAttack1;
	sf::SoundBuffer normalAttack2;
	sf::SoundBuffer normalAttack3;
	sf::SoundBuffer hurtSound;
	sf::SoundBuffer byebyeSound;
	sf::SoundBuffer throwAttack1;
	sf::SoundBuffer throwAttack2;
private:
	void loadMusic();
	sf::Music m_transitionMusic;
	sf::Music m_music;
	sf::Music m_win;

};
