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

#include "../header/MovableElement.h"

/********************************************
    Parameterized Constructor
*********************************************
    Arthur : 23/02 - 02/03
    Florian: 02/03 - 02/03
*********************************************/
MovableElement::MovableElement(int posX, int posY, int w, int h, int mvX, int mvY) :
    m_posX{posX}, m_posY{posY}, m_width{w}, m_height{h}, m_moveX{mvX}, m_moveY{mvY}
{

}


/********************************************
    Destructor
*********************************************
    Arthur : 23/02 - 02/03
*********************************************/
//=======================================
// Destructor
//=======================================
MovableElement::~MovableElement()
{

}

/********************************************
    Getters
*********************************************
    Arthur : 23/02 - 23/02
*********************************************/
int MovableElement::getMoveX() const { return m_moveX; }
int MovableElement::getMoveY() const { return m_moveY; }
int MovableElement::getPosX()  const { return m_posX;  }
int MovableElement::getPosY()  const { return m_posY;  }
int MovableElement::getWidth() const { return m_width; }
int MovableElement::getHeight()const { return m_height;}

/********************************************
    Setters
*********************************************
    Arthur : 23/02 - 23/03
*********************************************/
void MovableElement::setPositionX(int x) { m_posX = x; }
void MovableElement::setPositionY(int y) { m_posX = y; }


/********************************************
    String transforming function
*********************************************
    Arthur : 23/02 - 02/03
*********************************************/
std::string MovableElement::to_string() const
{
    std::string texte = "POS_X : " + std::to_string(m_posX) +"  ,  POS_Y : " +  std::to_string(m_posY);
    return texte;
}
