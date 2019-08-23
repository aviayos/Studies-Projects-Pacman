#include "Menu.h"
#include "Controller.h"



Menu::Menu()
{
	m_Order = Menu_t;
	m_voice = ON_t;
	//load the textures of the sprites shown on menu
	m_Background.setTexture(*(Files::instance().getPic(4)));
	m_Background.setTextureRect(sf::IntRect(0, 0, 1024, 728));
	//start button
	m_Start.setTexture(*(Files::instance().getPic(5)));
	m_Start.setTextureRect(sf::IntRect(0, 0, 200, 400));
	m_Start.setPosition(50.f, 550.f);
	//high score button
	m_HighScore.setTexture(*(Files::instance().getPic(5)));
	m_HighScore.setTextureRect(sf::IntRect(200 * 1, 0, 200, 400));
	m_HighScore.setPosition(300.f, 550.f);
	//help button
	m_Help.setTexture(*(Files::instance().getPic(5)));
	m_Help.setTextureRect(sf::IntRect(200 * 2, 0, 200, 400));
	m_Help.setPosition(550.f, 550.f);
	//exit button
	m_Exit.setTexture(*(Files::instance().getPic(5)));
	m_Exit.setTextureRect(sf::IntRect(200 * 3, 0, 200, 400));
	m_Exit.setPosition(800.f, 550.f);
	//sound button
	m_Voice.setTexture(*(Files::instance().getPic(6)));
	m_Voice.setPosition(0.f, 0.f);
	//high score screen
	m_HighScoreScreen.setTexture(*(Files::instance().getPic(7)));
	m_HighScoreScreen.setTextureRect(sf::IntRect(0, 0, 1024, 728));
	//new high score screen
	m_NewHighScore.setTexture(*(Files::instance().getPic(8)));
	m_NewHighScore.setTextureRect(sf::IntRect(0, 0, 800, 600));
	//help screen
	m_HelpScreen.setTexture(*(Files::instance().getPic(9)));
	m_HelpScreen.setTextureRect(sf::IntRect(0, 0, 1024, 728));

}
//the main function of the menu
void Menu::start()
{
	while (m_Order != Exit_t) {

		sf::Vector2f coords;
		bool exit = false;
		m_Order = Menu_t;
		Files::instance().PlayBackground();
		sf::RenderWindow window(sf::VideoMode(1024, 728), "Pacman", sf::Style::Titlebar);
		while (m_Order != Exit_t && m_Order != Start_t)
		{
			setDefault();
			sf::Event event;
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::Closed:
					window.close();
					break;

				case sf::Event::MouseMoved:
					coords = window.mapPixelToCoords({ event.mouseMove.x, event.mouseMove.y });
					check_sign(coords);
					break;
					
				case sf::Event::MouseButtonPressed:
					coords = window.mapPixelToCoords(
						{ event.mouseButton.x, event.mouseButton.y });
					getOrder(window, coords, exit);
					break;
				}
				draw(window);
				window.display();
			}
		}
	}
}
//method get the click from the user
void Menu::getOrder(sf::RenderWindow& window, sf::Vector2f coords, bool& exit)
{
	if (coords.y >= 550 && coords.y <= 750)
	{
		if (coords.x >= 50 && coords.x <= 250)//start
		{
			Files::instance().PlayClick();
			window.close();
			m_Order = Start_t;
			Controller cont;
			cont.run();
			//end game
			//check high score.
			checkHighScore(cont.get_score());

		}
		if (coords.x >= 300 && coords.x <= 500)//high score
		{
			Files::instance().PlayClick();
			Files::instance().stopBackground();
			Files::instance().PlayChamp();
			ShowLeadBoard(window);
			Files::instance().stopChamp();
			Files::instance().PlayBackground();

		}
		if (coords.x >= 550 && coords.x <= 750)//Help
		{
			Files::instance().PlayClick();
			ShowHelpScreen(window);
		}

		if (coords.x >= 800 && coords.x <= 1000) {//exit
			Files::instance().PlayClick();
			m_Order = Exit_t;
		}
	}

	if ((coords.y >= 0 && coords.y <= 50) && (coords.x >= 0 && coords.x <= 50))//sound icon
	{
		if (m_voice == ON_t)
		{
			Files::instance().Mute();
			m_voice = OFF_t;
		}
		else
		{
			Files::instance().MusicOn();
			m_voice = ON_t;
		}
	}
}
//function draw the help screen, get the render window from the menu
void Menu::ShowHelpScreen(sf::RenderWindow &window)
{
	sf::Event user_event;
	window.clear();
	window.draw(m_HelpScreen);
	window.display();

	bool exit = false;
	while (!exit)
	{
		while (window.pollEvent(user_event))
		{
			if (user_event.type == sf::Event::KeyPressed)
			{
				if (user_event.key.code == sf::Keyboard::Escape)
					exit = true;
			}
		}
	}
}
//this function draw the menu screen 
void Menu::draw(sf::RenderWindow &window)
{
	window.clear();
	window.draw(m_Background);
	window.draw(m_Start);
	window.draw(m_HighScore);
	window.draw(m_Help);
	window.draw(m_Exit);
	m_Voice.setTextureRect(sf::IntRect(0, 50 * m_voice, 50, 50));
	window.draw(m_Voice);
}
//function check the 5 leaders scores, get the player score and check if he did score that higher than the leaders 
void Menu::checkHighScore(int playerScore)
{
	readLeaders();
	int score;
	bool written = false;//check if the player written on vector, when the vector size is less then 5
	string name;

	if (m_leadings.size() > 5)//if the vector size is bigger than 5
	{
		for (unsigned int i = 0; i < 5; i++)
		{
			std::stringstream ss(extract_ints(m_leadings[i]));//extract the int from the string
			ss >> score;
			if (score < playerScore)
			{
				name = NewHighScore();
				name += " " + std::to_string(playerScore);
				m_leadings.insert(m_leadings.begin() + i, name);//put it on the other place, and push the others
				break;
			}
		}
	}
	else//if the vector size is less than 5
	{
		for (unsigned int i = 0; i < m_leadings.size(); i++)
		{
			std::stringstream ss(extract_ints(m_leadings[i]));
			ss >> score;
			if (score < playerScore)
			{
				name = NewHighScore();
				name += " " + std::to_string(playerScore);
				m_leadings.insert(m_leadings.begin() + i, name);//put it on the other place, and push the others
				written = true;
				break;
			}
		}
		if (written == false)
		{
			name = NewHighScore();
			name += " " + std::to_string(playerScore);
			m_leadings.insert(m_leadings.begin() + m_leadings.size(), name);//put it on the other place, and push the others
			written = true;
		}
	}
	writeRecordsOnFile();//write the new scores on file

}

//function extract int from string
std::string Menu::extract_ints(string str)
{
	return extract_ints(std::ctype_base::digit, str,
		std::use_facet<std::ctype<char>>(std::locale("")));

}
//function extract int from string
std::string Menu::extract_ints(std::ctype_base::mask category, string str, std::ctype<char> const& facet)
{
	using std::strlen;

	char const *begin = &str.front(), *end = &str.back();

	auto res = facet.scan_is(category, begin, end);

	begin = &res[0];
	end = &res[strlen(res)];

	return std::string(begin, end);
}
//function check the mouse coords and "highlights" the sprite
void Menu::check_sign(sf::Vector2f coords)
{
	if (coords.y >= 550 && coords.y <= 750)//the height of all buttons
	{
		if (coords.x >= 50 && coords.x <= 250)//start sprite
			m_Start.setTextureRect(sf::IntRect(0, 100, 200, 100));

		if (coords.x >= 300 && coords.x <= 500)//high score sprite
			m_HighScore.setTextureRect(sf::IntRect(200, 100, 200, 100));

		if (coords.x >= 550 && coords.x <= 750)//help sprite
			m_Help.setTextureRect(sf::IntRect(400, 100, 200, 100));

		if (coords.x >= 800 && coords.x <= 1000)//exit sprite
			m_Exit.setTextureRect(sf::IntRect(600, 100, 200, 100));
	}
}
//function read from text the leading board and place it on m_leading(vector)
void Menu::readLeaders()
{
	std::ifstream file;
	file.open("High_Score.txt");
	string str;

	while (!file.eof())
	{
		getline(file, str);
		if (str.size() >= 3)
			m_leadings.push_back(str);
	}

	file.close();
}
//clean the leadings vector
void Menu::cleanLeadings()
{
	int size = m_leadings.size();

	for (int i = 0; i < size; i++)
		m_leadings.pop_back();
}

// return the sprites to normal shape
void Menu::setDefault()
{
	m_Start.setTextureRect(sf::IntRect(0, 0, 200, 100));
	m_HighScore.setTextureRect(sf::IntRect(200, 0, 200, 100));
	m_Help.setTextureRect(sf::IntRect(400, 0, 200, 100));
	m_Exit.setTextureRect(sf::IntRect(600, 0, 200, 100));
}
//method shows the leading board (top 5 high scores), print it on render window with 
//special screen 
void Menu::ShowLeadBoard(sf::RenderWindow & window)
{
	sf::Event user_event;
	window.clear();
	window.draw(m_HighScoreScreen);//draw the sprites of this screen
	ifstream file;
	file.open("High_Score.txt");//open the file, read the leaders from there 
	string name;
	string score;
	sf::Text leaders(name, *(Files::instance().getFont()), 40);//set the font and size

	for (int i = 0; i < 5; i++)
	{

		name = std::to_string(i + 1);
		name += ". ";
		string temp;
		getline(file, temp);
		if (temp.size() >= 3)//assume that name + score size will be 3 or more
		{
			name += getName(temp);//adding the name to the string
			score = getTheScore(temp);//get the score from the screen

			leaders.setString(score);
			leaders.setPosition(580.f, (float)(250 + i * 50));
			window.draw(leaders);//print the score
		}
		leaders.setString(name);//print the name and the position
		leaders.setPosition(40.f, (float)(250 + i * 50));
		window.draw(leaders);

	}
	window.display();

	bool exit = false;
	while (!exit)//wait to esc button
	{
		while (window.pollEvent(user_event))
		{
			if (user_event.type == sf::Event::KeyPressed)
			{
				if (user_event.key.code == sf::Keyboard::Escape)//wait to esc button for exit
					exit = true;
			}
		}

	}
	file.close();
}

//method when the player got high score (if reach the top 5), get his name and write on the vec 
string Menu::NewHighScore()
{
	Files::instance().stopBackground();
	Files::instance().PlayChamp();
	sf::RenderWindow record(sf::VideoMode(800, 600), "New High Score!", sf::Style::Titlebar | sf::Style::Close);
	record.draw(m_NewHighScore);
	sf::String name;
	sf::Text text(name, *(Files::instance().getFont()), 25);
	text.setPosition(315, 310);
	bool end = false;

	while (!end)
	{
		sf::Event event;
		while (record.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape)
					record.close();
				if (event.key.code == sf::Keyboard::Return)
					end = true;
				break;
			case sf::Event::TextEntered://get his name
				if (event.text.unicode == 8 && name.getSize() > 0)
					name.erase(name.getSize() - 1, name.getSize());
				if (name.getSize() <= 20)//name size < 20
				{
					if ((event.text.unicode >= 32 && event.text.unicode <= 47) ||
						(event.text.unicode >= 58 && event.text.unicode <= 126)) {
						name += (char)event.text.unicode;
						Files::instance().PlayClick();
					}

				}
				text.setString(name);
			}
		}
		record.clear();
		record.draw(m_NewHighScore);
		record.draw(text);
		record.display();

	}
	record.close();
	Files::instance().stopChamp();
	Files::instance().PlayBackground();
	return name;
}
//extract the name from the whole string in the vec
string Menu::getName(string temp)
{
	int place = 0;
	char c = temp[place];
	while (!isdigit(c))
	{
		place++;
		c = temp[place];
	}
	return temp.substr(0, place);
}
//extract the score from the whole string in the vec
string Menu::getTheScore(string temp)
{
	int score;
	std::stringstream ss(extract_ints(temp));
	ss >> score;

	return std::to_string(score);

}

//write the vec on the high score file
void Menu::writeRecordsOnFile()
{
	std::ofstream file;
	file.open("High_Score.txt");
	file.clear();

	for (size_t i = 0; i < m_leadings.size(); i++)
	{
		if (i == 6)
			break;

		file << m_leadings[i] << std::endl;
	}

	file.close();

	cleanLeadings();
}
