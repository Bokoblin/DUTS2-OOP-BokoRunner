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

#include "../header/AnimatedGraphicElement.h"

using namespace std::chrono;

/********************************************
    Parameterized Constructor
*********************************************
    Arthur : 3/03 - 6/04
*********************************************/
AnimatedGraphicElement::AnimatedGraphicElement(sf::Texture &image, float x, float y, unsigned int w,
            unsigned int h, const std::vector<sf::IntRect> & clipRects, unsigned int separator):
    GraphicElement(image, x, y, w, h), m_clipRectsArray{clipRects},
    m_currentClipRect{0}, m_lastAnimationTime{system_clock::now() }, m_arraySeparator{separator}
{
    this->setTextureRect(m_clipRectsArray[m_currentClipRect]);
}


/********************************************
    Copy Constructor
*********************************************
    Arthur : 19/03 - 6/04
*********************************************/
AnimatedGraphicElement::AnimatedGraphicElement(AnimatedGraphicElement const& other) :
    GraphicElement(other), m_clipRectsArray{other.m_clipRectsArray},
    m_currentClipRect{0}, m_lastAnimationTime{system_clock::now() }, m_arraySeparator{other.m_arraySeparator}
{
    this->setTextureRect(m_clipRectsArray[m_currentClipRect]);
}


/********************************************
    Destructor
*********************************************
    Arthur : 5/03
*********************************************/
AnimatedGraphicElement::~AnimatedGraphicElement()
{}


/********************************************
    Synchronization Function : change animation
*********************************************
    Arthur : 3/03 - 6/04
*********************************************/
void AnimatedGraphicElement::sync()
{
    system_clock::duration duration = system_clock::now() - m_lastAnimationTime;

    if ( duration > milliseconds(200) )
    {
        if (m_currentClipRect == m_arraySeparator-1)
            m_currentClipRect = 0;
        else
            m_currentClipRect++;

        this->setTextureRect(m_clipRectsArray[m_currentClipRect]);
        m_lastAnimationTime = system_clock::now();
    }
}
