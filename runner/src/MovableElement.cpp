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
    Arthur : 23/02 - 10/03
    Florian: 02/03 - 02/03
*********************************************/
MovableElement::MovableElement(int posX, int posY, int w, int h, int mvX, int mvY) :
    m_posX{posX}, m_posY{posY}, m_width{w}, m_height{h}, m_moveX{mvX}, m_moveY{mvY}, m_collisionState{false}
{

}


/********************************************
    Getters
*********************************************
    Arthur : 23/02 - 20/03
*********************************************/
int MovableElement::getMoveX() const { return m_moveX; }
int MovableElement::getMoveY() const { return m_moveY; }
int MovableElement::getPosX()  const { return m_posX;  }
int MovableElement::getPosY()  const { return m_posY;  }
int MovableElement::getWidth() const { return m_width; }
int MovableElement::getHeight()const { return m_height;}
bool MovableElement::getCollisionState() const { return m_collisionState; }

/********************************************
    Setters
*********************************************
    Arthur : 23/02 - 22/03
*********************************************/
void MovableElement::setPosX(int x) { m_posX = x; }
void MovableElement::setPosY(int y) { m_posX = y; }
void MovableElement::setCollisionState(bool collisionState) { m_collisionState = collisionState;}
void MovableElement::setLife(int newLife) {}


/********************************************
   check if a position belongs to the current
   ennemy position
*********************************************
    Arthur : 8/03 - 12/03
*********************************************/
bool MovableElement::contains( const int posX, const int posY) const
{
    int  maxX = m_posX + m_width;
    int  maxY = m_posY + m_height;

    return (posX >= m_posX) && (posX < maxX) && (posY >= m_posY) && (posY < maxY);
}

/********************************************
    String transforming function
*********************************************
    Arthur : 23/02 - 02/03
*********************************************/
std::string MovableElement::to_string() const
{
    std::string texte = "X : " + std::to_string(m_posX) +"  ,  Y : " +  std::to_string(m_posY);
    return texte;
}
