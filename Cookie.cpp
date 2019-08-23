#include "Cookie.h"
#include "Level.h"
#include "Pacman.h"


//ctor , get color,type and place on board
Cookie::Cookie(sf::Color color, sf::Vector2i place, Type_t type)
{
	m_color = color;
	m_place.x = place.x * SHAPE_SIZE + CENTER;
	m_place.y = place.y * SHAPE_SIZE + CENTER;
	m_type = type;
	sf::Texture* texture = Files::instance().getPic(3);
	m_icon.setTexture(*texture);
	m_icon.setOrigin(CENTER, CENTER);

}
//------------------------------------------------------------------------------------------------
void Cookie::draw(sf::RenderWindow &window)
{

	m_icon.setTextureRect(sf::IntRect(0, (int)(m_type * SHAPE_SIZE), (int)SHAPE_SIZE, (int)SHAPE_SIZE));
	m_icon.setPosition(m_place.x, m_place.y);

	if (m_type == Regular)
		m_icon.setColor(m_color);
	window.draw(m_icon);
}
//------------------------------------------------------------------------------------------------
//calculate the new speed by the cookie type
double Cookie::get_speed(double speed) const
{
	switch (m_type)
	{
	case Health:
		return speed / 5;;
	case Poison:
		return -(speed / 10);
	}
	return 0.0; //if regular
}
//------------------------------------------------------------------------------------------------
Type_t Cookie::getType() const
{
	return m_type;
}
//-------------------------------------------------------------------------------------------
									//DOUBLE DISPATCH//
//------------------------------------------------------------------------------------------
void Cookie::collide(Object * other, Level & level)
{
	other->collide(this, level);
}
//------------------------------------------------------------------------------------------------

void Cookie::collide(Pacman * other, Level & level)
{
	other->collide(this, level);

}
//------------------------------------------------------------------------------------------------
void Cookie::collide(Ghost * other, Level & level)
{
	other->collide(this, level);
}
