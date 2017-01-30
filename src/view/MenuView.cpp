#include "MenuView.h"

using namespace std;

/**
 * Constructs a Menu view with app's size for menu and game,
 * app's window, a text handler and menu's model
 * @author Arthur, Florian
 * @date 25/02/16 - 24/01/17
 *
 * @param width the app's width
 * @param height the app's height
 * @param window the app's window
 * @param textHandler a text handler to display standalone text
 * @param menuModel the menu's model part
 */
MenuView::MenuView(float width, float height, sf::RenderWindow *window,
                   TextHandler *textHandler, MenuModel *menuModel) :
        AbstractView(width, height, window, textHandler), m_menu{menuModel},
        m_commandsView{nullptr}, m_leaderboardView{nullptr}, m_settingsView{nullptr}, m_shopView{nullptr}
{
    if (!m_menuMusic.openFromFile(MENU_MUSIC))
        cerr << "ERROR when loading music file: " << MENU_MUSIC << endl;
    else
    {
        if (m_menu->getDataBase()->isMenuMusicEnabled())
            m_menuMusic.setVolume(100);
        else
            m_menuMusic.setVolume(0);
        m_menuMusic.play();
        m_menuMusic.setLoop(true);
        m_menuMusic.setAttenuation(50);
    }

    loadImages();

    if (m_window->getSize().x != m_width )
    {
        m_window->create(sf::VideoMode((unsigned int) m_width, (unsigned int) m_height, SCREEN_BPP),
                         APP_TITLE, sf::Style::Close );
        m_window->setFramerateLimit(30);
        m_window->setPosition(ENVIRONMENT_CENTER);
    }
}


/**
 * Destructor
 * @author Arthur
 * @date 26/02/16 - 21/05/16
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
 * @date 26/03/16 - 30/01/17
 */
void MenuView::synchronize()
{
    if (m_menu->getDataBase()->isMenuMusicEnabled())
        m_menuMusic.setVolume(100);
    else
        m_menuMusic.setVolume(0);

    if ( m_menuMusic.getPlayingOffset() >= sf::milliseconds(28840))
        m_menuMusic.setPlayingOffset( sf::milliseconds(4851));

    switch (m_menu->getMenuState())
    {
        case HOME:
            m_farBackground->sync();
            m_nearBackground->sync();
            m_playRectButton->sync(m_menu->getDataBase());
            m_quitRectButton->sync(m_menu->getDataBase());
            m_commandsFormButton->sync();
            m_settingsFormButton->sync();
            m_leaderboardFormButton->sync();
            m_shopFormButton->sync();
            m_textHandler->syncMenuHomeText();
            break;

        case COMMANDS:
            m_commandsView->synchronize();
            break;

        case LEADERBOARD:
            m_leaderboardView->synchronize();
            break;

        case SETTINGS:
            m_settingsView->synchronize();
            break;

        case SHOP:
            m_shopView->synchronize();
            break;

        default:
            break;
    }


    //=== Delete commandsView if not anymore current menu state
    if ( m_menu->getMenuState() != COMMANDS && m_commandsView != nullptr)
    {
        delete m_commandsView;
        m_commandsView = nullptr;
    }

    //=== Delete leaderboardView if not anymore current menu state
    if ( m_menu->getMenuState() != LEADERBOARD && m_leaderboardView != nullptr)
    {
        delete m_leaderboardView;
        m_leaderboardView = nullptr;
    }

    //=== Delete settingsView if not anymore current menu state
    if ( m_menu->getMenuState() != SETTINGS && m_settingsView != nullptr)
    {
        delete m_settingsView;
        m_settingsView = nullptr;
    }

    //=== Delete shopView if not anymore current menu state
    if ( m_menu->getMenuState() != SHOP && m_shopView != nullptr)
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
    if (m_menu->getMenuState() == HOME)
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
    else if (m_menu->getMenuState() == COMMANDS)
        m_commandsView->draw();

    else if (m_menu->getMenuState() == SETTINGS)
        m_settingsView->draw();

    else if (m_menu->getMenuState() == LEADERBOARD)
        m_leaderboardView->draw();

    else if (m_menu->getMenuState() == SHOP)
        m_shopView->draw();

}


/**
 * Events treating
 * @author Arthur, Florian
 * @date 25/03/16 - 29/01/17
 */
bool MenuView::treatEvents(sf::Event event)
{
    bool result = false;

    if(m_window->isOpen())
    {
        result = true;

        while (m_window->pollEvent(event))
        {
            if  (event.type == sf::Event::Closed)
            {
                m_menu->getDataBase()->setAppState(QUIT);
                m_window->close();
                result = false;
            }

            if (m_menu->getMenuState() == HOME)
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
                        m_menu->getDataBase()->setAppState(GAME);
                        result = false;
                    }
                    else if ( m_quitRectButton->contains(MOUSE_POSITION) )
                    {
                        m_window->close();
                        result = false;
                    }
                    else if ( m_commandsFormButton->contains(MOUSE_POSITION) )
                    {
                        m_commandsView = new CommandsView(m_window, m_textHandler, m_menu->launchCommands());
                    }
                    else if ( m_leaderboardFormButton->contains(MOUSE_POSITION) )
                    {
                        m_leaderboardView = new LeaderboardView(m_window, m_textHandler, m_menu->launchLeaderboard());
                    }
                    else if ( m_settingsFormButton->contains(MOUSE_POSITION) )
                    {
                        m_settingsView = new SettingsView(m_window, m_textHandler, m_menu->launchSettings());
                    }
                    else if ( m_shopFormButton->contains(MOUSE_POSITION) )
                    {
                        m_shopView = new ShopView(m_window, m_textHandler, m_menu->launchShop());
                    }
                }
            }
            else if ( (m_menu->getMenuState() == COMMANDS && m_commandsView->treatEvents(event))
                      ||(m_menu->getMenuState() == LEADERBOARD && m_leaderboardView->treatEvents(event) )
                      ||(m_menu->getMenuState() == SETTINGS && m_settingsView->treatEvents(event))
                      ||(m_menu->getMenuState() == SHOP && m_shopView->treatEvents(event) )
                    )
            {
                m_menu->setMenuState(HOME);
            }
        }
    }
    return result;
}
