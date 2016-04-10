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
#include <math.h>


const int GAME_FLOOR = 480;
const float GRAVITATION = 20;
const float ACCELERATION = 10.0;
const int FRAMERATE = 30;
const int JUMP_LIMIT = 380;
const float PRECISION = 1.0;

/********************************************
    Player Class
*********************************************
    Arthur : 22/02 - 9/04
    Florian: 22/02 - 10/04
*********************************************/
class Player : public MovableElement
{
public:
    //=== CTORs / DTORs
   Player(float posX,float posY, unsigned int w, unsigned int h, float mvX, float mvY);
    virtual ~Player();

    //=== GETTERS
    bool getFlyingState() const;
    bool getJumpState() const;
    bool getDecelerationState() const;
    std::pair<float,float> getVector() const;

    //=== SETTERS
    virtual void setLife(unsigned int new_life) ;
    void setFlyingState(bool etat);
    void setJumpState(bool etat);
    void setDecelerationState(bool etat);

    //=== METHODS
    virtual void move() override;
    void controlPlayerMovements(bool left);


private:
    bool m_jumping;
    bool m_flying;
    bool m_inDeceleration;
    std::pair<float,float> m_vectorBall;
};

#endif // BALL_H
