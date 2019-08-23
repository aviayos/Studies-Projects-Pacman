#pragma once
#include "StaticObj.h"
class Wall : public StaticObj
{
public:
	Wall(sf::Color color, sf::Vector2i place);
	void draw(sf::RenderWindow&);
	virtual void collide(Object* other, Level& level);
	virtual void collide(Pacman* other, Level& level);
	virtual void collide(Ghost* other, Level& level);
	virtual void collide(Cookie* other, Level& level) {};
	virtual void collide(Wall* other, Level& level) {};
	virtual ~Wall() {};

};

