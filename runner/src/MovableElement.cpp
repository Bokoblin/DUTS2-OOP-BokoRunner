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

#include "MovableElement.h"

//=======================================
// Constructeur
//=======================================
MovableElement::MovableElement() : m_posX(rand()%800), m_posY(450), m_width(20), m_height(20)
{

}

//=======================================
// Destructeur
//=======================================
MovableElement::~MovableElement()
{

}

//=======================================
// Accesseurs en lecture
//=======================================
int MovableElement::getMoveX() const { return m_moveX; }
int MovableElement::getMoveY() const { return m_moveY; }
int MovableElement::getPosX()   const { return m_posX;    }
int MovableElement::getPosY()   const { return m_posY;    }
int MovableElement::getWidth()  const { return m_width;   }
int MovableElement::getHeight()const { return m_height;  }

//=======================================
// Accesseurs en écriture
//=======================================
void MovableElement::setPositionX(int x) { m_posX = x; }
void MovableElement::setPositionY(int y) { m_posX = y; }
