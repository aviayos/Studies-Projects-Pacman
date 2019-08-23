#pragma once
#include "Ghost.h"

using std::vector;

class SmartGhost : public Ghost//deriving from ghost
{
public:
	SmartGhost(sf::Vector2i place, char type);
	sf::Vector2f move( vector<vector <sf::Vector3i>> & vec, float playerMovment);
	Direction_t getWayFromBfs(const vector<vector <sf::Vector3i>> & vec);
	Direction_t findDirection(const sf::Vector2i & start, const sf::Vector2i & destination);
	virtual ~SmartGhost() {};
};

