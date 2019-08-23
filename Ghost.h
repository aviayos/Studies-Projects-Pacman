#pragma once
#include "DynamicObj.h"
#include <vector>

using std::vector;

class Ghost : public DynamicObj//deriving from dynamic obj
{
public:
	Ghost();
	virtual sf::Vector2f move(vector<vector <sf::Vector3i>> & vec, float) = 0;
	void draw(sf::RenderWindow&, float);
	virtual void collide(Object* other, Level& level);
	virtual void collide(Pacman* other, Level& level);
	virtual void collide(Ghost* other, Level& level) {};
	virtual void collide(Cookie* other, Level& level) {};
	virtual void collide(Wall* other, Level& level);
	virtual ~Ghost() {};//virtual dtor
protected:
	Color_t m_color;
	float m_changeDir;

};

