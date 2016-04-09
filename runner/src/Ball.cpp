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
    Arthur : 22/02 - 09/03
    Florian: 22/02 - 06/03
*********************************************/
Ball::Ball(float posX, float posY, int w, int h, float mvX, float mvY) :
    MovableElement(posX, posY, w, h, mvX, mvY), m_life{100},
    m_jumping{false}, m_flying{false}, m_inDeceleration{false}
{
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
    Arthur :  20/03 - 9/04
    Florian : 17/03 - 6/04
*********************************************/
bool Ball::getFlyingState() const { return m_flying; }
bool Ball::getJumpState() const { return m_jumping; }
bool Ball::getDecelerationState() const { return m_inDeceleration; }
pair<float,float> Ball::getVector() const { return m_vectorBall; }


/********************************************
    Setters
*********************************************
    Arthur :  08/04 - 09/04
    Florian : 17/03 - 6/04
*********************************************/
void Ball::setFlyingState(bool etat) { m_flying = etat; }
void Ball::setJumpState(bool etat) {  m_jumping = etat; }
void Ball::setDecelerationState(bool etat) {  m_inDeceleration = etat; }

void Ball::setLife(int new_life)
{
    m_life = new_life;
    if (m_life < 0)
        m_life = 0;
}


/********************************************
    Ball Moving
*********************************************
    Arthur :  8/04 - 9/04
    Florian : 12/03 - 6/04
*********************************************/
void Ball::move()
{
    m_flying =m_width < GAME_FLOOR - m_height;

    if (m_posY < JUMP_LIMIT)
        m_jumping = false;

    if(m_inDeceleration == true)
    {
        if(fabs(m_vectorBall.first) < PRECISION)
        {
            m_vectorBall.first =0;
            m_inDeceleration = false;
        }
        m_vectorBall.first /= 1+m_moveX/FRAMERATE;
    }

    if(m_jumping)
    {
        m_vectorBall.second = -m_moveY*GRAVITATION/FRAMERATE;
        m_posY+= m_vectorBall.second/FRAMERATE;
    }

    if(m_flying)
    {
        m_vectorBall.second += GRAVITATION/FRAMERATE;
        m_posY+= m_vectorBall.second/FRAMERATE;
    }

    if( m_posY == GAME_FLOOR - m_height && m_flying == true)
    {
        m_flying =false;
        m_jumping=false;
        m_posY = GAME_FLOOR - m_height;
    }
    if(m_posY > GAME_FLOOR - m_height )
    {
        m_vectorBall.second = 0;
        m_posY = GAME_FLOOR - m_height;
    }

   //Update ball position

    if ( m_posX + m_vectorBall.first >= 0 && (m_posX + m_width + m_vectorBall.first) <= 900 )
    {
        m_posX += m_vectorBall.first;
    }
    else if (m_posX + m_vectorBall.first < 0 )
    {
        m_posX = 0;
    }
    else
        m_posX = 900 - m_width;

    m_posY += m_vectorBall.second;
}


/********************************************
    Ball Control
*********************************************
    Arthur :  8/04 - 9/04
    Florian : 22/03 - 6/04
*********************************************/
void Ball::controlPlayerMovements(bool left)
{
    m_inDeceleration = false;
    if (left == true)
        m_vectorBall.first -= m_moveX*ACCELERATION/FRAMERATE;
    else
        m_vectorBall.first += m_moveX*ACCELERATION/FRAMERATE;
}

