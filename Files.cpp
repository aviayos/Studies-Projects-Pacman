#include "Files.h"


Files::Files()
{//loading the icons of the editor.
	m_pic[0].loadFromFile("Pics/Pacman.png");
	m_pic[1].loadFromFile("Pics/Ghost.png");
	m_pic[2].loadFromFile("Pics/Wall.png");
	m_pic[3].loadFromFile("Pics/Cookie.png");
	m_pic[4].loadFromFile("Pics/Background.png");
	m_pic[5].loadFromFile("Pics/Menu_buttons.png");
	m_pic[6].loadFromFile("Pics/Sound_icons.png");
	m_pic[7].loadFromFile("Pics/High_Score.png");
	m_pic[8].loadFromFile("Pics/New_High_Score.png");
	m_pic[9].loadFromFile("Pics/Help.png");
	m_pic[10].loadFromFile("Pics/Pause.png");

	//load sounds
	m_sound[0].openFromFile("Sounds/Background.flac");
	m_sound[0].setVolume(50);
	m_sound[1].openFromFile("Sounds/Bite.wav");
	m_sound[2].openFromFile("Sounds/Kill.wav");
	m_sound[3].openFromFile("Sounds/Click.wav");
	m_sound[4].openFromFile("Sounds/High_Score.flac");

	//load font
	m_font.loadFromFile("Fonts/game_font.TTF");

}
//--------------------------------------------------------------------------------------------
//this method return the icon according to index
sf::Texture* Files::getPic(int i)
{
	return &m_pic[i];
}
//--------------------------------------------------------------------------------------------
//singleton implementation
Files & Files::instance()
{
	static Files inst;
	return inst;
}
//--------------------------------------------------------------------------------------------
sf::Font * Files::getFont()
{
	return &m_font;
}
//--------------------------------------------------------------------------------------------
void Files::Mute()
{
	for (size_t i = 0; i < 5; i++)
		m_sound[i].setVolume(0);
}
//--------------------------------------------------------------------------------------------
void Files::MusicOn()
{
	for (size_t i = 1; i < 5; i++)
		m_sound[i].setVolume(100);

	m_sound[0].setVolume(50);
}
//--------------------------------------------------------------------------------------------
void Files::PlayBackground()
{
	m_sound[0].setLoop(true);
	m_sound[0].play();

}
//--------------------------------------------------------------------------------------------
void Files::PlayEat()
{
	m_sound[1].play();
}
//--------------------------------------------------------------------------------------------
void Files::PlayKill()
{
	m_sound[2].play();
}
//--------------------------------------------------------------------------------------------
void Files::PlayClick()
{
	m_sound[3].play();
}
//--------------------------------------------------------------------------------------------
void Files::PlayChamp()
{
	m_sound[4].setLoop(true);
	m_sound[4].play();
}
//--------------------------------------------------------------------------------------------
void Files::stopChamp()
{
	m_sound[4].pause();
}
//--------------------------------------------------------------------------------------------
void Files::stopBackground()
{
	m_sound[0].pause();
}