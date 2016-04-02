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

#include "../header/Coin.h"

using namespace std;

/********************************************
    Parameterized Constructor
*********************************************
    Arthur : 19/03
*********************************************/
Coin::Coin(unsigned int posX, unsigned int posY, unsigned int w, unsigned int h,
        int mvX, int mvY) : MovableElement(posX, posY, w, h, mvX, mvY)
{

}


/********************************************
    Destructor
*********************************************
    Arthur : 19/03
*********************************************/
Coin::~Coin()
{

}

/********************************************
    Coin Moving
*********************************************
    Arthur : 19/03
*********************************************/
void Coin::move()
{
    m_posX += m_moveX;
    m_posY += m_moveY;
}
