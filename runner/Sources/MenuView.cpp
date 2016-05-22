#include "MenuView.h"

using namespace std;

/********************************************
    Parameterized Constructor
*********************************************
    @author Arthur  @date 25/02 - 21/05
    @author Florian @date 22/04 - 06/05
*********************************************/
MenuView::MenuView(float w, float h, sf::RenderWindow *window, Text * text):
    View(w, h, window,text), m_menuModel{nullptr}, m_leaderboardView{nullptr},
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
        m_window->create( sf::VideoMode(w, h, SCREEN_BPP), APP_TITLE, sf::Style::Close );
		m_window->setFramerateLimit(FRAMERATE);
		m_window->setPosition(sf::Vector2i( (sf::VideoMode::getDesktopMode().width - m_width)/2,
				(sf::VideoMode::getDesktopMode().height - m_height)/2 ));
	}

	loadImages();
}


/********************************************
    Destructor
*********************************************
    @author Arthur  @date 26/02 - 21/05
*********************************************/
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
    @author Arthur  @date 26/03 - 16/05
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

	//=== Initialize PLAY and QUIT buttons

	if (!m_menuRectButtonsTexture.loadFromFile(MENU_RECT_BUTTONS_IMAGE) )
		cerr << "ERROR when loading image file: " << MENU_RECT_BUTTONS_IMAGE << endl;
	else
	{
        m_menuRectButtonsTexture.setSmooth(true);

		vector<sf::IntRect> clip_rects_play;
		clip_rects_play.push_back(sf::IntRect( 0, 0, 150, 80));
		clip_rects_play.push_back(sf::IntRect(151, 0, 150, 80));
		m_playRectButton = new Button(clip_rects_play, m_menuRectButtonsTexture, m_width/2-75, m_height/1.5, 150, 80, false);

		vector<sf::IntRect> clip_rects_quit;
		clip_rects_quit.push_back(sf::IntRect( 0, 0, 150, 80));
		clip_rects_quit.push_back(sf::IntRect(151, 0, 150, 80));
		m_quitRectButton = new Button(clip_rects_quit, m_menuRectButtonsTexture, m_width/2-75, m_height/1.2, 150, 80, false);
    }

    //=== Initialize SETTINGS, LEADERBOARD and SHOP form buttons

	if (!m_menuFormButtonsTexture.loadFromFile(FORM_BUTTONS_IMAGE) )
		cerr << "ERROR when loading image file: " << FORM_BUTTONS_IMAGE << endl;
	else
	{
		m_menuFormButtonsTexture.setSmooth(true);

		vector<sf::IntRect> clip_rects_settings;
		clip_rects_settings.push_back(sf::IntRect( 0, 0, 50, 50));
		clip_rects_settings.push_back(sf::IntRect( 51, 0, 50, 50));
		m_settingsFormButton = new Button(clip_rects_settings, m_menuFormButtonsTexture, 20, 530, 50, 50, false);

        vector<sf::IntRect> clip_rects_lb;
        clip_rects_lb.push_back(sf::IntRect( 0, 100, 50, 50));
        clip_rects_lb.push_back(sf::IntRect( 51, 100, 50, 50));
        m_leaderboardFormButton = new Button(clip_rects_lb, m_menuFormButtonsTexture, 830, 530, 50, 50, false);

        vector<sf::IntRect> clip_rects_shop;
        clip_rects_shop.push_back(sf::IntRect( 0, 150, 50, 50));
        clip_rects_shop.push_back(sf::IntRect( 51, 150, 50, 50));
        m_shopFormButton = new Button(clip_rects_shop, m_menuFormButtonsTexture, 830, 10, 50, 50, false);
	}
}


/********************************************
    Synchronization function
*********************************************
    @author Arthur  @date 26/03 - 21/05
*********************************************/
void MenuView::synchronize()
{
    if ( m_menuMusic.getPlayingOffset() >= sf::milliseconds(28840))
        m_menuMusic.setPlayingOffset( sf::milliseconds(4851));

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
        m_shopFormButton->sync();

		//=== Text update
		m_text->syncMenuHomeText(m_width, m_height);
	}
    else if (m_menuModel->getLeaderboardState())
        m_leaderboardView->synchronize();

	else if (m_menuModel->getSettingsState())
        m_settingsView->synchronize();

    else if (m_menuModel->getShopState())
        m_shopView->synchronize();

    //=== Delete leaderboardView if not anymore in leaderboardState
    if ( !m_menuModel->getLeaderboardState() && m_leaderboardView != nullptr)
    {
        delete m_leaderboardView;
        m_leaderboardView = nullptr;
    }

    //=== Delete settingsView if not anymore in shopState
    if ( !m_menuModel->getSettingsState() && m_settingsView != nullptr)
    {
        delete m_settingsView;
        m_settingsView = nullptr;
    }

    //=== Delete shopView if not anymore in shopState
    if ( !m_menuModel->getShopState() && m_shopView != nullptr)
    {
        delete m_shopView;
        m_shopView = nullptr;
    }
}


/********************************************
    Menu View Drawing
*********************************************
    @author Arthur  @date 26/03 - 21/05
*********************************************/
void MenuView::draw() const
{
	if (m_menuModel->getHomeState())
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
        m_window->draw(*m_shopFormButton);

		//=== Text Drawing
		m_text->drawMenuHomeText(m_window);

        m_window->display();
	}
	else if (m_menuModel->getSettingsState())
        m_settingsView->draw();

    else if (m_menuModel->getLeaderboardState())
        m_leaderboardView->draw();

    else if (m_menuModel->getShopState())
        m_shopView->draw();

}


/********************************************
    Events treating
*********************************************
    @author Arthur  @date 25/03 - 21/05
    @author Florian @date 22/04 - 06/05
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

            //=== Home Events

			if (m_menuModel->getHomeState() == true)
			{
                if (MOUSE_LEFT_PRESSED_EVENT)
				{
					if ( m_playRectButton->IS_POINTED )
						m_playRectButton->setPressedState(true);

					else if ( m_quitRectButton->IS_POINTED )
						m_quitRectButton->setPressedState(true);

					else if ( m_settingsFormButton->IS_POINTED )
						m_settingsFormButton->setPressedState(true);

                    else if ( m_leaderboardFormButton->IS_POINTED )
                        m_leaderboardFormButton->setPressedState(true);

                    else if ( m_shopFormButton->IS_POINTED )
                        m_shopFormButton->setPressedState(true);
				}

				if (event.type == sf::Event::MouseButtonReleased)
				{
					m_playRectButton->setPressedState(false);
					m_quitRectButton->setPressedState(false);
					m_settingsFormButton->setPressedState(false);
                    m_leaderboardFormButton->setPressedState(false);
                    m_shopFormButton->setPressedState(false);

					if ( m_playRectButton->IS_POINTED )
					{
                        if(m_menuMusic.getStatus() == sf::Music::Status::Playing )
                            m_menuMusic.stop();
						m_model->setMenuState(false);
						m_model->setGameState(true);
						result = false;
					}
					else if ( m_quitRectButton->IS_POINTED )
					{
						m_window->close();
						result = false;
					}
                    else if ( m_leaderboardFormButton->IS_POINTED )
                    {
                        m_leaderboardView = new LeaderboardView(m_width, m_height, m_window, m_text);
                        m_leaderboardView->setLeaderboardModel( m_menuModel->launchLeaderboard() );
                    }
					else if ( m_settingsFormButton->IS_POINTED )
					{
                        m_settingsView = new SettingsView(m_width, m_height, m_window, m_text);
                        m_settingsView->setModel(m_model);
                        m_settingsView->setSettingsModel( m_menuModel->launchSettings() );
					}
                    else if ( m_shopFormButton->IS_POINTED )
                    {
                        m_shopView = new ShopView(m_width, m_height, m_window, m_text);
                        m_shopView->setShopModel( m_menuModel->launchShop() );
                    }
				}
			}

            //=== Leaderboard Events

            //if treatEvents return true == if leaderboard is stopping
            else if (m_menuModel->getLeaderboardState()
                     && m_leaderboardView->treatEvents(event))
            {
                m_menuModel->setLeaderboardState(false);
                m_menuModel->setHomeState(true);
            }

            //=== Settings Events

            else if (m_menuModel->getSettingsState()
                     && m_settingsView->treatEvents(event))
            {
                m_menuModel->setSettingsState(false);
                m_menuModel->setHomeState(true);
            }

            //=== Shop Events

            else if (m_menuModel->getShopState()
                     && m_shopView->treatEvents(event))
            {
                m_menuModel->setShopState(false);
                m_menuModel->setHomeState(true);
            }
		}
	}
	return result;
}
