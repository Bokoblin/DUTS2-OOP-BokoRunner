#include "MenuView.h"

using namespace std;

/**
 * Parameterized Constructor
 * @author Arthur, Florian
 * @date 25/02/16 - 24/01/17
 */
MenuView::MenuView(float w, float h, sf::RenderWindow *window, TextHandler * textHandler):
        View(w, h, window,textHandler), m_menuModel{nullptr}, m_commandsView{nullptr},
        m_leaderboardView{nullptr}, m_settingsView{nullptr},  m_shopView{nullptr}
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
 * @date 26/02/16 - 21/05/17
 */
MenuView::~MenuView()
{
    delete m_farBackground;
    delete m_nearBackground;
    delete m_titleGraphic;
    delete m_playRectButton;
    delete m_quitRectButton;
    delete m_commandsFormButton;
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
 * @date 26/03/16 - 24/01/17
 */
void MenuView::loadImages()
{
    m_farBackground = new SlidingBackground(1200, m_height, 1, DEFAULT_FAR_HILL_BACKGROUND);
    m_nearBackground = new SlidingBackground(1200, m_height, 2, DEFAULT_NEAR_HILL_BACKGROUND);

    m_titleGraphic = new GraphicElement(m_width/2-200, m_height/6, 400, 200, TITLE_IMAGE);
    m_titleGraphic->resize(400,200);

    //=== Initialize PLAY and QUIT buttons

    vector<sf::IntRect> clipRectPlay;
    clipRectPlay.push_back(sf::IntRect( 0, 0, 150, 80));
    clipRectPlay.push_back(sf::IntRect(151, 0, 150, 80));
    m_playRectButton = new Button(m_width/2-75, (float) (m_height / 1.5), 150, 80, "menu_play_button",
                                  RECT_BUTTONS_IMAGE, clipRectPlay);

    vector<sf::IntRect> clipRectQuit;
    clipRectQuit.push_back(sf::IntRect( 0, 0, 150, 80));
    clipRectQuit.push_back(sf::IntRect(151, 0, 150, 80));
    m_quitRectButton = new Button(m_width/2-75, (float) (m_height / 1.2), 150, 80, "menu_quit_button",
                                  RECT_BUTTONS_IMAGE, clipRectQuit);


    //=== Initialize COMMANDS, SETTINGS, LEADERBOARD and SHOP form buttons

    vector<sf::IntRect> clipRectCommands;
    clipRectCommands.push_back(sf::IntRect( 0, 200, 50, 50));
    clipRectCommands.push_back(sf::IntRect( 51, 200, 50, 50));
    m_commandsFormButton = new Button(20, 10, 50, 50, SHAPE_BUTTONS_IMAGE, clipRectCommands);

    vector<sf::IntRect> clipRectSettings;
    clipRectSettings.push_back(sf::IntRect( 0, 0, 50, 50));
    clipRectSettings.push_back(sf::IntRect( 51, 0, 50, 50));
    m_settingsFormButton = new Button(20, 530, 50, 50, SHAPE_BUTTONS_IMAGE, clipRectSettings);

    vector<sf::IntRect> clipRectLeaderboard;
    clipRectLeaderboard.push_back(sf::IntRect( 0, 100, 50, 50));
    clipRectLeaderboard.push_back(sf::IntRect( 51, 100, 50, 50));
    m_leaderboardFormButton = new Button(830, 530, 50, 50, SHAPE_BUTTONS_IMAGE, clipRectLeaderboard);

    vector<sf::IntRect> clipRectShop;
    clipRectShop.push_back(sf::IntRect( 0, 150, 50, 50));
    clipRectShop.push_back(sf::IntRect( 51, 150, 50, 50));
    m_shopFormButton = new Button(830, 10, 50, 50, SHAPE_BUTTONS_IMAGE, clipRectShop);
}


/**
 * Synchronization function
 * @author Arthur
 * @date 26/03/16 - 24/01/17
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
        m_commandsFormButton->sync();
        m_settingsFormButton->sync();
        m_leaderboardFormButton->sync();
        m_shopFormButton->sync();

        //=== TextHandler update
        m_textHandler->syncMenuHomeText();
    }
    else if (m_menuModel->getMenuState() == COMMANDS)
        m_commandsView->synchronize();

    else if (m_menuModel->getMenuState() == LEADERBOARD)
        m_leaderboardView->synchronize();

    else if (m_menuModel->getMenuState() == SETTINGS)
        m_settingsView->synchronize();

    else if (m_menuModel->getMenuState() == SHOP)
        m_shopView->synchronize();

    //=== Delete commandsView if not anymore current menu state
    if ( m_menuModel->getMenuState() != COMMANDS && m_commandsView != nullptr)
    {
        delete m_commandsView;
        m_commandsView = nullptr;
    }

    //=== Delete leaderboardView if not anymore current menu state
    if ( m_menuModel->getMenuState() != LEADERBOARD && m_leaderboardView != nullptr)
    {
        delete m_leaderboardView;
        m_leaderboardView = nullptr;
    }

    //=== Delete settingsView if not anymore current menu state
    if ( m_menuModel->getMenuState() != SETTINGS && m_settingsView != nullptr)
    {
        delete m_settingsView;
        m_settingsView = nullptr;
    }

    //=== Delete shopView if not anymore current menu state
    if ( m_menuModel->getMenuState() != SHOP && m_shopView != nullptr)
    {
        delete m_shopView;
        m_shopView = nullptr;
    }
}


/**
 * Menu View Drawing
 * @author Arthur
 * @date 26/03/16 - 24/01/17
 */
void MenuView::draw() const
{
    if (m_menuModel->getMenuState() == HOME)
    {
        m_window->clear();

        m_farBackground->draw(m_window);
        m_nearBackground->draw(m_window);
        m_window->draw(*m_titleGraphic);
        m_playRectButton->draw(m_window);
        m_quitRectButton->draw(m_window);
        m_window->draw(*m_commandsFormButton);
        m_window->draw(*m_settingsFormButton);
        m_window->draw(*m_leaderboardFormButton);
        m_window->draw(*m_shopFormButton);

        m_window->display();
    }
    else if (m_menuModel->getMenuState() == COMMANDS)
        m_commandsView->draw();

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
 * @date 25/03/16 - 24/01/17
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

                    else if ( m_commandsFormButton->contains(MOUSE_POSITION) )
                        m_commandsFormButton->setPressed(true);

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
                    m_commandsFormButton->setPressed(false);
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
                    else if ( m_commandsFormButton->contains(MOUSE_POSITION) )
                    {
                        m_commandsView = new CommandsView(m_width, m_height, m_window, m_textHandler);
                        m_commandsView->setCommandsModel(m_menuModel->launchCommands());
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
            else if ( (m_menuModel->getMenuState() == COMMANDS && m_commandsView->treatEvents(event))
                    ||(m_menuModel->getMenuState() == LEADERBOARD && m_leaderboardView->treatEvents(event) )
                    ||(m_menuModel->getMenuState() == SETTINGS && m_settingsView->treatEvents(event))
                    ||(m_menuModel->getMenuState() == SHOP && m_shopView->treatEvents(event) )
                    )
            {
                m_menuModel->setMenuState(HOME);
            }
        }
    }
    return result;
}
