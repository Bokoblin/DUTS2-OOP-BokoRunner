#include "Intro.h"

using namespace std;

/**
 * Parameterized Constructor
 * @author Arthur
 * @date 27/03/16 - 11/04/16
 */
Intro::Intro(float w, float h, sf::RenderWindow *window, TextHandler *text): View(w, h, window, text)
{
    m_window->create(sf::VideoMode((unsigned int) w, (unsigned int) h, SCREEN_BPP), APP_TITLE, sf::Style::None );
    m_window->setFramerateLimit(30);
    m_window->setPosition(ENV_CENTERED);

    loadImages();
}


/**
 * Destructor
 * @author Arthur
 * @date 27/03/16
 */
Intro::~Intro()
{
    delete m_introGraphic;
}


/**
 * Image Loading
 * @author Arthur
 * @date 27/03 - 02/01/17
 */
void Intro::loadImages()
{
    m_introGraphic = new GraphicElement(0, 0, 400, 200);
    m_introGraphic->setTextureFromImage(INTRO_IMAGE);
}


/**
 * Synchronization function
 * @author Arthur
 * @date 27/03/16
 */
void Intro::synchronize()
{ }


/**
 * View Drawing
 * @author Arthur
 * @date 27/03/16
 */
void Intro::draw() const
{
    m_window->clear();
    m_window->draw(*m_introGraphic);
    m_window->display();
}


/**
 * Events treating
 * @author Arthur
 * @date 27/03/16
 */
bool Intro::treatEvents()
{
    bool result = false;

    if(m_window->isOpen())
    {
        result = true;

        sf::Event event;
        while (m_window->pollEvent(event))
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_model->getAppState() == INTRO)
            {
                m_model->setAppState(MENU);
            }
        }
    }
    return result;
}
