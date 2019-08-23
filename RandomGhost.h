#pragma once
#include "Ghost.h"

using std::vector;

class RandomGhost : public Ghost//deriving from ghost
{
public:
	RandomGhost(sf::Vector2i place, char type);
	sf::Vector2f move( vector<vector <sf::Vector3i>> & vec, float playerMovment);
	sf::Vector2f getPacPlaceOnTree(const vector<vector <sf::Vector3i>> & vec);
	virtual ~RandomGhost() {};
};

