#include "IntroView.h"

/**
 * Parameterized Constructor
 * @author Arthur
 * @date 27/03/16 - 02/11/17
 *
 * @param window the app's window
 * @param textHandler a text handler to display standalone text
 * @param introModel the intro's model part
 */
IntroView::IntroView(sf::RenderWindow *window, TextHandler *textHandler, IntroModel *introModel) :
        AbstractView(window, textHandler), m_intro{introModel}
{
    //Only on splash screen otherwise it overwrites user defined location at each menu/game restarting
    m_window->setPosition(ENVIRONMENT_CENTER);

    loadImages();
}


/**
 * Destructor
 * @author Arthur
 * @date 27/03/16
 */
IntroView::~IntroView()
{
    delete m_introGraphic;
}


/**
 * Image Loading
 * @author Arthur
 * @date 27/03/16 - 02/01/17
 */
void IntroView::loadImages()
{
    m_introGraphic = new GraphicElement(0, 0, 400, 200);
    m_introGraphic->setTextureFromImage(INTRO_IMAGE);
}


/**
 * Synchronization function
 * @author Arthur
 * @date 27/03/16
 */
void IntroView::synchronize()
{
    m_textHandler->syncSplashScreenText(m_intro->isContinueVisible());
}


/**
 * View Drawing
 * @author Arthur
 * @date 27/03/16
 */
void IntroView::draw() const
{
    m_window->clear();

    m_window->draw(*m_introGraphic);
    m_textHandler->drawSplashScreenText(m_window);

    m_window->display();
}


/**
 * Events treating
 * @author Arthur
 * @date 27/03/16 - 03/11/17
 */
bool IntroView::treatEvents(sf::Event event)
{
    while (m_window->pollEvent(event))
    {
        if  (event.type == sf::Event::Closed)
        {
            m_intro->getDataBase()->setAppState(QUIT);
            return false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            m_intro->getDataBase()->setAppState(MENU);
        }
    }
    return true;
}

