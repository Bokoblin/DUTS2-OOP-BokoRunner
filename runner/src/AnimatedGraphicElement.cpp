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
    Arthur : 3/03 - 3/03
*********************************************/
AnimatedGraphicElement::AnimatedGraphicElement(const std::vector<sf::IntRect> & clipRects,
                                               sf::Texture &image, int x, int y, int w, int h):
    m_clip_rects{clipRects}, GraphicElement(image, x, y, w, h), m_current_clip_rect{0}, m_nb_steps{0}
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
    Synchronization and drawing Function
*********************************************
    Arthur : 3/03 - 3/03
*********************************************/
void AnimatedGraphicElement::syncAndDraw(sf::RenderWindow *window)
{
    //=== Sync
    if (m_nb_steps%5 == 0) // each 5 function calls
    {
        this->setTextureRect(m_clip_rects[m_current_clip_rect]);
        if (m_current_clip_rect == 7)
            m_current_clip_rect = 0;
        else
            m_current_clip_rect++;
        m_nb_steps = 0;
    }
    m_nb_steps++;

    //=== Draw
    window->draw(*this);
}
