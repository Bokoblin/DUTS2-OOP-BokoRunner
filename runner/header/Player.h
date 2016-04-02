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

#ifndef BALL_H
#define BALL_H

#include "MovableElement.h"
#include <string>


/********************************************
    Player Class
*********************************************
    Arthur : 22/02 - 20/03
    Florian: 22/02 - 02/03
*********************************************/
class Player : public MovableElement
{
public:
    //=== CTORs / DTORs
    Player(unsigned int posX, unsigned int posY,
        unsigned int w, unsigned int h, int mvX, int mvY);
    virtual ~Player();

    //=== GETTERS
    virtual int getType() const override { return 0;}
    virtual unsigned int getLife() const override {return m_life;}

    //=== SETTERS
    virtual void setLife(unsigned int new_life) override ;

    //=== METHODS
    virtual void move() override;

private:
    unsigned int m_life;
};

#endif // BALL_H
