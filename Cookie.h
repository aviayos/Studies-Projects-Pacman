#pragma once
#include "StaticObj.h"

enum Type_t { Health, Regular, Poison };//the types of the cookie

class Cookie : public StaticObj
{
public:
	Cookie(sf::Color color, sf::Vector2i place, Type_t type);
	void draw(sf::RenderWindow&);
	double get_speed(double speed)const;
	Type_t getType()const;
	virtual void collide(Object* other, Level& level);
	virtual void collide(Pacman* other, Level& level);
	virtual void collide(Ghost* other, Level& level);
	virtual void collide(Cookie* other, Level& level) {};
	virtual void collide(Wall* other, Level& level) {};
	virtual ~Cookie() {};
private:
	Type_t m_type;

};

