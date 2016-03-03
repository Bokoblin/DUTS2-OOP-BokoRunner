#include "../header/SlidingBackground.h"
#include "../header/View.h"
#include <iostream>

using namespace std;

/********************************************
    Parameterized Constructor
*********************************************
    Arthur : 3/03 - 3/03
    Florian: 3/03 - 3/03
*********************************************/
SlidingBackground::SlidingBackground(sf::Texture &image, int w, int h, unsigned int speed):
    m_width{w}, m_height{h}, m_speed{speed}
{
    m_left = new GraphicElement(image, 0, 0, w, h);
    m_left->resize(900,600);
    m_right = new GraphicElement(image, w, 0, w, h);
    m_right->resize(900,600);
}


/********************************************
    Sunchronization and drawing Function
*********************************************
    Arthur : 3/03 - 3/03
    Florian: 3/03 - 3/03
*********************************************/
void SlidingBackground::syncAndDraw(sf::RenderWindow &window)
{
    //=== Sync

    m_left->setPosition(m_left->getPosition().x - m_speed, m_left->getPosition().y);
    m_right->setPosition(m_right->getPosition().x - m_speed, m_right->getPosition().y);


    if ( m_left->getPosition().x + m_width < 0 )
    {
        m_left->setPosition(0, 0);
        m_right->setPosition(m_width, 0);
    }

    //=== Draw

    window.draw(*m_left);
    window.draw(*m_right);
}



/********************************************
    SETTERS
*********************************************
    Arthur : 3/03 - 3/03
    Florian: 3/03 - 3/03
*********************************************/
void SlidingBackground::setSpeed(unsigned int speed) { m_speed = speed;}
