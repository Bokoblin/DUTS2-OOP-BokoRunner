#include "MenuView.h"

using namespace std;

/**
 * Parameterized Constructor
 * @author Arthur, Florian
 * @date 25/02 - 21/05
 */
MenuView::MenuView(float w, float h, sf::RenderWindow *window, TextHandler * textHandler):
    View(w, h, window,textHandler), m_menuModel{nullptr}, m_leaderboardView{nullptr},
    m_settingsView{nullptr},  m_shopView{nullptr}
{
    if (!m_menuMusic.openFromFile(MENU_MUSIC))
        cerr << "ERROR when loading music file: " << MENU_MUSIC << endl;
    else
    {
        m_menuMusic.play();
        m_menuMusic.setLoop(true);
        m_menuMusic.setAttenuation(50);
    }

	if (m_window->getSize().x != m_width )
	{
        m_window->create(sf::VideoMode((unsigned int) w, (unsigned int) h, SCREEN_BPP), APP_TITLE, sf::Style::Close );
		m_window->setFramerateLimit(FRAMERATE);
		m_window->setPosition(ENV_CENTERED);
	}

	loadImages();
}


/**
 * Destructor
 * @author Arthur
 * @date 26/02 - 21/05
 */
MenuView::~MenuView()
{
	delete m_farBackground;
	delete m_nearBackground;
	delete m_titleGraphic;
	delete m_playRectButton;
	delete m_quitRectButton;
	delete m_settingsFormButton;
    delete m_leaderboardFormButton;
    delete m_shopFormButton;
}


//=== Setters

void MenuView::setMenuModel(MenuModel *model)
{
	m_menuModel = model;
}


/**
 * Image Loading
 * @author Arthur
 * @date 26/03 - 23/12
 */
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
		m_titleGraphic->resize(400,200);
	}

	//=== Initialize PLAY and QUIT buttons

	if (!m_menuRectButtonsTexture.loadFromFile(MENU_RECT_BUTTONS_IMAGE) )
		cerr << "ERROR when loading image file: " << MENU_RECT_BUTTONS_IMAGE << endl;
	else
	{
        m_menuRectButtonsTexture.setSmooth(true);

		vector<sf::IntRect> clipRectPlay;
		clipRectPlay.push_back(sf::IntRect( 0, 0, 150, 80));
		clipRectPlay.push_back(sf::IntRect(151, 0, 150, 80));
		m_playRectButton = new Button(clipRectPlay, m_menuRectButtonsTexture,
                          m_width/2-75, (float) (m_height/1.5), 150, 80, "menu_play_button");

		vector<sf::IntRect> clipRectQuit;
		clipRectQuit.push_back(sf::IntRect( 0, 0, 150, 80));
		clipRectQuit.push_back(sf::IntRect(151, 0, 150, 80));
		m_quitRectButton = new Button(clipRectQuit, m_menuRectButtonsTexture,
                          m_width/2-75, (float) (m_height/1.2), 150, 80, "menu_quit_button");
    }

    //=== Initialize SETTINGS, LEADERBOARD and SHOP form buttons

	if (!m_menuFormButtonsTexture.loadFromFile(FORM_BUTTONS_IMAGE) )
		cerr << "ERROR when loading image file: " << FORM_BUTTONS_IMAGE << endl;
	else
	{
		m_menuFormButtonsTexture.setSmooth(true);

		vector<sf::IntRect> clipRectSettings;
		clipRectSettings.push_back(sf::IntRect( 0, 0, 50, 50));
		clipRectSettings.push_back(sf::IntRect( 51, 0, 50, 50));
		m_settingsFormButton = new Button(clipRectSettings, m_menuFormButtonsTexture, 20, 530, 50, 50);

        vector<sf::IntRect> clipRectLeaderboard;
        clipRectLeaderboard.push_back(sf::IntRect( 0, 100, 50, 50));
        clipRectLeaderboard.push_back(sf::IntRect( 51, 100, 50, 50));
        m_leaderboardFormButton = new Button(clipRectLeaderboard, m_menuFormButtonsTexture, 830, 530, 50, 50);

        vector<sf::IntRect> clipRectShop;
        clipRectShop.push_back(sf::IntRect( 0, 150, 50, 50));
        clipRectShop.push_back(sf::IntRect( 51, 150, 50, 50));
        m_shopFormButton = new Button(clipRectShop, m_menuFormButtonsTexture, 830, 10, 50, 50);
	}
}


/**
 * Synchronization function
 * @author Arthur
 * @date 26/03 - 20/12
 */
void MenuView::synchronize()
{
    if ( m_menuMusic.getPlayingOffset() >= sf::milliseconds(28840))
        m_menuMusic.setPlayingOffset( sf::milliseconds(4851));

	if (m_menuModel->getMenuState() == HOME)
	{
		//=== Elements update
		m_farBackground->sync();
		m_nearBackground->sync();
		m_playRectButton->sync(m_menuModel->getDataBase());
		m_quitRectButton->sync(m_menuModel->getDataBase());
		m_settingsFormButton->sync();
        m_leaderboardFormButton->sync();
        m_shopFormButton->sync();

		//=== TextHandler update
		m_textHandler->syncMenuHomeText();
	}
    else if (m_menuModel->getMenuState() == LEADERBOARD)
        m_leaderboardView->synchronize();

	else if (m_menuModel->getMenuState() == SETTINGS)
        m_settingsView->synchronize();

    else if (m_menuModel->getMenuState() == SHOP)
        m_shopView->synchronize();

    //=== Delete leaderboardView if not anymore in leaderboardState
    if ( m_menuModel->getMenuState() != LEADERBOARD && m_leaderboardView != nullptr)
    {
        delete m_leaderboardView;
        m_leaderboardView = nullptr;
    }

    //=== Delete settingsView if not anymore in shopState
    if ( m_menuModel->getMenuState() != SETTINGS && m_settingsView != nullptr)
    {
        delete m_settingsView;
        m_settingsView = nullptr;
    }

    //=== Delete shopView if not anymore in shopState
    if ( m_menuModel->getMenuState() != SHOP && m_shopView != nullptr)
    {
        delete m_shopView;
        m_shopView = nullptr;
    }
}


/**
 * Menu View Drawing
 * @author Arthur
 * @date 26/03 - 20/12
 */
void MenuView::draw() const
{
	if (m_menuModel->getMenuState() == HOME)
	{
		m_window->clear();

		//=== Graphic Elements drawing
		m_farBackground->draw(m_window);
		m_nearBackground->draw(m_window);
		m_window->draw(*m_titleGraphic);
        m_playRectButton->draw(m_window);
		m_quitRectButton->draw(m_window);
		m_window->draw(*m_settingsFormButton);
        m_window->draw(*m_leaderboardFormButton);
        m_window->draw(*m_shopFormButton);

		//=== TextHandler Drawing
		m_textHandler->drawMenuHomeText(m_window);

        m_window->display();
	}
	else if (m_menuModel->getMenuState() == SETTINGS)
        m_settingsView->draw();

    else if (m_menuModel->getMenuState() == LEADERBOARD)
        m_leaderboardView->draw();

    else if (m_menuModel->getMenuState() == SHOP)
        m_shopView->draw();

}


/**
 * Events treating
 * @author Arthur, Florian
 * @date 25/03 - 20/12
 */
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
				m_model->setAppState(QUIT);
				m_window->close();
				result = false;
			}

			if (m_menuModel->getMenuState() == HOME)
			{
                if (MOUSE_LEFT_PRESSED_EVENT)
				{
					if ( m_playRectButton->contains(MOUSE_POSITION) )
                        m_playRectButton->setPressed(true);

					else if ( m_quitRectButton->contains(MOUSE_POSITION) )
                        m_quitRectButton->setPressed(true);

					else if ( m_settingsFormButton->contains(MOUSE_POSITION) )
                        m_settingsFormButton->setPressed(true);

                    else if ( m_leaderboardFormButton->contains(MOUSE_POSITION) )
                        m_leaderboardFormButton->setPressed(true);

                    else if ( m_shopFormButton->contains(MOUSE_POSITION) )
                        m_shopFormButton->setPressed(true);
				}

				if (event.type == sf::Event::MouseButtonReleased)
				{
                    m_playRectButton->setPressed(false);
                    m_quitRectButton->setPressed(false);
                    m_settingsFormButton->setPressed(false);
                    m_leaderboardFormButton->setPressed(false);
                    m_shopFormButton->setPressed(false);

					if ( m_playRectButton->contains(MOUSE_POSITION) )
					{
                        if(m_menuMusic.getStatus() == sf::Music::Status::Playing )
                            m_menuMusic.stop();
						m_model->setAppState(GAME);
						result = false;
					}
					else if ( m_quitRectButton->contains(MOUSE_POSITION) )
					{
						m_window->close();
						result = false;
					}
                    else if ( m_leaderboardFormButton->contains(MOUSE_POSITION) )
                    {
                        m_leaderboardView = new LeaderboardView(m_width, m_height, m_window, m_textHandler);
                        m_leaderboardView->setLeaderboardModel( m_menuModel->launchLeaderboard() );
                    }
					else if ( m_settingsFormButton->contains(MOUSE_POSITION) )
					{
                        m_settingsView = new SettingsView(m_width, m_height, m_window, m_textHandler);
                        m_settingsView->setModel(m_model);
                        m_settingsView->setSettingsModel( m_menuModel->launchSettings() );
					}
                    else if ( m_shopFormButton->contains(MOUSE_POSITION) )
                    {
                        m_shopView = new ShopView(m_width, m_height, m_window, m_textHandler);
                        m_shopView->setShopModel( m_menuModel->launchShop() );
                    }
				}
			}
            else if (m_menuModel->getMenuState() == LEADERBOARD && m_leaderboardView->treatEvents(event))
            {
                m_menuModel->setMenuState(HOME);
            }
            else if (m_menuModel->getMenuState() == SETTINGS && m_settingsView->treatEvents(event))
            {
                m_menuModel->setMenuState(HOME);
            }
            else if (m_menuModel->getMenuState() == SHOP && m_shopView->treatEvents(event))
            {
                m_menuModel->setMenuState(HOME);
            }
		}
	}
	return result;
}
