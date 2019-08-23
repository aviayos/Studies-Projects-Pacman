#include "StatusBar.h"


//ctor get the board size
StatusBar::StatusBar(sf::Vector2i board_size)
{
	m_factor = board_size;
	m_font = *(Files::instance().getFont());
	m_status.setFont(m_font);
	m_status.setPosition(20.f, m_factor.y * SHAPE_SIZE + 5.f);

}
//draw the status, get from controller the current lives,score and level
void StatusBar::draw(sf::RenderWindow & window, int Lives, int Score, int Level)
{
	std::string status;
	
	status = "Lives: " + std::to_string(Lives) + 
		"  Score: " + std::to_string(Score) +
		"  Level: " + std::to_string(Level);
	
	m_status.setString(status);
	m_status.setCharacterSize((int)(m_factor.x * SHAPE_SIZE) / status.size() * 2);
	window.draw(m_status);
}
