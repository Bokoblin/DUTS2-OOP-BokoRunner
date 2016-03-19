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

#include <iostream>

/********************************************
    Parameterized Constructor
*********************************************
    Arthur : 3/03 - 19/03
*********************************************/
AnimatedGraphicElement::AnimatedGraphicElement(const std::vector<sf::IntRect> & clipRects,
                                               sf::Texture &image, int x, int y, int w, int h):
    GraphicElement(image, x, y, w, h), m_clip_rects{clipRects}, m_current_clip_rect{0}, m_lastAnimationTime{0}
{

}


/********************************************
    Copy Constructor
*********************************************
    Arthur : 19/03
*********************************************/
AnimatedGraphicElement::AnimatedGraphicElement(AnimatedGraphicElement const& elementACopier) :
    GraphicElement(elementACopier), m_clip_rects{elementACopier.m_clip_rects}, m_current_clip_rect{0}, m_lastAnimationTime{0}
{

}


/********************************************
    Destructor
*********************************************
    Arthur : 5/03 - 5/03
*********************************************/
AnimatedGraphicElement::~AnimatedGraphicElement()
{

}


/********************************************
    Drawing Function
*********************************************
    Arthur : 3/03 - 19/03
*********************************************/
void AnimatedGraphicElement::draw(sf::RenderWindow *window)
{
    //=== Change Animation
    float duration = (clock() - m_lastAnimationTime) / (double)CLOCKS_PER_SEC;
    if ( duration >= 0.150) // 150ms
    {
        this->setTextureRect(m_clip_rects[m_current_clip_rect]);
        if (m_current_clip_rect == m_clip_rects.size()-1)
            m_current_clip_rect = 0;
        else
            m_current_clip_rect++;

        m_lastAnimationTime = clock();
    }

    //=== Draw
    window->draw(*this);
}
