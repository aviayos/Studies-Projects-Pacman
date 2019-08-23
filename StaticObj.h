#pragma once
#include "Object.h"

class StaticObj : public Object//static object class(cookie,wall)
{
public:
	StaticObj();
	virtual void draw(sf::RenderWindow&) = 0;
	sf::Vector2f getPlace()const;
	virtual ~StaticObj();
protected:
	sf::Color m_color;
};

