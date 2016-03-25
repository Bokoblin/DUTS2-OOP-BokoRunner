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
    m_Vx = 0;
    m_Vy =0;
    m_realposX=0.;
    m_realposY=0.;
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
    clock_t Ball::getStartTimeJump() const{ return m_time_start_jump;}

/********************************************
    Setters
*********************************************
    Florian : 17/03 - 23/03
*********************************************/
    void Ball::setFlyingState(bool etat) {m_flying = etat;}
    void Ball::setJumpState(bool etat) {m_jumping = etat;}
    void Ball::setStartTimeJump(clock_t time){ m_time_start_jump = time;}




/********************************************
    Ball Moving
*********************************************
    Arthur : 10/02
*********************************************/
void Ball::move()
{

    if (m_jumping /*|| m_flying*/)
                                    {

        calculVector();
        RealPosition();
        Trajectory();
    }
}

/********************************************
    Ball vector calcul
*********************************************
   Florian : 12/03
*********************************************/

void Ball::calculVector()
{
    m_Vx = cos(1.0*m_angle)*m_moveX;
    m_Vy = sin(1.0*m_angle)*m_moveY;
}


/********************************************
    Ball Real position calcul
*********************************************
   Florian : 12/03 - 23/03
*********************************************/

void Ball::RealPosition()
{
   double tempsCourant =(clock() - m_time_start_jump)/(double)CLOCKS_PER_SEC;
   m_realposX=(double)(m_Vx*(tempsCourant));
   m_realposY=(double)((m_Vy*(tempsCourant))-((m_gravitation*(tempsCourant*tempsCourant))/2000));
   cout<< m_realposX << "               :              "<< m_realposY<<endl;

}


/********************************************
    Ball Trajectory calcul
*********************************************
   Florian : 12/03
*********************************************/

void Ball::Trajectory()
{
    bool taper = false;
    if(m_posY > 298 && !taper)
    {
         m_posX = m_posX + m_realposX;
         m_posY = m_posY - m_realposY;
    }
    else if(m_posY == 298)
    {
        m_posX = m_posX + m_realposX;
        m_posY = m_posY + m_realposY;
        taper = true;
    }
    if(taper && m_posY>550)
    {
        m_posX = m_posX + m_realposX;
        m_posY = m_posY + m_realposY;
    }




}













