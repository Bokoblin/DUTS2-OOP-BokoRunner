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

#include "../header/Button.h"

/********************************************
    Parameterized Constructor
*********************************************
    Arthur : 6/04
*********************************************/
Button::Button(const std::vector<sf::IntRect> & clipRects,
        sf::Texture &image, float x, float y, unsigned int w, unsigned int h):
    GraphicElement(image, x, y, w, h), m_clipRectsArray{clipRects}, m_currentClipRect{0}, m_pressedState{false}
{
    this->setTextureRect(m_clipRectsArray[m_currentClipRect]);
}


/********************************************
    Copy Constructor
*********************************************
    Arthur : 6/04
*********************************************/
Button::Button(Button const& elementACopier) :
    GraphicElement(elementACopier), m_clipRectsArray{elementACopier.m_clipRectsArray},
    m_currentClipRect{0}, m_pressedState{false}
{
    this->setTextureRect(m_clipRectsArray[m_currentClipRect]);
}


/********************************************
    Destructor
*********************************************
    Arthur : 6/04
*********************************************/
Button::~Button()
{}


/********************************************
    Setters
*********************************************
    Arthur : 6/04
*********************************************/
void Button::setPressedState(bool state) { m_pressedState = state; }


/********************************************
    Synchronization Function : change animation
*********************************************
    Arthur : 6/04
*********************************************/
void Button::sync()
{
    if ( m_pressedState == false )
        m_currentClipRect = 0;
    else
        m_currentClipRect = 1;

    this->setTextureRect(m_clipRectsArray[m_currentClipRect]);
}
