#include "DynamicObj.h"


//--------------------------------------------------------------------------------------
DynamicObj::DynamicObj()
{
}
//--------------------------------------------------------------------------------------
void DynamicObj::setNewPlace(sf::Vector2f new_place)
{
	m_place = new_place;
}
//--------------------------------------------------------------------------------------
Direction_t DynamicObj::getDir() const
{
	return m_dir;
}
//--------------------------------------------------------------------------------------
//method check if the dynamic object can change his direction(in the midlle of the tile)
bool DynamicObj::isMoveAble()
{
	int i = (int)((m_place.x) / WIDTH);
	int j = (int)((m_place.y) / HEIGHT);

	//check approximation
	if (floatEqual((i * SHAPE_SIZE + CENTER), m_place.x) && floatEqual((j * SHAPE_SIZE + CENTER), m_place.y))
	{
		m_place.x = i * SHAPE_SIZE + CENTER;
		m_place.y = j * SHAPE_SIZE + CENTER;
		return true;
	}
	return false;
}
//--------------------------------------------------------------------------------------
//method check range of floats, in approximation of 4
bool DynamicObj::floatEqual(float a, float b) const
{
	if (abs(a - b) <= 4.f)//μαγεχ
		return true;

	return false;
}
//--------------------------------------------------------------------------------------
//method check if the pacman and the ghost close to each other(the radius of the shape)
bool DynamicObj::isCloseEnough(sf::Vector2f other)
{
	return (abs(m_previous_place.x - other.x) <= 16.f && 
			abs(m_previous_place.y - other.y) <= 16.f);
}
//--------------------------------------------------------------------------------------
sf::Vector2f DynamicObj::getPlace() const
{
	return m_place;
}
//--------------------------------------------------------------------------------------
void DynamicObj::setDir(Direction_t new_dir)
{
	m_dir = new_dir;
}
//--------------------------------------------------------------------------------------
DynamicObj::~DynamicObj()
{
}
