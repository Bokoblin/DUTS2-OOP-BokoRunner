#include "../header/MenuView.h"

using namespace std;

/********************************************
    Parameterized Constructor
*********************************************
    @author Arthur  @date 25/02 - 14/04
*********************************************/
MenuView::MenuView(float w, float h, sf::RenderWindow *window, Text * text):
	View(w, h, window,text), m_menuModel{nullptr}
{
	if (m_window->getSize().x != m_width )
	{
		m_window->create( sf::VideoMode(w, h, 32), "Boko Runner", sf::Style::Close );
		m_window->setFramerateLimit(30);
		m_window->setPosition(sf::Vector2i( (sf::VideoMode::getDesktopMode().width - m_width)/2,
				(sf::VideoMode::getDesktopMode().height - m_height)/2 ));
	}

	loadImages();
}


/********************************************
    Destructor
*********************************************
    @author Arthur  @date 26/02 - 20/04
*********************************************/
MenuView::~MenuView()
{
	//=== Home Menu Graphic Elements

	delete m_farBackground;
	delete m_nearBackground;
	delete m_titleGraphic;
	delete m_playRectButton;
	delete m_quitRectButton;
	delete m_settingsFormButton;
    delete m_leaderboardFormButton;
    delete m_clearLbRectButton;

	//=== Settings Graphic Elements

	delete m_homeFormButton;
	delete m_englishLangRadioButton;
	delete m_frenchLangRadioButton;
	delete m_spanishLangRadioButton;
	delete m_normalQuestRadioButton;
	delete m_masterQuestRadioButton;
}


/********************************************
   Setters
*********************************************
    @author Arthur  @date 14/04
*********************************************/
void MenuView::setMenuModel(MenuModel *model)
{
	m_menuModel = model;
}


/********************************************
    Image Loading
*********************************************
    @author Arthur  @date 26/03 - 20/04
*********************************************/
void MenuView::loadImages()
{
	if (!m_farBackgroundTexture.loadFromFile(DEFAULT_FAR_HILL_BACKGROUND ))
		cerr << "ERROR when loading image file: " << DEFAULT_FAR_HILL_BACKGROUND << endl;
	else
	{
		m_farBackgroundTexture.setSmooth(true);
		m_farBackground = new SlidingBackground(m_farBackgroundTexture, 1200, m_height, 1);
	}

	if (!m_nearBackgroundTexture.loadFromFile(DEFAULT_NEAR_HILL_BACKGROUND ))
		cerr << "ERROR when loading image file: " << DEFAULT_NEAR_HILL_BACKGROUND << endl;
	else
	{
		m_nearBackgroundTexture.setSmooth(true);
		m_nearBackground = new SlidingBackground(m_nearBackgroundTexture, 1200, m_height, 2);
	}

	if (!m_titleImageTexture.loadFromFile(TITLE_IMAGE) )
		cerr << "ERROR when loading image file: " << TITLE_IMAGE << endl;
	else
	{
		m_titleImageTexture.setSmooth(true);
		m_titleGraphic = new GraphicElement(m_titleImageTexture, m_width/2-200, m_height/6, 400, 200);
	}

	//=== Initialize PLAY, QUIT and CLEAR Leaderboard buttons

	if (!m_menuRectButtonsTexture.loadFromFile(RECT_BUTTONS_IMAGE) )
		cerr << "ERROR when loading image file: " << RECT_BUTTONS_IMAGE << endl;
	else
	{
        m_menuRectButtonsTexture.setSmooth(true);

		std::vector<sf::IntRect> clip_rects_play;
		clip_rects_play.push_back(sf::IntRect( 0, 0, 150, 80));
		clip_rects_play.push_back(sf::IntRect(151, 0, 150, 80));
		m_playRectButton = new Button(clip_rects_play, m_menuRectButtonsTexture, m_width/2-75, m_height/1.5, 150, 80, false);

		std::vector<sf::IntRect> clip_rects_quit;
		clip_rects_quit.push_back(sf::IntRect( 0, 0, 150, 80));
		clip_rects_quit.push_back(sf::IntRect(151, 0, 150, 80));
		m_quitRectButton = new Button(clip_rects_quit, m_menuRectButtonsTexture, m_width/2-75, m_height/1.2, 150, 80, false);

        std::vector<sf::IntRect> clip_rects_clear;
		clip_rects_clear.push_back(sf::IntRect( 0, 100, 150, 40));
		clip_rects_clear.push_back(sf::IntRect(151, 100, 150, 40));
        m_clearLbRectButton = new Button(clip_rects_clear, m_menuRectButtonsTexture, m_width/2-75, 500, 150, 40, false);
    }

    //=== Initialize SETTINGS, LEADERBOARD and HOME form buttons

	if (!m_menuFormButtonsTexture.loadFromFile(FORM_BUTTONS_IMAGE) )
		cerr << "ERROR when loading image file: " << FORM_BUTTONS_IMAGE << endl;
	else
	{
		m_menuFormButtonsTexture.setSmooth(true);

		std::vector<sf::IntRect> clip_rects_settings;
		clip_rects_settings.push_back(sf::IntRect( 0, 0, 50, 50));
		clip_rects_settings.push_back(sf::IntRect( 51, 0, 50, 50));
		m_settingsFormButton = new Button(clip_rects_settings, m_menuFormButtonsTexture, 20, 530, 50, 50, false);

		std::vector<sf::IntRect> clip_rects_home;
		clip_rects_home.push_back(sf::IntRect( 0, 50, 50, 50));
		clip_rects_home.push_back(sf::IntRect( 51, 50, 50, 50));
		m_homeFormButton = new Button(clip_rects_home, m_menuFormButtonsTexture, 10, 10, 50, 50, false);

        std::vector<sf::IntRect> clip_rects_lb;
        clip_rects_lb.push_back(sf::IntRect( 0, 100, 50, 50));
        clip_rects_lb.push_back(sf::IntRect( 51, 100, 50, 50));
        m_leaderboardFormButton = new Button(clip_rects_lb, m_menuFormButtonsTexture, 830, 530, 50, 50, false);
	}


	//=== Initialize settings radio buttons

	if (!m_menuRadioButtonsTexture.loadFromFile(RADIO_BUTTONS_IMAGE) )
		cerr << "ERROR when loading image file: " << RADIO_BUTTONS_IMAGE << endl;
	else
	{
		m_menuRadioButtonsTexture.setSmooth(true);

		std::vector<sf::IntRect> clip_rects;
		clip_rects.push_back(sf::IntRect(  0,   0, 50, 50) );
		clip_rects.push_back(sf::IntRect(50,   0, 50, 50) );
		clip_rects.push_back(sf::IntRect(  0, 50, 50, 50) );
		clip_rects.push_back(sf::IntRect(50, 50, 50, 50) );

		m_englishLangRadioButton  = new Button(clip_rects, m_menuRadioButtonsTexture, 50, 205, 50, 50, true);
		m_frenchLangRadioButton   = new Button(clip_rects, m_menuRadioButtonsTexture, 50, 245, 50, 50, true);
		m_spanishLangRadioButton = new Button(clip_rects, m_menuRadioButtonsTexture, 50, 285, 50, 50, true);
		m_normalQuestRadioButton = new Button(clip_rects, m_menuRadioButtonsTexture, 50, 420, 50, 50, true);
		m_masterQuestRadioButton = new Button(clip_rects, m_menuRadioButtonsTexture, 50, 460, 50, 50, true);
	}
}


/********************************************
    Synchronization function
*********************************************
    @author Arthur  @date 26/03 - 19/04
*********************************************/
void MenuView::synchronize()
{
	if (m_menuModel->getHomeState() == true)
	{
		//=== Elements update

		m_titleGraphic->resize(400,200);
		m_farBackground->sync();
		m_nearBackground->sync();
		m_playRectButton->sync();
		m_quitRectButton->sync();
		m_settingsFormButton->sync();
        m_leaderboardFormButton->sync();

		//=== Text update

		m_text->syncMenuHomeText(m_width, m_height);

	}
	else if (m_menuModel->getSettingsState() == true)
	{
		//=== Elements update

		m_englishLangRadioButton->setActivatedState(m_menuModel->getDataModel()->getLanguage() == "en");
		m_frenchLangRadioButton->setActivatedState(m_menuModel->getDataModel()->getLanguage() == "fr");
		m_spanishLangRadioButton->setActivatedState(m_menuModel->getDataModel()->getLanguage() == "es");
		m_normalQuestRadioButton->setActivatedState(m_model->getDifficulty() == 0);
		m_masterQuestRadioButton->setActivatedState(m_model->getDifficulty() != 0);
		m_homeFormButton->sync();
		m_englishLangRadioButton->sync();
		m_frenchLangRadioButton->sync();
		m_spanishLangRadioButton->sync();
		m_normalQuestRadioButton->sync();
		m_masterQuestRadioButton->sync();
		m_homeFormButton->resize(30, 30);
		m_englishLangRadioButton->resize(25, 25);
		m_frenchLangRadioButton->resize(25, 25);
		m_spanishLangRadioButton->resize(25, 25);
		m_normalQuestRadioButton->resize(25, 25);
		m_masterQuestRadioButton->resize(25, 25);

		//=== Text update

		m_text->syncMenuSettingsText(m_menuModel, m_width, m_height);

	}
    else if (m_menuModel->getLeaderboardState() == true)
    {
        //=== Elements update

        m_homeFormButton->sync();
        m_clearLbRectButton->sync();
        m_clearLbRectButton->setPosition(m_width/2 -
				m_clearLbRectButton->getGlobalBounds().width/2, 500);
        m_homeFormButton->resize(30, 30);

        //=== Text update

        m_text->syncMenuLeaderboardText(m_width, m_height,
			m_menuModel->getLeaderboard());

    }
}


/********************************************
    Menu View Drawing
*********************************************
    @author Arthur  @date 26/03 - 20/04
*********************************************/
void MenuView::draw() const
{
	if (m_menuModel->getHomeState() == true)
	{
		m_window->clear();

		//=== Graphic Elements drawing

		m_farBackground->draw(m_window);
		m_nearBackground->draw(m_window);
		m_window->draw(*m_titleGraphic);
		m_window->draw(*m_playRectButton);
		m_window->draw(*m_quitRectButton);
		m_window->draw(*m_settingsFormButton);
        m_window->draw(*m_leaderboardFormButton);

		//=== Text Drawing

		m_text->drawMenuHomeText(m_window);

	}
	else if (m_menuModel->getSettingsState() == true)
	{
		m_window->clear(sf::Color(51, 51, 51, 255) );

		//=== Graphic Elements drawing

		m_window->draw(*m_homeFormButton);
		m_window->draw(*m_englishLangRadioButton);
		m_window->draw(*m_frenchLangRadioButton);
		m_window->draw(*m_spanishLangRadioButton);
		m_window->draw(*m_normalQuestRadioButton);
		m_window->draw(*m_masterQuestRadioButton);

		//=== Text Drawing

		m_text->drawMenuSettingsText(m_window);

	}
    else if (m_menuModel->getLeaderboardState() == true)
    {
        m_window->clear(sf::Color(51, 51, 51, 255) );

        //=== Graphic Elements drawing

        m_window->draw(*m_homeFormButton);
        m_window->draw(*m_clearLbRectButton);

        //=== Text Drawing

        m_text->drawMenuLeaderboardText(m_window);

    }

	m_window->display();
}


/********************************************
    Events treating
*********************************************
    @author Arthur  @date 25/03 - 20/04
*********************************************/
bool MenuView::treatEvents()
{
	bool result = false;

	if(m_window->isOpen())
	{
		result = true;

		sf::Event event;
		while (m_window->pollEvent(event))
		{
			if  (event.type == sf::Event::Closed)
			{
				m_model->setMenuState(false);
				m_window->close();
				result = false;
			}

			//Home Screen
			if (m_menuModel->getHomeState() == true)
			{
				if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
				{
					if ( m_playRectButton->getGlobalBounds().contains(MOUSE_POSITION) )
					{
						m_playRectButton->setPressedState(true);
					}
					else if ( m_quitRectButton->getGlobalBounds().contains(MOUSE_POSITION) )
					{
						m_quitRectButton->setPressedState(true);
					}
					else if ( m_settingsFormButton->getGlobalBounds().contains(MOUSE_POSITION) )
					{
						m_settingsFormButton->setPressedState(true);
					}
                    else if ( m_leaderboardFormButton->getGlobalBounds().contains(MOUSE_POSITION) )
                    {
                        m_leaderboardFormButton->setPressedState(true);
                    }
				}

				if (event.type == sf::Event::MouseButtonReleased)
				{
					m_playRectButton->setPressedState(false);
					m_quitRectButton->setPressedState(false);
					m_settingsFormButton->setPressedState(false);
                    m_leaderboardFormButton->setPressedState(false);

					if ( m_playRectButton->getGlobalBounds().contains(MOUSE_POSITION) )
					{
						m_model->setMenuState(false);
						m_model->setGameState(true);
						result = false;
					}
					else if ( m_quitRectButton->getGlobalBounds().contains(MOUSE_POSITION) )
					{
						m_window->close();
						result = false;
					}
					else if ( m_settingsFormButton->getGlobalBounds().contains(MOUSE_POSITION) )
					{
						m_menuModel->setHomeState(false);
						m_menuModel->setSettingsState(true);
					}
                    else if ( m_leaderboardFormButton->getGlobalBounds().contains(MOUSE_POSITION) )
                    {
                        m_menuModel->setHomeState(false);
                        m_menuModel->setLeaderboardState(true);
                    }
				}
			}

			//Settings Screen
			else if (m_menuModel->getSettingsState() == true)
			{
				if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
				{
					if ( m_homeFormButton->getGlobalBounds().contains(MOUSE_POSITION) )
					{
						m_homeFormButton->setPressedState(true);
					}
					else if ( m_englishLangRadioButton->getGlobalBounds().contains(MOUSE_POSITION) )
					{
						m_englishLangRadioButton->setPressedState(true);
					}
					else if ( m_frenchLangRadioButton->getGlobalBounds().contains(MOUSE_POSITION) )
					{
						m_frenchLangRadioButton->setPressedState(true);
					}
					else if ( m_spanishLangRadioButton->getGlobalBounds().contains(MOUSE_POSITION) )
					{
						m_spanishLangRadioButton->setPressedState(true);
					}
					else if ( m_normalQuestRadioButton->getGlobalBounds().contains(MOUSE_POSITION) )
					{
						m_normalQuestRadioButton->setPressedState(true);
					}
					else if ( m_masterQuestRadioButton->getGlobalBounds().contains(MOUSE_POSITION) )
					{
						m_masterQuestRadioButton->setPressedState(true);
					}
				}

				if (event.type == sf::Event::MouseButtonReleased)
				{
					m_homeFormButton->setPressedState(false);
					m_englishLangRadioButton->setPressedState(false);
					m_frenchLangRadioButton->setPressedState(false);
					m_spanishLangRadioButton->setPressedState(false);
					m_normalQuestRadioButton->setPressedState(false);
					m_masterQuestRadioButton->setPressedState(false);

					if ( m_homeFormButton->getGlobalBounds().contains(MOUSE_POSITION) )
					{
						m_menuModel->setSettingsState(false);
						m_menuModel->setHomeState(true);
					}
					else if ( m_englishLangRadioButton->getGlobalBounds().contains(MOUSE_POSITION) )
					{
						m_menuModel->getDataModel()->setLanguage("en");
						m_text->updateWholeText();
					}
					else if ( m_frenchLangRadioButton->getGlobalBounds().contains(MOUSE_POSITION) )
					{
						m_menuModel->getDataModel()->setLanguage("fr");
						m_text->updateWholeText();
					}
					else if ( m_spanishLangRadioButton->getGlobalBounds().contains(MOUSE_POSITION) )
					{
						m_menuModel->getDataModel()->setLanguage("es");
						m_text->updateWholeText();
					}
					else if ( m_normalQuestRadioButton->getGlobalBounds().contains(MOUSE_POSITION) )
					{
						m_model->setDifficulty(0);
					}
					else if ( m_masterQuestRadioButton->getGlobalBounds().contains(MOUSE_POSITION) )
					{
						m_model->setDifficulty(2);
					}
				}
			}

            //Leaderboard Screen
            else if (m_menuModel->getLeaderboardState() == true)
            {
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                {
                    if ( m_homeFormButton->getGlobalBounds().contains(MOUSE_POSITION) )
                    {
                        m_homeFormButton->setPressedState(true);
                    }
                    if ( m_clearLbRectButton->getGlobalBounds().contains(MOUSE_POSITION) )
                    {
                        m_clearLbRectButton->setPressedState(true);
                    }
                }

                if (event.type == sf::Event::MouseButtonReleased)
                {
                    m_homeFormButton->setPressedState(false);
                    m_clearLbRectButton->setPressedState(false);

                    if ( m_homeFormButton->getGlobalBounds().contains(MOUSE_POSITION) )
                    {
                        m_menuModel->setSettingsState(false);
                        m_menuModel->setHomeState(true);
                    }
                    if ( m_clearLbRectButton->getGlobalBounds().contains(MOUSE_POSITION) )
                    {
                        m_menuModel->getLeaderboard()->createFile();
                    }
                }
            }
		}
	}
	return result;
}
