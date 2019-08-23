#include "Controller.h"


//-------------------------------------------------------------------------------------------------
Controller::Controller()
{
}
//-------------------------------------------------------------------------------------------------
//main method running the game 
void Controller::run()
{
	Files::instance().PlayBackground();//put on music
	srand((unsigned)time(NULL));
	
	bool createNewWind = true;//while reach the end of level turned to false for create new render window
	float factor;//factor help us with the times and speed
	float playersMovment = 0;
	sf::Clock clock;

	m_level.LoadNewLvL();//load the new level
	Char_Details temp = m_level.getPacData();//get the data from the level
	m_player = make_unique <Pacman>(temp.type, temp.m_StartPlace);
	set_rivals();//set the ghosts

	while (createNewWind)
	{
		sf::RenderWindow window(sf::VideoMode((unsigned int)(m_level.getBoardSize().x * SHAPE_SIZE),
			(unsigned int)(m_level.getBoardSize().y * SHAPE_SIZE + STATUS_SIZE)),
			"Pacman",
			sf::Style::Titlebar/* | sf::Style::Close*/);
		createNewWind = false;
		Direction_t way = Stop_t;//default direction

		m_level.getBoardSize().x >= m_level.getBoardSize().y ? factor = (float)m_level.getBoardSize().x / SHAPE_SIZE :
			factor = (float)m_level.getBoardSize().y / SHAPE_SIZE;

		StatusBar game_status(m_level.getBoardSize());

		while (window.isOpen() && m_player.get()->getLives() > 0 && !createNewWind)
		{
			sf::Event user_event;
			if (m_level.AllCookiesAte())//cookies over - time to load new level
			{
				clearRivals();
				m_level.emptyVec();
				m_level.LoadNewLvL();
				set_rivals();
				setPlayer(way);
				createNewWind = true;
			}
			getEvent(window, user_event, way, clock);//get the event from the window
			playersMovment += clock.restart().asSeconds();
			popCookie(playersMovment * factor);//
			draw(window, playersMovment * factor, game_status);
			if (playersMovment >= TIME_TO_MOVE) {//constants for moving all the characters
				move(way, playersMovment);
				playersMovment = 0;
			}
			window.display();
		}

		window.close();

	}
}

//-------------------------------------------------------------------------------------------------
//method create the vector of ptrs of the ghosts
void Controller::set_rivals()
{
	Char_Details temp;

	if (m_rivals.size() > 0)
		clearRivals();

	for (int i = 0; i < m_level.getNumghost(); i++)
	{
		temp = m_level.getGhostData(i);
		if (i % 2 == 0)//even will be smart
			m_rivals.push_back(std::make_unique<SmartGhost>(temp.m_StartPlace, temp.type));
		else//odd will be random
			m_rivals.push_back(std::make_unique<RandomGhost>(temp.m_StartPlace, temp.type));
	}

}
//-------------------------------------------------------------------------------------------------
//method moves the pacman and the ghosts
void Controller::move(Direction_t &way, float playersMovment)
{
	sf::Vector2i PlaceOnBoard;
	sf::Vector2f new_place;

	new_place = m_player->move(way, playersMovment);
	teleport(new_place, m_player.get());
	checkCollision(m_player.get(), m_player.get()->getDir());

	PlaceOnBoard.x = (int)(m_player.get()->getPlace().x / SHAPE_SIZE);
	PlaceOnBoard.y = (int)(m_player.get()->getPlace().y / SHAPE_SIZE);
	//bfs tree 
	 vector<vector<sf::Vector3i>> waysToPac = m_player.get()->BFS_fromMe(PlaceOnBoard, m_level.getBoard());

	for (size_t i = 0; i < m_rivals.size(); i++)
	{
		new_place = m_rivals[i].get()->move(waysToPac, playersMovment);
		teleport(new_place, m_rivals[i].get());
		checkCollision(m_rivals[i].get(), m_rivals[i].get()->getDir());

		if (m_player.get()->isCloseEnough(m_rivals[i].get()->getPlace())) {//collison between ghost and pacman
			m_player.get()->collide(m_rivals[i].get(), m_level);
			StartPlaces();
			way = Stop_t;
		}

	}

}
//-------------------------------------------------------------------------------------------------
//draw the whole drawable characters and status bar 
void Controller::draw(sf::RenderWindow &window, float playersMovment, StatusBar & game_status)
{
	window.clear();
	m_level.draw(window);
	m_player->draw(window, playersMovment);

	for (size_t i = 0; i < m_rivals.size(); i++)
		m_rivals[i].get()->draw(window, playersMovment);
	game_status.draw(window, m_player.get()->getLives(), m_player.get()->getScore(), m_level.getLevel());

}
//-------------------------------------------------------------------------------------------------
//method exchange the charcters place if they go thorugh teleport passage
void Controller::teleport(sf::Vector2f& new_place, DynamicObj* player)
{
	sf::Vector2i board_size = m_level.getBoardSize();

	if (new_place.x > board_size.x * 32 && player->getDir() == Right_t)
		new_place.x = 0.f;

	else if (new_place.x < 0 && player->getDir() == Left_t)
		new_place.x = (float)((board_size.x * 32) - 1);


	else if (new_place.y > board_size.y * 32 && player->getDir() == Down_t)
		new_place.y = 0;


	else if (new_place.y < 0 && player->getDir() == Up_t)
		new_place.y = (float)((board_size.y * 32) - 1);


	player->setNewPlace(new_place);
}
//-------------------------------------------------------------------------------------------------
//function check collisons between dynamic obect and static object
void Controller::checkCollision(DynamicObj* character, Direction_t way)
{
	sf::Vector2f obj_place = character->getPlace();
	Object* object = m_level.getObject(obj_place, way);//return the object
													   //that is in the destination of the characters

	if (object != nullptr)
		object->collide(character, m_level);
}
//-------------------------------------------------------------------------------------------------
//method get the next event from the user, get the clock,event, direction and the window by refer
void Controller::getEvent(sf::RenderWindow& window, sf::Event& user_event,
	Direction_t& way, sf::Clock& clock)
{

	while (window.pollEvent(user_event))
	{
		switch (user_event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;

		case sf::Event::KeyPressed:
			if (user_event.key.code == sf::Keyboard::Right)
				way = Right_t;
			else if (user_event.key.code == sf::Keyboard::Down)
				way = Down_t;

			else if (user_event.key.code == sf::Keyboard::Left)
				way = Left_t;

			else if (user_event.key.code == sf::Keyboard::Up)
				way = Up_t;

			else if (user_event.key.code == sf::Keyboard::Space)
				way = Stop_t;

			else if (user_event.key.code == sf::Keyboard::Escape)
			{
				PauseGame(window);//the game paused
				clock.restart();
				break;
			}
			else if (user_event.key.code == sf::Keyboard::M)//mute the sounds
				Files::instance().Mute();                  //during the game

			else if (user_event.key.code == sf::Keyboard::S)
				Files::instance().MusicOn();//turn on the sounds during the game

			break;
		}
	}
}
//-------------------------------------------------------------------------------------------------
//method clean up the vector of ghost after loading new level
void Controller::clearRivals()
{
	size_t size = m_rivals.size();
	for (size_t i = 0; i < size; i++)
		m_rivals.pop_back();
}
//-------------------------------------------------------------------------------------------------
//method turn back the pacman and the ghosts to their starting position
void Controller::StartPlaces()
{
	Char_Details temp;
	sf::Vector2f start_place;

	temp = m_level.getPacData();
	start_place.x = (float)temp.m_StartPlace.x * SHAPE_SIZE + CENTER;
	start_place.y = (float)temp.m_StartPlace.y * SHAPE_SIZE + CENTER;
	m_player.get()->setNewPlace(start_place);


	for (size_t i = 0; i < m_rivals.size(); i++)
	{
		temp = m_level.getGhostData(i);
		start_place.x = (float)temp.m_StartPlace.x * SHAPE_SIZE + CENTER;
		start_place.y = (float)temp.m_StartPlace.y * SHAPE_SIZE + CENTER;
		m_rivals[i].get()->setNewPlace(start_place);

	}
}
//-------------------------------------------------------------------------------------------------
//method change the pacman details(color,place) while reaching the next stage.
// change also the next direction(way) as default(stop_t)
void Controller::setPlayer(Direction_t &way)
{
	Char_Details temp = m_level.getPacData();
	sf::Vector2f place;
	place.x = (float)temp.m_StartPlace.x * SHAPE_SIZE + CENTER;
	place.y = (float)temp.m_StartPlace.y * SHAPE_SIZE + CENTER;
	m_player.get()->ChangePlayerColor(temp.type);
	m_player.get()->setNewPlace(place);
	way = Stop_t;
}
//-------------------------------------------------------------------------------------------------
//method poping special cookies on random and clear place on board
//get the time from the method "run"
void Controller::popCookie(float time)
{
	static float time_to_pop = 0;
	static int type = -1;
	time_to_pop += time;

	if (time_to_pop >= 160.f)//20 seconds more or less 
	{
		type = rand() % 2;//choose the type of the cookie: poison/health
		m_level.setSpecialCookie(type);
		time_to_pop = 0;//initial the static
	}
	if (m_level.Is_SpecialCreated())
		m_level.SpecialsRemove(time);//summarize the "time" when special cookie created
									 // and check removal time

	if (m_player.get()->ateSpecial())//if the player ate one of the specials
	{
		m_player.get()->CountSpeed(time, type);//calculate his new speed
	}
}
//-------------------------------------------------------------------------------------------------
//method printing a "pause" sprite and wait for the player choice
void Controller::PauseGame(sf::RenderWindow & window)
{
	bool pause = true;//using the while term, turn to false if the user want to resume
	sf::Event user_event;
	sf::Vector2f coords;
	sf::Sprite pause_screen;

	pause_screen.setTexture(*(Files::instance().getPic(10)));
	pause_screen.setOrigin(100, 150);
	pause_screen.setTextureRect(sf::IntRect(0, 0, 200, 300));
	sf::Vector2f center{ (m_level.getBoardSize().x * SHAPE_SIZE) / 2 ,
		((m_level.getBoardSize().y) * SHAPE_SIZE) / 2 };
	pause_screen.setPosition(center);

	window.draw(pause_screen);
	window.display();

	while (pause)
	{
		while (window.pollEvent(user_event))
		{
			switch (user_event.type)
			{
			case sf::Event::MouseButtonPressed:
				coords = window.mapPixelToCoords({ user_event.mouseButton.x, user_event.mouseButton.y });
				if (coords.x >= center.x - 65.f && coords.x <= center.x + 75.f)
				{
					if (coords.y >= center.y - 45.f  && coords.y <= center.y + 25.f) {//resume
						pause = false;
						Files::instance().PlayClick();
					}
					else if ((coords.y >= center.y + 50.f && coords.y <= center.y + 120.f)) {//exit
						window.close();
						pause = false;
						Files::instance().PlayClick();
					}
				}
			}
		}
	}
}
//-------------------------------------------------------------------------------------------------
//method return to the menu the score of the player in the end of the game 
int Controller::get_score()
{
	return m_player.get()->getScore();

}


