#include "RandomGhost.h"
#include <time.h>


//--------------------------------------------------------------------------------------------
//ctor get the place on board and the char type
RandomGhost::RandomGhost(sf::Vector2i place, char type)
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
//------------------------------------------------------------------------------------------------
//movement method of the random
sf::Vector2f RandomGhost::move( std::vector<std::vector <sf::Vector3i>> & vec, 
								float playerMovment)
{
	m_previous_place = m_place;
	int choice = 2;
	m_changeDir += playerMovment;//sum the floats 
	sf::Vector2f pacPlace = getPacPlaceOnTree(vec);

	if (m_changeDir >= 1.f && isMoveAble())
	{
		choice = rand() % 2;
		m_changeDir = 0;
	}

	switch (choice)
	{
	case 0:// try to get pacman x value
		if (pacPlace.x > m_place.x)
		{
			m_place.x += playerMovment * REGULAR_SPEED;
			m_dir = Right_t;
		}
		else {
			m_place.x += playerMovment * -REGULAR_SPEED;
			m_dir = Left_t;
		}
		break;
	case 1: //try to get pacman y value
		if (pacPlace.y > m_place.y)
		{
			m_place.y += playerMovment * REGULAR_SPEED;
			m_dir = Down_t;
		}
		else {
			m_place.y += playerMovment * -REGULAR_SPEED;
			m_dir = Up_t;
		}
		break;
	case 2://go on same direction
		switch (m_dir)
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
		break;

	}
	return m_place;
}
//--------------------------------------------------------------------------------------------
//method check the pac place on tree
sf::Vector2f RandomGhost::getPacPlaceOnTree(const std::vector<std::vector<sf::Vector3i>>& vec)
{
	sf::Vector2f pac_place{ -1,-1 };
	for (size_t i = 0; i < vec.size(); i++)
	{
		for (size_t j = 0; j < vec[i].size(); j++)
		{
			if (vec[i][j].x == -1 && vec[i][j].y == -1 && vec[i][j].z == 0)//the source vertex(pacman)
			{
				pac_place.x = j * SHAPE_SIZE + CENTER;
				pac_place.y = i * SHAPE_SIZE + CENTER;
				return pac_place;
			}
		}
	}
	return pac_place;
}




