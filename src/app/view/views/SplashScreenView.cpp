#include "SplashScreenView.h"

namespace ViewResources = Bokoblin::BokoRunner::Resources::View;

//------------------------------------------------
//          CONSTRUCTORS / DESTRUCTOR
//------------------------------------------------
/**
 * @brief Constructor
 *
 * @param window the app window
 * @param textManager the text manager
 * @param splashModel the splash screen model counterpart
 *
 * @author Arthur
 * @date 27/03/2016 - 05/01/2017
 */
SplashScreenView::SplashScreenView(sf::RenderWindow* window, AppTextManager* textManager, SplashScreenModel* splashModel) :
        AbstractView(window, textManager), m_splashModel{splashModel}
{
    //Only on splash screen otherwise it overwrites user defined location at each menu/game restarting

    const unsigned int desktopWidth = sf::VideoMode::getDesktopMode().width;
    const unsigned int desktopHeight = sf::VideoMode::getDesktopMode().height;

    const unsigned int appPositionX = (desktopWidth - m_width) / 2;
    const unsigned int appPositionY = (desktopHeight - m_height) / 2;

    m_window->setPosition(sf::Vector2i(appPositionX, appPositionY));

    SplashScreenView::loadSprites();
}

/**
 * @brief Destructor
 *
 * @author Arthur
 * @date 27/03/2016 - 13/07/2019
 */
SplashScreenView::~SplashScreenView()
{
    delete m_splashScreen;
    delete m_appTitle;
    delete m_parallaxBackground;
}

//------------------------------------------------
//          METHODS
//------------------------------------------------

/**
 * @brief Load all sprites used by the splash screen
 *
 * @author Arthur
 * @date 27/03/2016 - 07/07/2020
 */
void SplashScreenView::loadSprites()
{
    //FIXME: merging causes black drawing, is there a weird difference ?? Virtual effect ?
    m_splashScreen = new mdsf::Image(0, 0, m_width, m_height);
    m_splashScreen->loadAndApplyTextureFromFile(ViewResources::SPLASH_SCREEN_IMAGE);

    m_parallaxBackground = new ParallaxBackground(BACKGROUND_WIDTH, m_height);
    m_parallaxBackground->addBackground(0, 0, ViewResources::GAME_FAR_HILL_BACKGROUND);
    m_parallaxBackground->addBackground(1, 0, ViewResources::GAME_NEAR_HILL_BACKGROUND);
    m_parallaxBackground->setLight(0);
    //m_parallaxBackground->applyColor();

    m_appTitle = new mdsf::Image(getHalfXPosition() - (0.45f * TITLE_WIDTH), 0.167f * m_height,
                                  TITLE_WIDTH, TITLE_HEIGHT, ViewResources::TITLE_IMAGE);
    m_appTitle->resize(m_appTitle->getWidth() * 0.95f, m_appTitle->getHeight() * 0.95f);
    m_appTitle->setAlpha(0);
    //m_appTitle->sync();
}

/**
 * @brief Synchronize splash screen elements
 *
 * @author Arthur
 * @date 27/03/2016 - 05/07/2020
 */
void SplashScreenView::synchronize()
{
    if (!m_splashModel->isInEndingPhase()) {
        m_textManager->syncSplashScreenText(m_splashModel->isContinueVisible());
    } else {
        if (m_appTitle->getAlpha() >= 245) {
            m_splashModel->setAppState(MENU);
        } else {
            m_splashScreen->setAlpha(15, mdsf::Color::DECR);
            m_parallaxBackground->setLight(3, mdsf::Color::INCR);
            m_appTitle->setAlpha(5, mdsf::Color::INCR);
        }
    }

    //FIXME: sync causes black background
    //m_splashScreen->sync();
    //m_parallaxBackground->sync();
    //m_appTitle->sync();
}

/**
 * @brief Draw splash screen elements on the window
 *
 * @author Arthur
 * @date 27/03/2016 - 05/07/2019
 */
void SplashScreenView::draw() const
{
    m_window->clear();

    //m_window->draw(*m_parallaxBackground);
    m_window->draw(*m_appTitle);
    m_window->draw(*m_splashScreen);

    if (!m_splashModel->isInEndingPhase()) {
        m_textManager->drawSplashScreenText(m_window);
    }

    m_window->display();
}

/**
 * @brief Handle the user interaction events (mouse, keyboard, title bar buttons)
 *
 * @param event sfml event object
 * @return true if app state is unchanged
 *
 * @author Arthur
 * @date 27/03/2016 - 13/01/2019
 */
bool SplashScreenView::handleEvents(sf::Event& event)
{
    while (m_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_splashModel->setAppState(QUIT);
            return false;
        }

        if (EventUtils::wasKeyboardContinuePressed()) {
            m_splashModel->setEndingPhase(true);
        }
    }
    return true;
}
