#pragma once
#include "Files.h"
#include "Level.h"
class StatusBar
{
public://class represent the status bar of the game(live,score,level)
	StatusBar(sf::Vector2i board_size);
	void draw(sf::RenderWindow & window, int, int, int);

private:
	sf::Text m_status;
	sf::Font m_font;
	sf::Vector2i m_factor;//help us to addjust the size of the board to the character size and status place
	std::string m_text;
};

