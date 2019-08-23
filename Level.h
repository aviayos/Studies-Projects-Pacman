#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include <SFML\Graphics.hpp>
#include "Wall.h"
#include "Ghost.h"
#include "Cookie.h"
#include "Pacman.h"
#include <vector>
#include <memory> 

using std::vector;
using std::ifstream;
using std::string;
using std::make_unique;

const float STATUS_BAR = 100;

struct Char_Details {//hold the dynamic characters start place
	sf::Vector2i m_StartPlace;
	char type;
};
struct SpecialCookie {//hold the special cookies details
	sf::Vector2i m_Place;
	Type_t type;//health/poison
	float time_to_clear = 0;//the time to clear the cookie
	bool is_create = false;
};

class Level//class hold the characters details and the board, loading levels and commuincate with controller
{
public:
	Level();
	void LoadNewLvL();
	void draw(sf::RenderWindow&);
	bool AllCookiesAte();
	int getNumghost()const;
	sf::Vector2i getBoardSize()const;
	Char_Details getGhostData(int index)const;
	Char_Details getPacData()const;
	StaticObj* getObject(sf::Vector2f place, Direction_t direction) const;
	void clearObj(int i, int j);
	void decCookie();
	int getLevel()const;
	void emptyVec();
	void setSpecialCookie(int);
	bool Is_SpecialCreated();
	void SpecialsRemove(float time);
	const vector<vector<std::unique_ptr<StaticObj>>> & getBoard();

private:
	//members
	vector<vector<std::unique_ptr<StaticObj>>> m_board;
	sf::Vector2i m_boardSize;
	vector <Char_Details> m_RivalsDetails;
	Char_Details m_pacDetails;
	int m_numCookies = 0;
	int m_num_level = 0;
	vector <SpecialCookie> m_specials;
	//methods
	bool freeSpace(int i, int j);
	void resizeBoard();
	void setObj(char, int, int);



};

