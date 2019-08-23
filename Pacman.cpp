#include "Pacman.h"
#include "Ghost.h"
#include "Wall.h"
#include "Cookie.h"
#include "Level.h"


//ctor of pacman , get the char, and the place on board
Pacman::Pacman(char obj, sf::Vector2i place)
{
	m_dir = Stop_t;//default direction
	m_speed = REGULAR_SPEED;
	m_place.x = (float)place.x * SHAPE_SIZE + CENTER;//convert the acctual place on screen
	m_place.y = (float)place.y * SHAPE_SIZE + CENTER;
	m_step = Step1_t;
	m_lives = 15;//initiate lives and score
	m_score = 0;
	m_SpecialAte = false;

	switch (obj)
	{
	case '@':
		m_Color = Red_t;//set the color
		break;
	case 'W':
		m_Color = Green_t;
		break;
	case 'S':
		m_Color = Blue_t;
		break;
	}
	sf::Texture* texture = Files::instance().getPic(0);
	m_icon.setTexture(*texture);
	m_icon.setOrigin(CENTER, CENTER);
}
//--------------------------------------------------------------------------------------
//method moving the player , get direction from the user 
sf::Vector2f Pacman::move(Direction_t step, float time)
{
	m_previous_place = m_place;

	if (isMoveAble()) //check if the pacman can change his direction(middle of the tile)
		m_dir = step;
	

	switch (m_dir)
	{
	case Right_t:m_place.x += time * m_speed;
		break;
	case Down_t:m_place.y += time * m_speed;
		break;
	case Left_t:m_place.x += time * -m_speed;
		break;
	case Up_t: m_place.y += time * -m_speed;
		break;
	case Stop_t: break;
	}
	return m_place;
}
//------------------------------------------------------------------------------------------
//method drawing the pacman
void Pacman::draw(sf::RenderWindow &window, float change_step)
{
	static float change_pic = 0;
	change_pic += change_step;
	if (change_pic >= 2.f) {//change the pose of the pacman
		m_step == Step1_t ? m_step = Step2_t : m_step = Step1_t;
		change_pic = 0;
	}                       //change the pose and the sprite direction
	m_icon.setTextureRect(sf::IntRect((m_step + m_Color * 2) * 32, m_dir * 32, 32, 32));
	m_icon.setPosition(m_place);
	window.draw(m_icon);
}
//-------------------------------------------------------------------------------------------
int Pacman::getLives() const
{
	return m_lives;
}
//-------------------------------------------------------------------------------------------
int Pacman::getScore() const
{
	return m_score;
}

//-------------------------------------------------------------------------------------------
								//DOUBLE DISPATCH//
//------------------------------------------------------------------------------------------
//collision with unknown object
void Pacman::collide(Object * other, Level & level)
{
	other->collide(this, level);
}
//-------------------------------------------------------------------------------------------
//collision with ghost
void Pacman::collide(Ghost * other, Level & level)
{
	m_lives--;
	Files::instance().PlayKill();
}
//-------------------------------------------------------------------------------------------
//pacman collision with cookie
void Pacman::collide(Cookie * other, Level & level)
{
	int i = (int)(other->getPlace().x / 32);//GET THE PLACE without the remainder
	int j = (int)(other->getPlace().y / 32);//

	float pos_x = (float)((32 * i) + 16);//
	float pos_y = (float)((32 * j) + 16);//

	if (std::abs(m_place.x - pos_x) < 8 && std::abs(m_place.y - pos_y) < 8)//half of shape radius
	{
		Files::instance().PlayEat();
		m_speed += (float)other->get_speed(m_speed);//increase/decrease speed
		m_score += (level.getNumghost() + 1) * 2;

		if (level.AllCookiesAte()) {//adding bonus for level up
			m_score += (level.getNumghost() + 1) * 50;
		}

		if (other->getType() == Health || other->getType() == Poison)
		{
			m_SpecialAte = true;
			if (other->getType() == Health)
				m_score += (level.getNumghost() + 3) * 2;
			else
				m_score -= level.getNumghost() * 2;
		}
		else//specials not included in the total cookies
			level.decCookie();

		level.clearObj(i, j);
	}
}
//-------------------------------------------------------------------------------------------
//pacman collision with the Wall
void Pacman::collide(Wall *other, Level & level)
{
	m_place.x = (int)(m_previous_place.x / SHAPE_SIZE)* SHAPE_SIZE + CENTER;
	m_place.y = (int)(m_previous_place.y / SHAPE_SIZE)* SHAPE_SIZE + CENTER;
}
//-------------------------------------------------------------------------------------------
//change player color when exceeding to the next level
void Pacman::ChangePlayerColor(char pac_color)
{
	switch (pac_color)
	{
	case '@': m_Color = Red_t;
		break;
	case 'W': m_Color = Green_t;
		break;
	case 'S': m_Color = Blue_t;
		break;
	}

}
//-------------------------------------------------------------------------------------------
//check if we ate special cookie
bool Pacman::ateSpecial()
{
	return m_SpecialAte;
}
//-------------------------------------------------------------------------------------------
//method counting the new speed by get the cookie type
void Pacman::CountSpeed(float time, int cookieType)
{
	static float time_to_return = 0;
	time_to_return += time;

	if (cookieType == 0 && time_to_return >= 160.f)//health
	{
		m_speed = REGULAR_SPEED;
		time_to_return = 0;
		m_SpecialAte = false;
	}

	else if (cookieType == 1 && time_to_return >= 70.f)//poison
	{
		m_speed = REGULAR_SPEED;
		time_to_return = 0;
		m_SpecialAte = false;
	}


}
//-------------------------------------------------------------------------------------------
//BFS method, pacman make the shortest way for all the verteices on board
vector<vector<sf::Vector3i>> Pacman::BFS_fromMe(sf::Vector2i &start,
	const vector<vector<std::unique_ptr<StaticObj>>> &board)
{
	//start - the source, pacman place
	vector<vector<sf::Vector3i>> BFS_Tree;
	sf::Vector2i current_vertex;
	std::queue<sf::Vector2i> vertices_queue;

	BFS_Tree.assign(board.size(), std::vector<sf::Vector3i>(board[0].size(),
		sf::Vector3i(-1, -1, INT_MAX)));//intiate vertices of the tree
	BFS_Tree[start.x][start.y].z = 0;//initiate the distance of the source
	vertices_queue.push(start);//push to the queue the source vertex

	while (!vertices_queue.empty())
	{
		current_vertex = vertices_queue.front();//current=the first in the queue
		vertices_queue.pop();

		std::vector<sf::Vector2i> neighboors = getMyNeighboor(current_vertex, board);
		//get the current vertex neighbors

		for (size_t i = 0; i < neighboors.size(); i++)
		{
			//next vertex is one of my neighboors(differ from me in one coordinate(x val or y val))
			sf::Vector2i next_vertex = neighboors[i];
			//next vertex is not the sourch && no one "touched" him than update the tree
			if ((next_vertex.y != start.y || next_vertex.x != start.x) &&
				BFS_Tree[next_vertex.x][next_vertex.y].z == INT_MAX)
			{
				vertices_queue.push(next_vertex);//push him to the back of the queue
				BFS_Tree[next_vertex.x][next_vertex.y].x = current_vertex.x;//set "his father" x value
				BFS_Tree[next_vertex.x][next_vertex.y].y = current_vertex.y;//set "his father" y value
				BFS_Tree[next_vertex.x][next_vertex.y].z = BFS_Tree[current_vertex.x][current_vertex.y].z + 1;
				//set his distance to father distance+1
			}
		}
	}

	return BFS_Tree;
}

//-------------------------------------------------------------------------------------------
//method return the vertex neigboors as vector of vector2i
vector<sf::Vector2i> Pacman::getMyNeighboor(sf::Vector2i &center,
	const vector<vector<std::unique_ptr<StaticObj>>> &board)
{
	vector<sf::Vector2i> shifts = { { 1,0 },{ -1,0 },{ 0,1 },{ 0,-1 } };
	//set vector to hold the result
	vector<sf::Vector2i> neighbors;
	sf::Vector2i next;

	for (int i = 0; i < 4; i++)
	{
		next = center + shifts[i];
		//if the neighboor is not Wall and exist in board sizes
		if (is_InBoardBounds(next, board) && !dynamic_cast<Wall*>(board[next.x][next.y].get()))
			neighbors.push_back(next);

	}
	return neighbors;

}
//-------------------------------------------------------------------------------------------
//method check if the vertex sent is in board sizes
bool Pacman::is_InBoardBounds(sf::Vector2i new_place,
	const vector<vector<std::unique_ptr<StaticObj>>> &board)
{
	return !(new_place.x < 0 || new_place.y < 0 || new_place.y >= (int)board[0].size() ||
		new_place.x >= (int)board.size());
}
//-------------------------------------------------------------------------------------------
//virtual dtor
Pacman::~Pacman()
{
}
