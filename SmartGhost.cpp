#include "SmartGhost.h"


//--------------------------------------------------------------------------------------
//ctor of smart ghost
SmartGhost::SmartGhost(sf::Vector2i place, char type)
{
	m_place.x = (float)place.x * SHAPE_SIZE + CENTER;
	m_place.y = (float)place.y * SHAPE_SIZE + CENTER;
	switch (type)
	{
	case '%':
		m_color = Red_t;
		break;
	case 'T':
		m_color = Green_t;
		break;
	case 'G':
		m_color = Blue_t;
		break;
	}
}
//--------------------------------------------------------------------------------------------
//mehtod of the smartGhost, get the bfs tree and float. return the new place
sf::Vector2f SmartGhost::move( std::vector<std::vector <sf::Vector3i>> & vec,
								float playerMovment)
{
	m_previous_place = m_place;
	m_changeDir += playerMovment;

	if (m_changeDir >= 1.f && isMoveAble())
	{
		m_dir = getWayFromBfs(vec);// activate bfs 
	}

	switch (m_dir)//move the smart with the direction
	{
	case Right_t: m_place.x += playerMovment * REGULAR_SPEED;
		m_dir = Right_t;
		break;
	case Down_t: m_place.y += playerMovment * REGULAR_SPEED;
		m_dir = Down_t;
		break;
	case Left_t: m_place.x += playerMovment * -REGULAR_SPEED;
		m_dir = Left_t;
		break;
	case Up_t: m_place.y += playerMovment * -REGULAR_SPEED;
		m_dir = Up_t;
		break;
	}

	return m_place;
}
//----------------------------------------------------------------------------------------
//method get bfs tree and extract the direction 
Direction_t SmartGhost::getWayFromBfs(const std::vector<std::vector<sf::Vector3i>>& Tree)
{
	sf::Vector2i my_vertex = { (int)(m_place.x / SHAPE_SIZE), (int)(m_place.y / SHAPE_SIZE) };

	return findDirection(my_vertex, sf::Vector2i(Tree[my_vertex.x][my_vertex.y].x,
		Tree[my_vertex.x][my_vertex.y].y));

}
//-----------------------------------------------------------------------------------------
//get the cuuernt place as vertex and the next place vertex (the one who "reveald" me), 
//return the direction
Direction_t SmartGhost::findDirection(const sf::Vector2i &start,
	const sf::Vector2i &destination)
{
	if (start.x > destination.x)
		return Left_t;

	if (start.x < destination.x)
		return Right_t;

	if (start.y > destination.y)
		return Up_t;

	if (start.y < destination.y)
		return Down_t;

	return Stop_t;
}

