#pragma once
#include <SFML\Graphics.hpp>
#include "Files.h"

class Level;
class Ghost;
class Cookie;
class Wall;
class Pacman;

const float HEIGHT = 32;
const float WIDTH = 32;
const float CENTER = 32 / 2;
const float SHAPE_SIZE = 32;

class Object//main abstract class, derived from all characters objects
{
public:
	Object();
	virtual void collide(Object* other, Level& level) = 0;
	virtual void collide(Pacman* other, Level& level) = 0;
	virtual void collide(Ghost* other, Level& level) = 0;
	virtual void collide(Cookie* other, Level& level) = 0;
	virtual void collide(Wall* other, Level& level) = 0;
	virtual ~Object() {};

protected:
	sf::Vector2f m_place;
	sf::Sprite m_icon;

};

