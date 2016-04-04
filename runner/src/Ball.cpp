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

#include "../header/Ball.h"

using namespace std;

/********************************************
    Parameterized Constructor
*********************************************
    Arthur : 22/02 - 02/03
    Florian: 22/02 - 02/03
*********************************************/
Ball::Ball(float posX,float posY, int w, int h, int mvX, int mvY) :
    MovableElement(posX, posY, w, h, mvX, mvY, 0)
{
    m_jumping = false;
    m_flying = false;
    m_vectorBall.first=0;
    m_vectorBall.second=0;
}

/********************************************
    Destructor
*********************************************
    Arthur : 23/02 - 22/02
    Florian: 22/02 - 22/02
*********************************************/
Ball::~Ball()
{

}


/********************************************
    Getters
*********************************************
    Florian : 17/03 - 23/03
*********************************************/
    bool Ball::getFlyingState() const {return m_flying;}
    bool Ball::getJumpState() const {return m_jumping;}
    bool Ball::getDecelerationState() const {return m_deceleration;}
    clock_t Ball::getStartTimeJump() const{ return m_time_start_jump;}

    pair<float,float> Ball::getVector() const { return m_vectorBall; }
    float Ball::getVectorY() const { return m_vectorBall.second; }

/********************************************
    Setters
*********************************************
    Florian : 17/03 - 23/03
*********************************************/
    void Ball::setFlyingState(bool etat) {m_flying = etat;}
    void Ball::setJumpState(bool etat) {m_jumping = etat;}
    void Ball::setDecelerationState(bool etat) {m_deceleration = etat;}
    void Ball::setStartTimeJump(clock_t time){ m_time_start_jump = time;}
    void Ball::setVectorY(float y){ m_vectorBall.second = y;}

    void Ball::setVector(float x,float y)
    {
        m_vectorBall.first = x;
        m_vectorBall.second = y;
    }


/********************************************
    Ball Moving
*********************************************
    Arthur : 10/02
*********************************************/
void Ball::move()
{
    m_posX += m_vectorBall.first;
    m_posY += m_vectorBall.second;

    if(m_deceleration)
    {
       /* if(m_vectorBall.first < 0.0001 && m_vectorBall.first > -0.0001)
            m_vectorBall.first =0;*/

        m_vectorBall.first /= 1+MOVE_SPEED*1.0/FRAMERATE;


    }

    if(m_jumping)
    {
           m_vectorBall.second = -JUMP_SPEED;
    }

    if(m_flying)
    {
       // m_vectorBall.second += m_gravitation/FRAMERATE;
       // m_posY+= m_vectorBall.second*1.0/FRAMERATE;

    }


}





void Ball::MoveRight()
{
    cout << m_moveX << endl;
    m_vectorBall.first += MOVE_SPEED*ACCELERATION*1.0/FRAMERATE;
    cout << m_moveX << endl;
}

void Ball::MoveLeft()
{
    m_vectorBall.first += -MOVE_SPEED*ACCELERATION*1.0/FRAMERATE;
}

void Ball::Deceleration()
{
    m_vectorBall.first /= 1+MOVE_SPEED*1.0/FRAMERATE;

}

void Ball::Jump()
{
    m_vectorBall.second = -JUMP_SPEED;

}
















