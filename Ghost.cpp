#include "Ghost.h"
#include "Pacman.h"


//-------------------------------------------------------------------------------------------------
Ghost::Ghost()
{
	sf::Texture* texture = Files::instance().getPic(1);
	m_icon.setTexture(*texture);
	m_icon.setOrigin(CENTER, CENTER);
	m_dir = Right_t;
	m_step = Step1_t;
	m_color = Red_t;
	m_changeDir = 0;
}
//-------------------------------------------------------------------------------------------------
void Ghost::draw(sf::RenderWindow &window, float change_step)
{
	static float change_pic = 0;
	change_pic += change_step;
	if (change_pic >= 3.f) {
		m_step == Step1_t ? m_step = Step2_t : m_step = Step1_t;
		change_pic = 0;
	}
	m_icon.setTextureRect(sf::IntRect(((m_color * 2) + m_step)*(int)SHAPE_SIZE, m_dir * (int)SHAPE_SIZE, (int)SHAPE_SIZE, (int)SHAPE_SIZE));
	m_icon.setPosition(m_place.x, m_place.y);
	window.draw(m_icon);
}
//-------------------------------------------------------------------------------------------------
								//DOUBLE DISPATCH//
//-------------------------------------------------------------------------------------------------
//collision with unknown object
void Ghost::collide(Object * other, Level & level)
{
	other->collide(this, level);

}
//-------------------------------------------------------------------------------------------------
//collision with Pacman, forwarding to pacman collision with ghost
void Ghost::collide(Pacman * other, Level & level)
{
	other->collide(this, level);
}
//-------------------------------------------------------------------------------------------------
//collision with Wall
void Ghost::collide(Wall * other, Level & level)
{
	static int change = 0;//count the time of collision with wall
	change++;
	m_place = m_previous_place;

	if (change == 3)
	{
		change = 0;
		switch (m_dir)
		{
		case Right_t: m_dir = Down_t;
			break;
		case Left_t: m_dir = Up_t;
			break;
		case Down_t: m_dir = Left_t;
			break;
		case Up_t: m_dir = Right_t;
			break;
		}
	}
}

