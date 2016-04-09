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

#include "../header/Player.h"
#include <iostream>
using namespace std;

/********************************************
    Parameterized Constructor
*********************************************
    Arthur : 22/02 - 09/04
    Florian: 22/02 - 06/04
*********************************************/
Player::Player(float posX, float posY, unsigned int w, unsigned int h, float mvX, float mvY) :
    MovableElement(posX, posY, w, h, mvX, mvY),
    m_jumping{false}, m_flying{false}, m_inDeceleration{false}
{
    m_elementType = 0;
    m_life  = 100;
    m_vectorBall.first = 0;
    m_vectorBall.second = 0;
}

/********************************************
    Destructor
*********************************************
    Arthur : 23/02 - 22/02
    Florian: 22/02 - 22/02
*********************************************/
Player::~Player()
{}


/********************************************
    Getters
*********************************************
    Arthur :  20/03 - 9/04
    Florian : 17/03 - 6/04
*********************************************/
bool Player::getFlyingState() const { return m_flying; }
bool Player::getJumpState() const { return m_jumping; }
bool Player::getDecelerationState() const { return m_inDeceleration; }
pair<float,float> Player::getVector() const { return m_vectorBall; }


/********************************************
    Setters
*********************************************
    Arthur :  08/04 - 09/04
    Florian : 17/03 - 6/04
*********************************************/
void Player::setFlyingState(bool etat) { m_flying = etat; }
void Player::setJumpState(bool etat) {  m_jumping = etat; }
void Player::setDecelerationState(bool etat) {  m_inDeceleration = etat; }

void Player::setLife(unsigned int new_life)
{
    if ( m_life <= new_life)
        m_life = 0;
    else
        m_life = new_life;
}


/********************************************
    Ball Moving
*********************************************
    Arthur :  8/04 - 9/04
    Florian : 12/03 - 6/04
*********************************************/
void Player::move()
{
    m_flying =m_width < GAME_FLOOR;

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

    if( m_posY == GAME_FLOOR && m_flying == true)
    {
        m_flying =false;
        m_jumping=false;
        m_posY = GAME_FLOOR;
    }
    if(m_posY > GAME_FLOOR )
    {
        m_vectorBall.second = 0;
        m_posY = GAME_FLOOR;
    }

   //=== Update ball position

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
    Player Control
*********************************************
    Arthur :  8/04 - 9/04
    Florian : 22/03 - 6/04
*********************************************/
void Player::controlPlayerMovements(bool left)
{
    m_inDeceleration = false;
    if (left == true)
        m_vectorBall.first -= m_moveX*ACCELERATION/FRAMERATE;
    else
        m_vectorBall.first += m_moveX*ACCELERATION/FRAMERATE;
}

