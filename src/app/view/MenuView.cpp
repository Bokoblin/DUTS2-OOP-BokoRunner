#include "MenuView.h"

using std::vector;
using Bokoblin::SimpleLogger::Logger;

//------------------------------------------------
//          CONSTRUCTORS / DESTRUCTOR
//------------------------------------------------

/**
 * Constructs the menu view
 * with the window, the text manager and its model counterpart
 *
 * @param window the app window
 * @param textManager the text manager
 * @param menuModel the menu model counterpart
 *
 * @author Arthur, Florian
 * @date 25/02/16 - 24/01/17
 */
MenuView::MenuView(sf::RenderWindow *window, AppTextManager *textManager, MenuModel *menuModel) :
        AbstractView(window, textManager), m_menu{menuModel},
        m_commandsView{nullptr}, m_leaderboardView{nullptr}, m_settingsView{nullptr}, m_shopView{nullptr}
{
    loadMusic();
    loadImages();
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


//------------------------------------------------
//          METHODS
//------------------------------------------------

/**
 * Loads the menu music at startup
 *
 * @author Arthur
 * @date 29/12/17
 */
void MenuView::loadMusic()
{
    if (!m_menuMusic.openFromFile(MENU_MUSIC_THEME))

        Logger::printErrorOnConsole("Music loading failed for \"" + MENU_MUSIC_THEME + "\"");
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
}


/**
 * Loads all sprites used by the menu screen
 *
 * @author Arthur
 * @date 26/03/16 - 24/12/17
 */
void MenuView::loadImages()
{
    m_farBackground = new ScrollingBackground(1200, m_height, 1, DEFAULT_FAR_HILL_BACKGROUND);
    m_nearBackground = new ScrollingBackground(1200, m_height, 2, DEFAULT_NEAR_HILL_BACKGROUND);

    m_titleGraphic = new mdsf::Sprite(m_width/2-180, m_height/6, 400, 200, TITLE_IMAGE);
    m_titleGraphic->resize(360, 180);

    //=== Initialize PLAY and QUIT buttons

    vector<sf::IntRect> clipRectPlay;
    clipRectPlay.emplace_back(0, 0, 150, 80);
    clipRectPlay.emplace_back(151, 0, 150, 80);
    m_playRectButton = new mdsf::Button(m_width/2-75, (float) (m_height / 1.5), 150, 80, "menu_play_button",
                                  RECT_BUTTONS_IMAGE, clipRectPlay);
    m_playRectButton->retrieveAndSyncLabel(m_menu->getDataBase()->getLanguageFile());

    vector<sf::IntRect> clipRectQuit;
    clipRectQuit.emplace_back(0, 0, 150, 80);
    clipRectQuit.emplace_back(151, 0, 150, 80);
    m_quitRectButton = new mdsf::Button(m_width/2-75, (float) (m_height / 1.2), 150, 80, "menu_quit_button",
                                  RECT_BUTTONS_IMAGE, clipRectQuit);
    m_quitRectButton->retrieveAndSyncLabel(m_menu->getDataBase()->getLanguageFile());


    //=== Initialize COMMANDS, SETTINGS, LEADERBOARD and SHOP form buttons

    vector<sf::IntRect> clipRectCommands;
    clipRectCommands.emplace_back(0, 200, 50, 50);
    clipRectCommands.emplace_back(51, 200, 50, 50);
    m_commandsFormButton = new mdsf::Button(20, 10, 50, 50, SHAPE_BUTTONS_IMAGE, clipRectCommands);

    vector<sf::IntRect> clipRectSettings;
    clipRectSettings.emplace_back(0, 0, 50, 50);
    clipRectSettings.emplace_back(51, 0, 50, 50);
    m_settingsFormButton = new mdsf::Button(20, 530, 50, 50, SHAPE_BUTTONS_IMAGE, clipRectSettings);

    vector<sf::IntRect> clipRectLeaderboard;
    clipRectLeaderboard.emplace_back(0, 100, 50, 50);
    clipRectLeaderboard.emplace_back(51, 100, 50, 50);
    m_leaderboardFormButton = new mdsf::Button(830, 530, 50, 50, SHAPE_BUTTONS_IMAGE, clipRectLeaderboard);

    vector<sf::IntRect> clipRectShop;
    clipRectShop.emplace_back(0, 150, 50, 50);
    clipRectShop.emplace_back(51, 150, 50, 50);
    m_shopFormButton = new mdsf::Button(830, 10, 50, 50, SHAPE_BUTTONS_IMAGE, clipRectShop);
}


/**
 * Synchronizes menu elements
 *
 * @author Arthur
 * @date 26/03/16 - 30/01/17
 */
void MenuView::synchronize()
{
    if (m_menu->getDataBase()->isMenuMusicEnabled())
        m_menuMusic.setVolume(100);
    else
        m_menuMusic.setVolume(0);

    if (m_menuMusic.getPlayingOffset() >= sf::milliseconds(28840))
        m_menuMusic.setPlayingOffset(sf::milliseconds(4851));

    switch (m_menu->getMenuState())
    {
        case HOME:
            m_farBackground->sync();
            m_nearBackground->sync();
            m_playRectButton->sync();
            m_quitRectButton->sync();
            m_commandsFormButton->sync();
            m_settingsFormButton->sync();
            m_leaderboardFormButton->sync();
            m_shopFormButton->sync();
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
    if (m_menu->getMenuState() != COMMANDS && m_commandsView != nullptr)
    {
        delete m_commandsView;
        m_commandsView = nullptr;
    }

    //=== Delete leaderboardView if not anymore current menu state
    if (m_menu->getMenuState() != LEADERBOARD && m_leaderboardView != nullptr)
    {
        delete m_leaderboardView;
        m_leaderboardView = nullptr;
    }

    //=== Delete settingsView if not anymore current menu state
    if (m_menu->getMenuState() != SETTINGS && m_settingsView != nullptr)
    {
        delete m_settingsView;
        m_settingsView = nullptr;
    }

    //=== Delete shopView if not anymore current menu state
    if (m_menu->getMenuState() != SHOP && m_shopView != nullptr)
    {
        delete m_shopView;
        m_shopView = nullptr;
    }
}


/**
 * Draws menu elements on the window
 *
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
 * Handles Home screen events
 *
 * @param event sfml event object
 * @return true if app state is unchanged
 *
 * @author Arthur, Florian
 * @date 25/03/16 - 27/12/17
 */
bool MenuView::handleHomeEvents(const sf::Event &event)
{
    if (MOUSE_LEFT_PRESSED_EVENT)
    {
        if (m_playRectButton->contains(MOUSE_POSITION))
            m_playRectButton->setPressed(true);

        else if (m_quitRectButton->contains(MOUSE_POSITION))
            m_quitRectButton->setPressed(true);

        else if (m_commandsFormButton->contains(MOUSE_POSITION))
            m_commandsFormButton->setPressed(true);

        else if (m_settingsFormButton->contains(MOUSE_POSITION))
            m_settingsFormButton->setPressed(true);

        else if (m_leaderboardFormButton->contains(MOUSE_POSITION))
            m_leaderboardFormButton->setPressed(true);

        else if (m_shopFormButton->contains(MOUSE_POSITION))
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

        if (m_playRectButton->contains(MOUSE_POSITION))
        {
            if (m_menuMusic.getStatus() == sf::Music::Status::Playing)
                m_menuMusic.stop();
            m_menu->getDataBase()->setAppState(GAME);
            return false;
        }
        else if (m_quitRectButton->contains(MOUSE_POSITION))
        {
            if (m_menuMusic.getStatus() == sf::Music::Status::Playing)
                m_menuMusic.stop();
            m_menu->getDataBase()->setAppState(QUIT);
            return false;
        }
        else if (m_commandsFormButton->contains(MOUSE_POSITION))
        {
            m_commandsView = new CommandsView(m_window, m_textManager, m_menu->launchCommands());
        }
        else if (m_leaderboardFormButton->contains(MOUSE_POSITION))
        {
            m_leaderboardView = new LeaderboardView(m_window, m_textManager, m_menu->launchLeaderboard());
        }
        else if (m_settingsFormButton->contains(MOUSE_POSITION))
        {
            m_settingsView = new SettingsView(m_window, m_textManager, m_menu->launchSettings());
        }
        else if (m_shopFormButton->contains(MOUSE_POSITION))
        {
            m_shopView = new ShopView(m_window, m_textManager, m_menu->launchShop());
        }
    }

    return true;
}


/**
 * Handles the user interaction events (mouse, keyboard, title bar buttons)
 *
 * @param event sfml event object
 * @return true if app state is unchanged
 *
 * @author Arthur, Florian
 * @date 25/03/16 - 27/12/17
 */
bool MenuView::handleEvents(sf::Event event)
{
    while (m_window->pollEvent(event))
    {
        if  (event.type == sf::Event::Closed)
        {
            m_menu->getDataBase()->setAppState(QUIT);
            return false;
        }

        if (m_menu->getMenuState() == HOME)
        {
            return handleHomeEvents(event);
        }
        else if ((m_menu->getMenuState() == COMMANDS && !m_commandsView->handleEvents(event))
                 || (m_menu->getMenuState() == LEADERBOARD && !m_leaderboardView->handleEvents(event))
                 || (m_menu->getMenuState() == SETTINGS && !m_settingsView->handleEvents(event))
                 || (m_menu->getMenuState() == SHOP && !m_shopView->handleEvents(event))
                )
        {
            m_menu->setMenuState(HOME);
            m_playRectButton->retrieveAndSyncLabel(m_menu->getDataBase()->getLanguageFile());
            m_quitRectButton->retrieveAndSyncLabel(m_menu->getDataBase()->getLanguageFile());
        }
    }
    return true;
}
