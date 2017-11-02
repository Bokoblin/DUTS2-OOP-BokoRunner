#include "IntroView.h"

/**
 * Parameterized Constructor
 * @author Arthur
 * @date 27/03/16 - 11/04/16
 */
IntroView::IntroView(float width, float height, sf::RenderWindow *window,
                     TextHandler *textHandler, IntroModel *introModel) :
        AbstractView(width, height, window, textHandler), m_intro{introModel}
{
    m_window->create(sf::VideoMode((unsigned int) width, (unsigned int) height, SCREEN_BPP), APP_TITLE, sf::Style::Close);
    m_window->setFramerateLimit(30);
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
 * @date 27/03/16 - 29/01/17
 */
bool IntroView::treatEvents(sf::Event event)
{
    bool result = false;

    if (m_window->isOpen())
    {
        result = true;

        while (m_window->pollEvent(event))
        {
            if  (event.type == sf::Event::Closed)
            {
                m_intro->getDataBase()->setAppState(QUIT);
                m_window->close();
                result = false;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                m_intro->getDataBase()->setAppState(MENU);
            }
        }
    }
    return result;
}

