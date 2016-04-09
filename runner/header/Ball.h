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
    Ball Class
*********************************************
    Arthur : 22/02 - 8/04
    Florian: 22/02 - 6/04
*********************************************/
class Ball : public MovableElement
{
public:
    //=== CTORs / DTORs
   Ball(float posX,float posY, int w, int h, float mvX, float mvY);
    ~Ball();

    //=== GETTERS
    virtual int getType() const override { return 0;}
    virtual int getLife() const override {return m_life;}
    virtual bool getFlyingState() const override;
    virtual bool getJumpState() const override;
    virtual bool getDecelerationState() const override;
    virtual std::pair<float,float> getVector() const override;

    //=== SETTERS
    virtual void setLife(int new_life) override ;
    virtual void setFlyingState(bool etat) override;
    virtual void setJumpState(bool etat) override;
    virtual void setDecelerationState(bool etat) override;

    //=== METHODS
    virtual void move() override;
    virtual void controlPlayerMovements(bool left) override;


private:
    int m_life;
    bool m_jumping;
    bool m_flying;
    bool m_inDeceleration;
    std::pair<float,float> m_vectorBall;
};

#endif // BALL_H
