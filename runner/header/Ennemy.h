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

#ifndef ENNEMY_H
#define ENNEMY_H

#include "MovableElement.h"
#include <string>


/********************************************
    Ennemy Class
*********************************************
    Arthur : 13/03
*********************************************/
class Ennemy : public MovableElement
{
public:
    //=== CTORs / DTORs
    Ennemy(int posX, int posY, int w, int h);
    ~Ennemy();

    //=== METHODS
    void move();
    void chooseEnnemyType();

private:
    int m_ennemyType; // 0: simple ennemy, 1: 3-ennemy-totem, 3: 4-ennemy-block 
};

#endif // ENNEMY_H
