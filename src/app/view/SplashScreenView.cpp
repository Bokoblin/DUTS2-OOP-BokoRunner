#include "SplashScreenView.h"

//------------------------------------------------
//          CONSTRUCTORS / DESTRUCTOR
//------------------------------------------------

/**
 * Constructs the splash screen view
 * with the window, the text manager and its model counterpart
 *
 * @param window the app window
 * @param textManager the text manager
 * @param splashModel the splash screen model counterpart
 *
 * @author Arthur
 * @date 27/03/16 - 05/01/17
 */
SplashScreenView::SplashScreenView(sf::RenderWindow *window, AppTextManager *textManager, SplashScreenModel *splashModel) :
        AbstractView(window, textManager), m_splashModel{splashModel}
{
    //Only on splash screen otherwise it overwrites user defined location at each menu/game restarting

    const unsigned int desktopWidth = sf::VideoMode::getDesktopMode().width;
    const unsigned int desktopHeight = sf::VideoMode::getDesktopMode().height;

    const unsigned int appPositionX = (desktopWidth - m_width)/2;
    const unsigned int appPositionY = (desktopHeight - m_height)/2;

    m_window->setPosition(sf::Vector2i(appPositionX, appPositionY));

    loadImages();
}


/**
 * Destructor
 * @author Arthur
 * @date 27/03/16 - 24/12/17
 */
SplashScreenView::~SplashScreenView()
{
    delete m_splashScreen;
    delete m_appTitle;
    delete m_farBackground;
    delete m_nearBackground;
}


//------------------------------------------------
//          METHODS
//------------------------------------------------

/**
 * Loads all sprites used by the splash screen
 * @author Arthur
 * @date 27/03/16 - 24/12/17
 */
void SplashScreenView::loadImages()
{
    m_splashScreen = new mdsf::Sprite(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    m_splashScreen->loadAndApplyTextureFromImageFile(SPLASH_SCREEN_IMAGE);

    m_farBackground = new ScrollingBackground(1200, m_height, 0, DEFAULT_FAR_HILL_BACKGROUND);
    m_nearBackground = new ScrollingBackground(1200, m_height, 0, DEFAULT_NEAR_HILL_BACKGROUND);
    m_farBackground->setLight(0);
    m_nearBackground->setLight(0);
    m_farBackground->applyColor();
    m_nearBackground->applyColor();

    m_appTitle = new mdsf::Sprite(m_width/2-180, m_height/6, 400, 200, TITLE_IMAGE);
    m_appTitle->resize(360, 180);
    m_appTitle->setAlpha(0);
    m_appTitle->applyColor();
}


/**
 * Synchronizes splash screen elements
 *
 * @author Arthur
 * @date 27/03/16 - 24/12/17
 */
void SplashScreenView::synchronize()
{
    if (!m_splashModel->isInEndingPhase())
    {
        m_textManager->syncSplashScreenText(m_splashModel->isContinueVisible());
    }
    else
    {
        if (m_farBackground->getLight() >= 245)
        {
            m_splashModel->getDataBase()->setAppState(MENU);
        }
        else
        {
            m_splashScreen->decreaseAlpha(15);
            m_farBackground->increaseLight(5);
            m_nearBackground->increaseLight(5);
            m_appTitle->increaseAlpha(5);

            m_splashScreen->sync();
            m_farBackground->sync();
            m_nearBackground->sync();
            m_appTitle->sync();
        }
    }
}


/**
 * Draws splash screen elements on the window
 *
 * @author Arthur
 * @date 27/03/16 - 24/12/17
 */
void SplashScreenView::draw() const
{
    m_window->clear();

    m_farBackground->draw(m_window);
    m_nearBackground->draw(m_window);
    m_window->draw(*m_appTitle);
    m_window->draw(*m_splashScreen);

    if (!m_splashModel->isInEndingPhase())
        m_textManager->drawSplashScreenText(m_window);

    m_window->display();
}


/**
 * Handles the user interaction events (mouse, keyboard, title bar buttons)
 *
 * @param event sfml event object
 * @return true if app state is unchanged
 *
 * @author Arthur
 * @date 27/03/16 - 26/12/17
 */
bool SplashScreenView::handleEvents(sf::Event event)
{
    while (m_window->pollEvent(event))
    {
        if  (event.type == sf::Event::Closed)
        {
            m_splashModel->getDataBase()->setAppState(QUIT);
            return false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            m_splashModel->setEndingPhase(true);
        }
    }
    return true;
}

