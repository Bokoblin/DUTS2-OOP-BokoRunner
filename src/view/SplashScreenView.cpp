#include "SplashScreenView.h"

/**
 * Parameterized Constructor
 * @author Arthur
 * @date 27/03/16 - 02/11/17
 *
 * @param window the app's window
 * @param textHandler a text handler to display standalone text
 * @param splashModel the splash screen's model part
 */
SplashScreenView::SplashScreenView(sf::RenderWindow *window, TextHandler *textHandler, SplashScreenModel *splashModel) :
        AbstractView(window, textHandler), m_splashModel{splashModel}
{
    //Only on splash screen otherwise it overwrites user defined location at each menu/game restarting
    m_window->setPosition(ENVIRONMENT_CENTER);

    loadImages();
}


/**
 * Destructor
 * @author Arthur
 * @date 27/03/16 - 24/12/17
 */
SplashScreenView::~SplashScreenView()
{
    delete m_splashScreenGraphic;
    delete m_titleGraphic;
    delete m_farBackground;
    delete m_nearBackground;
}


/**
 * Image Loading
 * @author Arthur
 * @date 27/03/16 - 24/12/17
 */
void SplashScreenView::loadImages()
{
    m_splashScreenGraphic = new GraphicElement(0, 0, 400, 200);
    m_splashScreenGraphic->setTextureFromImage(SPLASH_SCREEN_IMAGE);

    m_farBackground = new ScrollingBackground(1200, m_height, 0, DEFAULT_FAR_HILL_BACKGROUND);
    m_nearBackground = new ScrollingBackground(1200, m_height, 0, DEFAULT_NEAR_HILL_BACKGROUND);
    m_farBackground->setLight(0);
    m_nearBackground->setLight(0);
    m_farBackground->applyColor();
    m_nearBackground->applyColor();

    m_titleGraphic = new GraphicElement(m_width/2-180, m_height/6, 400, 200, TITLE_IMAGE);
    m_titleGraphic->resize(360, 180);
    m_titleGraphic->setAlpha(0);
    m_titleGraphic->applyColor();
}


/**
 * Synchronization function
 * @author Arthur
 * @date 27/03/16 - 24/12/17
 */
void SplashScreenView::synchronize()
{
    if (!m_splashModel->isInEndingPhase())
    {
        m_textHandler->syncSplashScreenText(m_splashModel->isContinueVisible());
    }
    else
    {
        if (m_farBackground->getLight() >= 245)
        {
            m_splashModel->getDataBase()->setAppState(MENU);
        }
        else
        {
            m_splashScreenGraphic->decreaseAlpha(15);
            m_farBackground->increaseLight(5);
            m_nearBackground->increaseLight(5);
            m_titleGraphic->increaseAlpha(5);

            m_splashScreenGraphic->sync();
            m_farBackground->sync();
            m_nearBackground->sync();
            m_titleGraphic->sync();
        }
    }
}


/**
 * View Drawing
 * @author Arthur
 * @date 27/03/16 - 24/12/17
 */
void SplashScreenView::draw() const
{
    m_window->clear();

    m_farBackground->draw(m_window);
    m_nearBackground->draw(m_window);
    m_window->draw(*m_titleGraphic);
    m_window->draw(*m_splashScreenGraphic);

    if (!m_splashModel->isInEndingPhase())
        m_textHandler->drawSplashScreenText(m_window);

    m_window->display();
}


/**
 * Events treating
 * @author Arthur
 * @date 27/03/16 - 24/12/17
 */
bool SplashScreenView::treatEvents(sf::Event event)
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

