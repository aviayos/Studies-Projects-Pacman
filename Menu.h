#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <cstring>
#include <stdlib.h>
#include <ctype.h>

using std::vector;
using std::string;

enum Orders_t { Start_t, HighScore_t, Help_t, Exit_t, Menu_t };//enums of the orders in the main screen
enum Sounds_t { ON_t, OFF_t };//enums of the sound in the game
class Menu
{
public:
	Menu();
	void start();

private:
	sf::Sprite m_Background;
	sf::Sprite m_Start;
	sf::Sprite m_HighScore;
	sf::Sprite m_Help;
	sf::Sprite m_Exit;
	sf::Sprite m_Voice;
	sf::Sprite m_HelpScreen;
	sf::Sprite m_HighScoreScreen;
	sf::Sprite m_NewHighScore;
	Orders_t m_Order;
	Sounds_t m_voice;
	vector <std::string> m_leadings;//vector hold the leading scores placed on text file

	void draw(sf::RenderWindow&);
	void getOrder(sf::RenderWindow& window, sf::Vector2f coords, bool& exit);
	string NewHighScore();
	string getName(string);
	string getTheScore(string);
	void writeRecordsOnFile();
	void ShowLeadBoard(sf::RenderWindow &window);
	void checkHighScore(int);
	void check_sign(sf::Vector2f);
	void setDefault();
	void readLeaders();
	void cleanLeadings();
	string extract_ints(string str);
	string extract_ints(std::ctype_base::mask category, string str, std::ctype<char> const& facet);
	void ShowHelpScreen(sf::RenderWindow &window);

};

