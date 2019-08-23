#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

class Files//singletone class 
{
public:
	sf::Texture* getPic(int i);
	static Files & instance();
	sf::Font* getFont();
	void Mute();
	void MusicOn();
	void PlayBackground();
	void PlayEat();
	void PlayKill();
	void PlayClick();
	void PlayChamp();
	void stopChamp();
	void stopBackground();
private:
	Files();
	sf::Texture m_pic[11];
	sf::Music m_sound[5];
	sf::Font m_font;


};

