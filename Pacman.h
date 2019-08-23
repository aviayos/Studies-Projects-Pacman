#pragma once
#include "DynamicObj.h"
#include <queue> 
#include <memory> 

class Ghost;
class Cookie;
class Wall;
class StaticObj;
using std::vector;

class Pacman : public DynamicObj
{
public:
	Pacman(char obj, sf::Vector2i place);
	sf::Vector2f move(Direction_t, float);
	void draw(sf::RenderWindow&, float);
	int getLives()const;
	int getScore()const;
	void ChangePlayerColor(char pac_data);
	bool ateSpecial();
	void CountSpeed(float, int);
	//double dispatch methods
	virtual void collide(Object* other, Level& level);
	virtual void collide(Ghost* other, Level& level);
	virtual void collide(Cookie* other, Level& level);
	virtual void collide(Wall* other, Level& level);
	virtual void collide(Pacman* other, Level& level) {};
	//bfs
	vector<vector <sf::Vector3i> > BFS_fromMe(sf::Vector2i &start, 
		const vector<vector<std::unique_ptr<StaticObj>>> & board);
	bool is_InBoardBounds(sf::Vector2i new_place, 
		const vector<vector<std::unique_ptr<StaticObj>>> &board);
	
	virtual ~Pacman();


private:
	float m_speed;
	int m_lives;
	int m_score;
	Color_t m_Color;
	bool m_SpecialAte;//help us to know if we ate special cookie
	vector<sf::Vector2i>getMyNeighboor(sf::Vector2i &center,
		const vector<vector<std::unique_ptr<StaticObj>>> &board);
};

