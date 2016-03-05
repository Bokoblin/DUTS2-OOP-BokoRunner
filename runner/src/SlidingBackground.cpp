/* Copyright (C) 2016 Jolivet Arthur & Laronze Florian

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#include "../header/SlidingBackground.h"
#include "../header/View.h"

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
    //m_left->resize(900,600);
    m_right = new GraphicElement(image, w, 0, w, h);
    //m_right->resize(900,600);
}


/********************************************
    Destructor
*********************************************
    Arthur : 5/03 - 5/03
*********************************************/
SlidingBackground::~SlidingBackground()
{
    if(m_left!= NULL)
        delete m_left;
    if(m_right!= NULL)
        delete m_right;
}


/********************************************
    Synchronization and drawing Function
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
