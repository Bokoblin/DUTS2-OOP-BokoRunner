#include "../header/SlidingBackground.h"

/********************************************
    Parameterized Constructor
*********************************************
    @author Arthur  @date 3/03 - 3/04
    @author Florian  @date 3/03
*********************************************/
SlidingBackground::SlidingBackground(sf::Texture &image, float w, float h, unsigned int speed):
    GraphicElement(w, h), m_speed{speed}
{
    m_left = new GraphicElement(image, 0, 0, w, h);
    m_right = new GraphicElement(image, w, 0, w, h);
}


/********************************************
    Destructor
*********************************************
    @author Arthur  @date 5/03 - 15/04
*********************************************/
SlidingBackground::~SlidingBackground()
{
    delete m_left;
    delete m_right;
}


/********************************************
    Synchronization Function
*********************************************
    @author Arthur  @date 3/03 - 26/03
*********************************************/
void SlidingBackground::sync()
{
    m_left->setPosition(m_left->getPosition().x - m_speed, m_left->getPosition().y);
    m_right->setPosition(m_right->getPosition().x - m_speed, m_right->getPosition().y);

    if ( m_left->getPosition().x + m_width < 0 )
    {
        m_left->setPosition(0, 0);
        m_right->setPosition(m_width, 0);
    }
}


/********************************************
    Drawing Function
*********************************************
    @author Arthur  @date 3/03 - 03/04
*********************************************/
void SlidingBackground::draw(sf::RenderWindow *window) const
{
    window->draw(*m_left);
    window->draw(*m_right);
}


/********************************************
    Setters
*********************************************
    @author Arthur  @date 3/03
    @author Florian @date 3/03
*********************************************/
void SlidingBackground::setSpeed(unsigned int speed) { m_speed = speed; }
