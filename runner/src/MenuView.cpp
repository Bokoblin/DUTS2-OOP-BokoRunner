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
		m_window->setPosition(sf::Vector2i( (sf::VideoMode::getDesktopMode().width - m_width)/2, (sf::VideoMode::getDesktopMode().height - m_height)/2 ));
	}

	loadImages();
}


/********************************************
    Destructor
*********************************************
    @author Arthur  @date 26/02 - 15/04
*********************************************/
MenuView::~MenuView()
{
	//=== Home Elements

	delete m_farBackground;
	delete m_nearBackground;
	delete m_titleGraphic;
	delete m_playButtonGraphic;
	delete m_quitButtonGraphic;
	delete m_settingsButtonGraphic;

	//=== Settings Elements

	delete m_homeButtonGraphic;
	delete m_langEnRadioGraphic;
	delete m_langFrRadioGraphic;
	delete m_langEsRadioGraphic;
	delete m_difNormalRadioGraphic;
	delete m_difMasterRadioGraphic;
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
    @author Arthur  @date 26/03 - 14/04
*********************************************/
void MenuView::loadImages()
{
	if (!m_farBackgroundTexture.loadFromFile(BACKGROUND_IMAGE_2))
		cerr << "ERROR when loading image file: " << BACKGROUND_IMAGE_2 << endl;
	else
	{
		m_farBackgroundTexture.setSmooth(true);
		m_farBackground = new SlidingBackground(m_farBackgroundTexture, 1200, m_height, 1);
	}

	if (!m_nearBackgroundTexture.loadFromFile(BACKGROUND_IMAGE_1))
		cerr << "ERROR when loading image file: " << BACKGROUND_IMAGE_1 << endl;
	else
	{
		m_nearBackgroundTexture.setSmooth(true);
		m_nearBackground = new SlidingBackground(m_nearBackgroundTexture, 1200, m_height, 2);
	}

	if (!m_titleTexture.loadFromFile(TITLE_IMAGE) )
		cerr << "ERROR when loading image file: " << TITLE_IMAGE << endl;
	else
	{
		m_titleTexture.setSmooth(true);
		m_titleGraphic = new GraphicElement(m_titleTexture, m_width/2-200, m_height/6, 400, 200);
	}

	if (!m_playButtonTexture.loadFromFile(BUTTONS_IMAGE) )
		cerr << "ERROR when loading image file: " << BUTTONS_IMAGE << endl;
	else
	{
		std::vector<sf::IntRect> clip_rects;
		clip_rects.push_back(sf::IntRect( 0, 0, 150, 80));
		clip_rects.push_back(sf::IntRect(151, 0, 150, 80));

		m_playButtonTexture.setSmooth(true);
		m_playButtonGraphic = new Button(clip_rects, m_playButtonTexture, m_width/2-75, m_height/1.5, 150, 80, false);
	}

	if (!m_quitButtonTexture.loadFromFile(BUTTONS_IMAGE) )
		cerr << "ERROR when loading image file: " << BUTTONS_IMAGE << endl;
	else
	{
		std::vector<sf::IntRect> clip_rects;
		clip_rects.push_back(sf::IntRect( 0, 0, 150, 80));
		clip_rects.push_back(sf::IntRect(151, 0, 150, 80));

		m_quitButtonTexture.setSmooth(true);
		m_quitButtonGraphic = new Button(clip_rects, m_quitButtonTexture, m_width/2-75, m_height/1.2, 150, 80, false);
	}

	if (!m_settingsButtonTexture.loadFromFile(SETTINGS_BUTTONS_IMAGE) )
		cerr << "ERROR when loading image file: " << SETTINGS_BUTTONS_IMAGE << endl;
	else
	{
		std::vector<sf::IntRect> clip_rects;
		clip_rects.push_back(sf::IntRect( 0, 0, 50, 50));
		clip_rects.push_back(sf::IntRect( 51, 0, 50, 50));

		m_settingsButtonTexture.setSmooth(true);
		m_settingsButtonGraphic = new Button(clip_rects, m_settingsButtonTexture, 20, 530, 50, 50, false);
	}

	if (!m_homeButtonTexture.loadFromFile(SETTINGS_BUTTONS_IMAGE) )
		cerr << "ERROR when loading image file: " << SETTINGS_BUTTONS_IMAGE << endl;
	else
	{
		std::vector<sf::IntRect> clip_rects;
		clip_rects.push_back(sf::IntRect( 0, 50, 50, 50));
		clip_rects.push_back(sf::IntRect( 51, 50, 50, 50));

		m_homeButtonTexture.setSmooth(true);
		m_homeButtonGraphic = new Button(clip_rects, m_homeButtonTexture, 10, 10, 50, 50, false);
	}

	if (!m_radioTexture.loadFromFile(RADIOS_IMAGE) )
		cerr << "ERROR when loading image file: " << RADIOS_IMAGE << endl;
	else
	{
		std::vector<sf::IntRect> clip_rects;
		clip_rects.push_back(sf::IntRect(  0,   0, 50, 50) );
		clip_rects.push_back(sf::IntRect(50,   0, 50, 50) );
		clip_rects.push_back(sf::IntRect(  0, 50, 50, 50) );
		clip_rects.push_back(sf::IntRect(50, 50, 50, 50) );

		m_radioTexture.setSmooth(true);
		m_langEnRadioGraphic = new Button(clip_rects, m_radioTexture, 50, 205, 50, 50, true);
		m_langFrRadioGraphic = new Button(clip_rects, m_radioTexture, 50, 245, 50, 50, true);
		m_langEsRadioGraphic = new Button(clip_rects, m_radioTexture, 50, 285, 50, 50, true);
		m_difNormalRadioGraphic = new Button(clip_rects, m_radioTexture, 50, 420, 50, 50, true);
		m_difMasterRadioGraphic = new Button(clip_rects, m_radioTexture, 50, 460, 50, 50, true);
	}
}



/********************************************
    Synchronization function
*********************************************
    @author Arthur  @date 26/03 - 14/04
*********************************************/
void MenuView::synchronize()
{
	if (m_menuModel->getHomeState() == true)
	{
		//=== Elements update

		m_titleGraphic->resize(400,200);
		m_farBackground->sync();
		m_nearBackground->sync();
		m_playButtonGraphic->sync();
		m_quitButtonGraphic->sync();
		m_settingsButtonGraphic->sync();

		//=== Text update

		m_text->syncMenuHomeText(m_width, m_height);

	}
	else if (m_menuModel->getSettingsState() == true)
	{
		//=== Elements update

		m_langEnRadioGraphic->setActivatedState(m_model->getLanguage() == "en");
		m_langFrRadioGraphic->setActivatedState(m_model->getLanguage() == "fr");
		m_langEsRadioGraphic->setActivatedState(m_model->getLanguage() == "es");
		m_difNormalRadioGraphic->setActivatedState(m_model->getDifficulty() == 0);
		m_difMasterRadioGraphic->setActivatedState(m_model->getDifficulty() != 0);
		m_homeButtonGraphic->sync();
		m_langEnRadioGraphic->sync();
		m_langFrRadioGraphic->sync();
		m_langEsRadioGraphic->sync();
		m_difNormalRadioGraphic->sync();
		m_difMasterRadioGraphic->sync();
		m_homeButtonGraphic->resize(30, 30);
		m_langEnRadioGraphic->resize(25, 25);
		m_langFrRadioGraphic->resize(25, 25);
		m_langEsRadioGraphic->resize(25, 25);
		m_difNormalRadioGraphic->resize(25, 25);
		m_difMasterRadioGraphic->resize(25, 25);

		//=== Text update

		m_text->syncMenuSettingsText(m_width, m_height);

	}
}


/********************************************
    View Drawing
*********************************************
    @author Arthur  @date 26/03 - 14/04
*********************************************/
void MenuView::draw() const
{
	m_window->clear();

	if (m_menuModel->getHomeState() == true)
	{
		//=== Graphic Elements drawing

		m_farBackground->draw(m_window);
		m_nearBackground->draw(m_window);
		m_window->draw(*m_titleGraphic);
		m_window->draw(*m_playButtonGraphic);
		m_window->draw(*m_quitButtonGraphic);
		m_window->draw(*m_settingsButtonGraphic);

		//=== Text Drawing

		m_text->drawMenuHomeText(m_window);

	}
	else if (m_menuModel->getSettingsState() == true)
	{
		m_window->clear(sf::Color(51, 51, 51, 255) );

		//=== Graphic Elements drawing

		m_window->draw(*m_homeButtonGraphic);
		m_window->draw(*m_langEnRadioGraphic);
		m_window->draw(*m_langFrRadioGraphic);
		m_window->draw(*m_langEsRadioGraphic);
		m_window->draw(*m_difNormalRadioGraphic);
		m_window->draw(*m_difMasterRadioGraphic);

		//=== Text Drawing

		m_text->drawMenuSettingsText(m_window);
	}

	m_window->display();
}


/********************************************
    Events treating
*********************************************
    @author Arthur  @date 25/03 - 14/04
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
					if ( m_playButtonGraphic->getGlobalBounds().contains(MOUSE_POSITION) )
					{
						m_playButtonGraphic->setPressedState(true);
					}
					else if ( m_quitButtonGraphic->getGlobalBounds().contains(MOUSE_POSITION) )
					{
						m_quitButtonGraphic->setPressedState(true);
					}
					else if ( m_settingsButtonGraphic->getGlobalBounds().contains(MOUSE_POSITION) )
					{
						m_settingsButtonGraphic->setPressedState(true);
					}
				}

				if (event.type == sf::Event::MouseButtonReleased)
				{
					m_playButtonGraphic->setPressedState(false);
					m_quitButtonGraphic->setPressedState(false);
					m_settingsButtonGraphic->setPressedState(false);

					if ( m_playButtonGraphic->getGlobalBounds().contains(MOUSE_POSITION) )
					{
						m_model->setMenuState(false);
						m_model->setGameState(true);
						result = false;
					}
					else if ( m_quitButtonGraphic->getGlobalBounds().contains(MOUSE_POSITION) )
					{
						m_window->close();
						result = false;
					}
					else if ( m_settingsButtonGraphic->getGlobalBounds().contains(MOUSE_POSITION) )
					{
						m_menuModel->setHomeState(false);
						m_menuModel->setSettingsState(true);
					}
				}
			}

			//Settings Screen

			else if (m_menuModel->getSettingsState() == true)
			{
				if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
				{
					if ( m_homeButtonGraphic->getGlobalBounds().contains(MOUSE_POSITION) )
					{
						m_homeButtonGraphic->setPressedState(true);
					}
					else if ( m_langEnRadioGraphic->getGlobalBounds().contains(MOUSE_POSITION) )
					{
						m_langEnRadioGraphic->setPressedState(true);
					}
					else if ( m_langFrRadioGraphic->getGlobalBounds().contains(MOUSE_POSITION) )
					{
						m_langFrRadioGraphic->setPressedState(true);
					}
					else if ( m_langEsRadioGraphic->getGlobalBounds().contains(MOUSE_POSITION) )
					{
						m_langEsRadioGraphic->setPressedState(true);
					}
					else if ( m_difNormalRadioGraphic->getGlobalBounds().contains(MOUSE_POSITION) )
					{
						m_difNormalRadioGraphic->setPressedState(true);
					}
					else if ( m_difMasterRadioGraphic->getGlobalBounds().contains(MOUSE_POSITION) )
					{
						m_difMasterRadioGraphic->setPressedState(true);
					}
				}

				if (event.type == sf::Event::MouseButtonReleased)
				{
					m_homeButtonGraphic->setPressedState(false);
					m_langEnRadioGraphic->setPressedState(false);
					m_langFrRadioGraphic->setPressedState(false);
					m_langEsRadioGraphic->setPressedState(false);
					m_difNormalRadioGraphic->setPressedState(false);
					m_difMasterRadioGraphic->setPressedState(false);

					if ( m_homeButtonGraphic->getGlobalBounds().contains(MOUSE_POSITION) )
					{
						m_menuModel->setSettingsState(false);
						m_menuModel->setHomeState(true);
					}
					else if ( m_langEnRadioGraphic->getGlobalBounds().contains(MOUSE_POSITION) )
					{
						m_model->setLanguage("en");
						m_text->changeLanguage(m_model->getLanguage());
					}
					else if ( m_langFrRadioGraphic->getGlobalBounds().contains(MOUSE_POSITION) )
					{
						m_model->setLanguage("fr");
						m_text->changeLanguage(m_model->getLanguage());
					}
					else if ( m_langEsRadioGraphic->getGlobalBounds().contains(MOUSE_POSITION) )
					{
						m_model->setLanguage("es");
						m_text->changeLanguage(m_model->getLanguage());
					}
					else if ( m_difNormalRadioGraphic->getGlobalBounds().contains(MOUSE_POSITION) )
					{
						m_model->setDifficulty(0);
					}
					else if ( m_difMasterRadioGraphic->getGlobalBounds().contains(MOUSE_POSITION) )
					{
						m_model->setDifficulty(2);
					}
				}
			}
		}
	}
	return result;
}
