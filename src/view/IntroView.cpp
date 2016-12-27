#include "IntroView.h"

/********************************************
    Constant Variables
********************************************/
const int INTRO_WIDTH = 400;
const int INTRO_HEIGHT = 200;

/**
 * Parameterized Constructor
 * @author Arthur
 * @date 27/03 - 11/04
 */
IntroView::IntroView(int width, int height, sf::RenderWindow *window,
                     TextHandler *textHandler, IntroModel *introModel) :
        AbstractView(width, height, window, textHandler), m_intro{introModel}
{
    m_window->create(sf::VideoMode((unsigned int) width, (unsigned int) height, SCREEN_BPP), APP_TITLE, sf::Style::None );
    m_window->setFramerateLimit(30);
    m_window->setPosition(ENVIRONMENT_CENTER);

    loadImages();
}


/**
 * Destructor
 * @author Arthur
 * @date 27/03
 */
IntroView::~IntroView()
{
    delete m_introGraphic;
}


/**
 * Image Loading
 * @author Arthur
 * @date 27/03
 */
void IntroView::loadImages()
{
    if (!m_introTexture.loadFromFile(INTRO_IMAGE))
        std::cerr << "ERROR when loading image file: " << INTRO_IMAGE << std::endl;
    else
    {
        m_introTexture.setSmooth(true);
        m_introGraphic = new GraphicElement(m_introTexture, 0,0, 400, 200);
    }
}


/**
 * Synchronization function
 * @author Arthur
 * @date 27/03
 */
void IntroView::synchronize()
{ }


/**
 * View Drawing
 * @author Arthur
 * @date 27/03
 */
void IntroView::draw() const
{
    m_window->clear();
    m_window->draw(*m_introGraphic);
    m_window->display();
}


/**
 * Events treating
 * @author Arthur
 * @date 27/03
 */
bool IntroView::treatEvents()
{
    bool result = false;

    if(m_window->isOpen())
    {
        result = true;

        sf::Event event;
        while (m_window->pollEvent(event))
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                m_intro->getDataBase()->setAppState(MENU);
            }
        }
    }
    return result;
}