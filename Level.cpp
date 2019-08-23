#include "Level.h"



Level::Level()
{
}
//------------------------------------------------------------------------------------------
//main methods, read new level from txt files and create new board
void Level::LoadNewLvL()
{
	m_num_level = 0;
	m_num_level++;
	string num = std::to_string(m_num_level);
	string level{ "Levels/Level" };
	ifstream file;

	num.append(".txt");//append the level number and .txt ending
	level.append(num);//append and create "Level<#num>.txt" string

	file.open(level);
	char obj;

	if (!file.is_open())
		std::cerr << "level not open\n";

	file >> m_boardSize.x >> m_boardSize.y;

	resizeBoard();//resize new board size

	for (int i = 0; i < m_boardSize.x; i++)
	{
		file.get();
		for (int j = 0; j < m_boardSize.y; j++)
		{
			obj = file.get();
			setObj(obj, i, j);
		}
	}
	file.close();
}
//------------------------------------------------------------------------------------------
void Level::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < m_boardSize.x; i++)
	{
		for (int j = 0; j < m_boardSize.y; j++)
		{
			if (m_board[i][j] != nullptr)//if the cell is not empty
				m_board[i][j].get()->draw(window);

		}
	}
}
//------------------------------------------------------------------------------------------
//return if all cookies ate by the player
bool Level::AllCookiesAte()
{
	if (m_numCookies == 0) {
		SpecialsRemove(100.f);//remove all the specials if exist
		return true;
	}
	return false;
}
//------------------------------------------------------------------------------------------
int Level::getNumghost() const
{
	return m_RivalsDetails.size();
}
//------------------------------------------------------------------------------------------
sf::Vector2i Level::getBoardSize()const
{
	return m_boardSize;
}
//------------------------------------------------------------------------------------------
//return the ghost start details(char,place) by index
Char_Details Level::getGhostData(int index) const
{
	return m_RivalsDetails[index];
}
//------------------------------------------------------------------------------------------
//return the pacman start details(char,place) 
Char_Details Level::getPacData() const
{
	return m_pacDetails;
}

//------------------------------------------------------------------------------------------
//return the object placed in the radius of the object direction
StaticObj* Level::getObject(sf::Vector2f place, Direction_t direction)const
{
	int i, j;

	switch (direction)
	{
	case Up_t: place.y -= 16.f;//sum the radius by the direction
		break;
	case Down_t: place.y += 16.f;//
		break;
	case Right_t: place.x += 16.f;//
		break;
	case Left_t: place.x -= 16.f;//
		break;
	}
	i = (int)(place.x / SHAPE_SIZE);//convert to the board tile
	j = (int)(place.y / SHAPE_SIZE);

	i >= m_boardSize.x ? i = i % m_boardSize.x : i;
	j >= m_boardSize.y ? j = j % m_boardSize.y : j;

	return m_board[i][j].get();
}
//------------------------------------------------------------------------------------------
void Level::clearObj(int i, int j)
{
	m_board[i][j] = nullptr;
}
//------------------------------------------------------------------------------------------
void Level::decCookie()
{
	m_numCookies--;
}
//------------------------------------------------------------------------------------------
int Level::getLevel()const
{
	return m_num_level;
}
//------------------------------------------------------------------------------------------
//method create new object
void Level::setObj(char obj, int i, int j)
{
	sf::Vector2i place{ i,j };
	Char_Details temp;

	switch (obj)
	{
	case '@':m_pacDetails.m_StartPlace = place;//save the pacman details
		m_pacDetails.type = obj;
		break;
	case 'W':m_pacDetails.m_StartPlace = place;//
		m_pacDetails.type = obj;
		break;

	case 'S':m_pacDetails.m_StartPlace = place;//
		m_pacDetails.type = obj;
		break;

	case '%':temp.m_StartPlace = place;//save the ghost details
		temp.type = obj;
		m_RivalsDetails.push_back(temp);
		break;

	case 'T':temp.m_StartPlace = place;//
		temp.type = obj;
		m_RivalsDetails.push_back(temp);
		break;

	case 'G':temp.m_StartPlace = place;//
		temp.type = obj;
		m_RivalsDetails.push_back(temp);
		break;

	case '#':m_board[i][j] = make_unique <Wall>(sf::Color::Red, place);//create Wall
		break;
	case 'E':m_board[i][j] = make_unique <Wall>(sf::Color::Green, place);//
		break;
	case 'D':m_board[i][j] = make_unique <Wall>(sf::Color::Blue, place);//
		break;
	case '*':m_board[i][j] = make_unique <Cookie>(sf::Color::Red, place, Regular);//create Cookie
		m_numCookies++;
		break;
	case 'I':m_board[i][j] = make_unique <Cookie>(sf::Color::Green, place, Regular);//
		m_numCookies++;
		break;
	case 'K':m_board[i][j] = make_unique <Cookie>(sf::Color::Blue, place, Regular);//
		m_numCookies++;
		break;
	}
}
//------------------------------------------------------------------------------------------
//check if the place on board is nullptr 
bool Level::freeSpace(int i, int j)
{
	return (m_board[i][j] == nullptr);
}
//------------------------------------------------------------------------------------------
//reisze the board and initiate with nullptr
void Level::resizeBoard()
{
	m_board.resize(m_boardSize.x);

	for (int i = 0; i < m_boardSize.x; i++)
	{
		m_board[i].resize(m_boardSize.y);
		for (int j = 0; j < m_boardSize.y; j++)
		{
			m_board[i][j] = nullptr;
		}
	}

}
//------------------------------------------------------------------------------------------
//empty the ghost details while level up
void Level::emptyVec()
{
	int size = m_RivalsDetails.size();
	for (int i = 0; i < size; i++)
		m_RivalsDetails.pop_back();
}
//------------------------------------------------------------------------------------------
//set specials cookies on empty place on board, by the type
void Level::setSpecialCookie(int type)
{
	SpecialCookie temp;
	int i = rand() % m_boardSize.x;
	int j = rand() % m_boardSize.y;
	sf::Vector2i place;

	while (!freeSpace(i, j))
	{
		i = rand() % m_boardSize.x;
		j = rand() % m_boardSize.y;
	}

	place.x = i;
	place.y = j;

	switch (type)
	{
	case 0: m_board[i][j] = make_unique <Cookie>(sf::Color::Red, place, Health);
		temp.is_create = true;
		temp.m_Place = { i,j };
		temp.type = Health;
		m_specials.push_back(temp);
		break;

	case 1:
		m_board[i][j] = make_unique <Cookie>(sf::Color::Red, place, Poison);
		temp.is_create = true;
		temp.m_Place = { i,j };
		temp.type = Poison;
		m_specials.push_back(temp);
		break;
	}
}
//------------------------------------------------------------------------------------------
//check if there are specials cookies on boaed
bool Level::Is_SpecialCreated()
{
	for (size_t i = 0; i < m_specials.size(); i++)
	{
		if (m_specials[i].is_create)
			return true;
	}
	return false;
}
//------------------------------------------------------------------------------------------
//remove the special cookies if the time is passed
void Level::SpecialsRemove(float time)
{
	for (size_t i = 0; i < m_specials.size(); i++)
	{
		if (m_specials[i].is_create)//adding the time to clear
			m_specials[i].time_to_clear += time;

		if (m_specials[i].time_to_clear >= 120.f)//if we reach the limit - remove
		{
			m_board[m_specials[i].m_Place.x][m_specials[i].m_Place.y] = nullptr;
			m_specials.erase(m_specials.begin() + i);
			i--;
		}
	}
}
//------------------------------------------------------------------------------------------
const vector<vector<std::unique_ptr<StaticObj>>> & Level::getBoard()
{
	return m_board;
}



