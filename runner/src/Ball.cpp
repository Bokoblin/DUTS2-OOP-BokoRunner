/*
Copyright (C) 2015 Jolivet Arthur & Laronze Florian

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

#include "../header/Ball.h"
#include <iostream>

using namespace std;

//=======================================
// Constructeur
//=======================================
Ball::Ball()
{
    m_posX = 50, m_posY = 450;
    m_width = 50, m_height = 50;
    m_moveX = 10, m_moveY = 10;
}


//=======================================
// Destructeur
//=======================================
Ball::~Ball()
{
    //dtor
}


//=======================================
// Accesseurs en lecture
//=======================================
int Ball::getMoveX() { return m_moveX; }
int Ball::getMoveY() { return m_moveY; }
int Ball::getPositionX() { return m_posX; }
int Ball::getPositionY() { return m_posY; }


//=======================================
// Accesseurs en écriture
//=======================================
void Ball::setPositionX(int x) { m_posX = x; }
void Ball::setPositionY(int y) { m_posX = y; }
