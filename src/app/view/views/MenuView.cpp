#include "MenuView.h"

using std::vector;
using Bokoblin::SimpleLogger::Logger;
namespace ViewResources = Bokoblin::BokoRunner::Resources::View;

//------------------------------------------------
//          CONSTRUCTORS / DESTRUCTOR
//------------------------------------------------

/**
 * @brief Constructor
 *
 * @param window the app window
 * @param textManager the text manager
 * @param menuModel the menu model counterpart
 *
 * @author Arthur, Florian
 * @date 25/02/2016 - 24/01/2017
 */
MenuView::MenuView(sf::RenderWindow* window, AppTextManager* textManager, MenuModel* menuModel) :
        AbstractView(window, textManager), m_menu{menuModel},
        m_commandsView{nullptr}, m_leaderboardView{nullptr}, m_settingsView{nullptr}, m_shopView{nullptr}
{
    loadMusic();
    MenuView::loadSprites();
}

/**
 * @brief Destructor
 * @author Arthur
 * @date 26/02/2016 - 14/07/2019
 */
MenuView::~MenuView()
{
    delete m_parallaxBackground;
    delete m_titleSprite;
    delete m_playButton;
    delete m_quitButton;
    delete m_commandsButton;
    delete m_settingsButton;
    delete m_leaderboardButton;
    delete m_shopButton;
}

//------------------------------------------------
//          METHODS
//------------------------------------------------

/**
 * @brief Load the menu music at startup
 *
 * @author Arthur
 * @date 29/12/2017
 */
void MenuView::loadMusic()
{
    if (!m_menuMusic.openFromFile(ViewResources::MENU_MUSIC_THEME)) {
        Logger::printError("Music loading failed for \"" + ViewResources::MENU_MUSIC_THEME + "\"");
    } else {
        if (m_menu->isMusicEnabled()) {
            m_menuMusic.setVolume(100);
        } else {
            m_menuMusic.setVolume(0);
        }
        m_menuMusic.play();
        m_menuMusic.setLoop(true);
        m_menuMusic.setAttenuation(50);
    }
}

/**
 * @brief Load all sprites used by the menu screen
 *
 * @author Arthur
 * @date 26/03/2016 - 14/07/2019
 */
void MenuView::loadSprites()
{
    m_parallaxBackground = new ParallaxBackground(BACKGROUND_WIDTH, m_height);
    m_parallaxBackground->addBackground(0, FAR_SCROLL_SPEED, ViewResources::GAME_FAR_HILL_BACKGROUND);
    m_parallaxBackground->addBackground(1, NEAR_SCROLL_SPEED, ViewResources::GAME_NEAR_HILL_BACKGROUND);

    m_titleSprite = new mdsf::Sprite(getHalfXPosition() - (0.45f * TITLE_WIDTH), 0.167f * m_height,
                                     TITLE_WIDTH, TITLE_HEIGHT, ViewResources::TITLE_IMAGE);
    m_titleSprite->resize(m_titleSprite->getWidth() * 0.95f, m_titleSprite->getHeight() * 0.95f);

    //=== Initialize PLAY and QUIT buttons

    m_playButton = new mdsf::RaisedButton(getHalfXPosition() - 0.5f * MAIN_BTN_WIDTH, 0.667f * m_height,
                                          MAIN_BTN_WIDTH, MAIN_BTN_HEIGHT, "menu_play_button", ViewResources::MENU_BUTTON_IMAGE);
    m_playButton->retrieveLabel(LocalizationManager::fetchLocalizedString);

    m_quitButton = new mdsf::RaisedButton(getHalfXPosition() - 0.5f * MAIN_BTN_WIDTH, 0.833f * m_height,
                                          MAIN_BTN_WIDTH, MAIN_BTN_HEIGHT, "menu_quit_button", ViewResources::MENU_BUTTON_IMAGE);
    m_quitButton->retrieveLabel(LocalizationManager::fetchLocalizedString);


    //=== Initialize COMMANDS, SETTINGS, LEADERBOARD and SHOP buttons

    m_commandsButton = new mdsf::RaisedButton(0.02f * m_width, 0.02f * m_height, HOME_BTN_SIZE, HOME_BTN_SIZE, "", "");
    m_commandsButton->loadAndApplyTextureFromImageFile(ViewResources::SHAPE_BUTTONS_IMAGE, sf::Rect<int>(0, 0, 50, 50));

    m_settingsButton = new mdsf::RaisedButton(0.02f * m_width, 0.89f * m_height, HOME_BTN_SIZE, HOME_BTN_SIZE, "", "");
    m_settingsButton->loadAndApplyTextureFromImageFile(ViewResources::SHAPE_BUTTONS_IMAGE, sf::Rect<int>(0, 50, 50, 50));

    m_shopButton = new mdsf::RaisedButton(0.92f * m_width, 0.02f * m_height, HOME_BTN_SIZE, HOME_BTN_SIZE, "", "");
    m_shopButton->loadAndApplyTextureFromImageFile(ViewResources::SHAPE_BUTTONS_IMAGE, sf::Rect<int>(0, 100, 50, 50));

    m_leaderboardButton = new mdsf::RaisedButton(0.92f * m_width, 0.89f * m_height, HOME_BTN_SIZE, HOME_BTN_SIZE, "", "");
    m_leaderboardButton->loadAndApplyTextureFromImageFile(ViewResources::SHAPE_BUTTONS_IMAGE, sf::Rect<int>(0, 150, 50, 50));
}

/**
 * @brief Synchronize menu elements
 *
 * @author Arthur
 * @date 26/03/2016 - 14/07/2019
 */
void MenuView::synchronize()
{
    if (m_menu->isMusicEnabled()) {
        m_menuMusic.setVolume(100);
    } else {
        m_menuMusic.setVolume(0);
    }

    if (m_menuMusic.getPlayingOffset() >= sf::milliseconds(MUSIC_LOOP_END)) {
        m_menuMusic.setPlayingOffset(sf::milliseconds(MUSIC_LOOP_START));
    }

    switch (m_menu->getMenuState()) {
        case HOME:
            m_parallaxBackground->sync();
            m_playButton->sync();
            m_quitButton->sync();
            m_commandsButton->sync();
            m_settingsButton->sync();
            m_leaderboardButton->sync();
            m_shopButton->sync();
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
    if (m_menu->getMenuState() != COMMANDS && m_commandsView != nullptr) {
        delete m_commandsView;
        m_commandsView = nullptr;
    }

    //=== Delete leaderboardView if not anymore current menu state
    if (m_menu->getMenuState() != LEADERBOARD && m_leaderboardView != nullptr) {
        delete m_leaderboardView;
        m_leaderboardView = nullptr;
    }

    //=== Delete settingsView if not anymore current menu state
    if (m_menu->getMenuState() != SETTINGS && m_settingsView != nullptr) {
        delete m_settingsView;
        m_settingsView = nullptr;
    }

    //=== Delete shopView if not anymore current menu state
    if (m_menu->getMenuState() != SHOP && m_shopView != nullptr) {
        delete m_shopView;
        m_shopView = nullptr;
    }
}

/**
 * @brief Draw menu elements on the window
 *
 * @author Arthur
 * @date 26/03/2016 - 14/07/2019
 */
void MenuView::draw() const
{
    if (m_menu->getMenuState() == HOME) {
        m_window->clear();

        m_parallaxBackground->draw(m_window);
        m_titleSprite->draw(m_window);
        m_playButton->draw(m_window);
        m_quitButton->draw(m_window);
        m_commandsButton->draw(m_window);
        m_settingsButton->draw(m_window);
        m_leaderboardButton->draw(m_window);
        m_shopButton->draw(m_window);

        m_window->display();
    } else if (m_menu->getMenuState() == COMMANDS) {
        m_commandsView->draw();
    } else if (m_menu->getMenuState() == SETTINGS) {
        m_settingsView->draw();
    } else if (m_menu->getMenuState() == LEADERBOARD) {
        m_leaderboardView->draw();
    } else if (m_menu->getMenuState() == SHOP) {
        m_shopView->draw();
    }
}

/**
 * @brief Handle Home screen events
 *
 * @param event sfml event object
 * @return true if app state is unchanged
 *
 * @author Arthur, Florian
 * @date 25/03/2016 - 30/10/2018
 */
bool MenuView::handleHomeEvents(const sf::Event& event)
{
    if (EventUtils::wasMouseLeftPressed(event)) {
        m_playButton->setPressed(EventUtils::isMouseInside(*m_playButton, event));
        m_quitButton->setPressed(EventUtils::isMouseInside(*m_quitButton, event));
        m_commandsButton->setPressed(EventUtils::isMouseInside(*m_commandsButton, event));
        m_settingsButton->setPressed(EventUtils::isMouseInside(*m_settingsButton, event));
        m_leaderboardButton->setPressed(EventUtils::isMouseInside(*m_leaderboardButton, event));
        m_shopButton->setPressed(EventUtils::isMouseInside(*m_shopButton, event));
    }

    if (EventUtils::wasMouseReleased(event)) {
        m_playButton->setPressed(false);
        m_quitButton->setPressed(false);
        m_commandsButton->setPressed(false);
        m_settingsButton->setPressed(false);
        m_leaderboardButton->setPressed(false);
        m_shopButton->setPressed(false);

        if (EventUtils::isMouseInside(*m_playButton, event)) {
            if (m_menuMusic.getStatus() == sf::Music::Status::Playing) {
                m_menuMusic.stop();
            }
            m_menu->setAppState(GAME);
            return false;
        } else if (EventUtils::isMouseInside(*m_quitButton, event)) {
            if (m_menuMusic.getStatus() == sf::Music::Status::Playing) {
                m_menuMusic.stop();
            }
            m_menu->setAppState(QUIT);
            return false;
        } else if (EventUtils::isMouseInside(*m_commandsButton, event)) {
            m_commandsView = new CommandsView(m_window, m_textManager, m_menu->launchCommands());
        } else if (EventUtils::isMouseInside(*m_leaderboardButton, event)) {
            m_leaderboardView = new LeaderboardView(m_window, m_textManager, m_menu->launchLeaderboard());
        } else if (EventUtils::isMouseInside(*m_settingsButton, event)) {
            m_settingsView = new SettingsView(m_window, m_textManager, m_menu->launchSettings());
        } else if (EventUtils::isMouseInside(*m_shopButton, event)) {
            m_shopView = new ShopView(m_window, m_textManager, m_menu->launchShop());
        }
    }

    return true;
}

/**
 * @brief Handle the user interaction events (mouse, keyboard, title bar buttons)
 *
 * @param event sfml event object
 * @return true if app state is unchanged
 *
 * @author Arthur, Florian
 * @date 25/03/2016 - 13/01/19
 */
bool MenuView::handleEvents(sf::Event& event)
{
    while (m_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_menu->setAppState(QUIT);
            return false;
        }

        if (m_menu->getMenuState() == HOME) {
            return handleHomeEvents(event);
        } else if ((m_menu->getMenuState() == COMMANDS && !m_commandsView->handleEvents(event))
                || (m_menu->getMenuState() == LEADERBOARD && !m_leaderboardView->handleEvents(event))
                || (m_menu->getMenuState() == SETTINGS && !m_settingsView->handleEvents(event))
                || (m_menu->getMenuState() == SHOP && !m_shopView->handleEvents(event))
                ) {
            m_menu->setMenuState(HOME);
            m_playButton->retrieveLabel(LocalizationManager::fetchLocalizedString);
            m_quitButton->retrieveLabel(LocalizationManager::fetchLocalizedString);
        }
    }
    return true;
}
