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
    Arthur : 3/03 - 30/03
*********************************************/
AnimatedGraphicElement::AnimatedGraphicElement(const std::vector<sf::IntRect> & clipRects,
                                               sf::Texture &image, int x, int y, int w, int h):
    GraphicElement(image, x, y, w, h), m_clip_rects{clipRects},
    m_current_clip_rect{0}, m_lastAnimationTime{system_clock::now() }
{
    this->setTextureRect(m_clip_rects[m_current_clip_rect]);
}


/********************************************
    Copy Constructor
*********************************************
    Arthur : 19/03 - 30/03
*********************************************/
AnimatedGraphicElement::AnimatedGraphicElement(AnimatedGraphicElement const& elementACopier) :
    GraphicElement(elementACopier), m_clip_rects{elementACopier.m_clip_rects},
    m_current_clip_rect{0}, m_lastAnimationTime{system_clock::now() }
{
    this->setTextureRect(m_clip_rects[m_current_clip_rect]);
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
 Synchronization Function : change animation
*********************************************
    Arthur : 3/03 - 30/03
*********************************************/
void AnimatedGraphicElement::sync()
{
    //=== Change Animation

    system_clock::duration duration = system_clock::now() - m_lastAnimationTime;

    if ( duration > milliseconds(200) )
    {

        if (m_current_clip_rect == m_clip_rects.size()-1)
            m_current_clip_rect = 0;
        else
            m_current_clip_rect++;

        this->setTextureRect(m_clip_rects[m_current_clip_rect]);

        m_lastAnimationTime = system_clock::now();
    }
}
