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
    Arthur : 23/02 - 09/04
    Florian: 02/03 - 02/03
*********************************************/
MovableElement::MovableElement(float x, float y, unsigned int w, unsigned int h, float mvX, float mvY) :
    m_posX{x}, m_posY{y}, m_width{w}, m_height{h}, m_moveX{mvX}, m_moveY{mvY}, m_collisionState{false}
{

}


/********************************************
    Destructor
*********************************************
    Arthur : 23/02
*********************************************/
MovableElement::~MovableElement()
{}


/********************************************
    Getters
*********************************************
    Arthur : 23/02 - 09/04
*********************************************/
float MovableElement::getMoveX() const { return m_moveX; }
float MovableElement::getMoveY() const { return m_moveY; }
float MovableElement::getPosX()  const { return m_posX;  }
float MovableElement::getPosY()  const { return m_posY;  }
unsigned int MovableElement::getWidth() const { return m_width; }
unsigned int MovableElement::getHeight()const { return m_height;}
bool MovableElement::getCollisionState() const { return m_collisionState; }
unsigned int MovableElement::getLife() const { return m_life; }


/********************************************
    Setters
*********************************************
    Arthur  : 23/02 - 09/04
*********************************************/
void MovableElement::setPosX(float x) { m_posX = x; }
void MovableElement::setPosY(float y) { m_posX = y; }
int MovableElement::getType() const { return m_elementType; }
void MovableElement::setCollisionState(bool state) { m_collisionState = state;}
void MovableElement::setLife(unsigned int life) {}


/********************************************
   check if a position belongs to the current
   ennemy position
*********************************************
    Arthur  : 08/03 - 09/04
*********************************************/
bool MovableElement::contains( float posX, float posY) const
{
    float  maxX = m_posX + m_width;
    float  maxY = m_posY + m_height;

    return (posX >= m_posX) && (posX < maxX) && (posY >= m_posY) && (posY < maxY);
}


bool MovableElement::collision( const MovableElement& other) const
{
    return ( this->contains( other.getPosX(), other.getPosY() )
        || this->contains( other.getPosX() + other.getWidth(), other.getPosY() )
        || this->contains( other.getPosX(), other.getPosY()+ other.getHeight() )
        || this->contains( other.getPosX() + other.getWidth(), other.getPosY() + other.getHeight() ) );
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
