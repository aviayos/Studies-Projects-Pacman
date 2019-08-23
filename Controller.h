#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include "Pacman.h"
#include "Level.h"
#include "Menu.h"
#include "SmartGhost.h" 
#include "RandomGhost.h"
#include "StatusBar.h"

const float TIME_TO_MOVE = 0.05f;
const float STATUS_SIZE = 80.f;

class Controller
{
public:
	Controller();
	void run();
	int get_score();

private:
	//members
	Level m_level;
	std::unique_ptr <Pacman> m_player;
	vector<std::unique_ptr<Ghost>> m_rivals;
	//functions
	void set_rivals();
	void move(Direction_t&, float);
	void draw(sf::RenderWindow&, float, StatusBar &);
	void teleport(sf::Vector2f& new_place, DynamicObj* player);
	void checkCollision(DynamicObj*, Direction_t);
	void getEvent(sf::RenderWindow& window, sf::Event& user_event, Direction_t& way, sf::Clock& clock);
	void clearRivals();
	void StartPlaces();
	void setPlayer(Direction_t &way);
	void popCookie(float time);
	void PauseGame(sf::RenderWindow& window);



};

