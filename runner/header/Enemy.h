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
    Enemy Class
*********************************************
    Arthur : 13/03 - 15/03
*********************************************/
class Enemy : public MovableElement
{
public:
    //=== CTORs / DTORs
    Enemy(int posX, int posY, int w, int h, int movX, int movY);
    ~Enemy();

    //=== GETTERS
    int getEnemyType() const;

    //=== METHODS
    void move();
    void chooseEnemyType();

private:
    int m_enemyType; // 0: simple ennemy, 1: 3-ennemy-totem, 3: 4-ennemy-block
};

#endif // ENNEMY_H
