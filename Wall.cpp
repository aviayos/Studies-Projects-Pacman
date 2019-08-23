#include "Wall.h"
#include "Pacman.h"
#include "Ghost.h"


//-------------------------------------------------------------------------------------------
//ctor of wall, get the color and the place on board
Wall::Wall(sf::Color color, sf::Vector2i place)
{
	m_place.x = (float)place.x * SHAPE_SIZE + CENTER;
	m_place.y = (float)place.y * SHAPE_SIZE + CENTER;
	m_color = color;
	sf::Texture* texture = Files::instance().getPic(2);
	m_icon.setTexture(*texture);
	m_icon.setOrigin(CENTER, CENTER);
}
//-------------------------------------------------------------------------------------------
void Wall::draw(sf::RenderWindow &window)
{
	m_icon.setTextureRect(sf::IntRect(0, 0, 32, 32));
	m_icon.setPosition(m_place.x, m_place.y);
	m_icon.setColor(m_color);
	window.draw(m_icon);
}
//-------------------------------------------------------------------------------------------
								//DOUBLE DISPATCH//
//------------------------------------------------------------------------------------------
//colllision with unknown object
void Wall::collide(Object * other, Level & level)
{
	other->collide(this, level);
}
//-------------------------------------------------------------------------------------------
//collision with pacman, forwarding to Pacman collide
void Wall::collide(Pacman* other, Level & level)
{
	other->collide(this, level);
}
//-------------------------------------------------------------------------------------------
//collision with pacman, forwarding to Ghost collide
void Wall::collide(Ghost * other, Level & level)
{
	other->collide(this, level);
}
