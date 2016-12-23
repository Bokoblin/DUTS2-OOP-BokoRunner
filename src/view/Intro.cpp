#include "Intro.h"

using namespace std;

/**
 * Parameterized Constructor
 * @author Arthur
 * @date 27/03 - 11/04
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
 * @date 27/03
 */
Intro::~Intro()
{
    delete m_introGraphic;
}


/**
 * Image Loading
 * @author Arthur
 * @date 27/03
 */
void Intro::loadImages()
{
    if (!m_introTexture.loadFromFile(INTRO_IMAGE))
        cerr << "ERROR when loading image file: " << INTRO_IMAGE << endl;
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
void Intro::synchronize()
{ }


/**
 * View Drawing
 * @author Arthur
 * @date 27/03
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
 * @date 27/03
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
