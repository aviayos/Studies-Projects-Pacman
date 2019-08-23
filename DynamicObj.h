#pragma once
#include "Object.h"

const float REGULAR_SPEED = 100;

enum Color_t { Red_t, Green_t, Blue_t };//enums of the colors, help us changing pics 
enum Direction_t { Right_t, Down_t, Left_t, Up_t, Stop_t };//directions of the dynamic characters
enum Pos_t { Step1_t, Step2_t };//tow poses of the character

class DynamicObj : public Object//deriving from Object
{
public:
	DynamicObj();
	virtual void draw(sf::RenderWindow&, float) = 0;
	void setNewPlace(sf::Vector2f);
	Direction_t getDir()const;
	bool isCloseEnough(sf::Vector2f other);
	sf::Vector2f getPlace()const;
	void setDir(Direction_t);
	virtual ~DynamicObj();


protected:
	bool isMoveAble();
	bool floatEqual(float, float)const;


	sf::Vector2f m_previous_place;
	sf::Vector2f m_place;
	Direction_t m_dir;
	Pos_t m_step;
};

