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
Ball::Ball(int posX, int posY, int w, int h, int mvX, int mvY) :
    MovableElement(posX, posY, w, h, mvX, mvY, 0)
{
    m_enSaut = false;
    m_enVol = false;
    m_Vx = 0;
    m_Vy =0;
    m_realposX=0;
    m_realposY=0;
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
    Florian : 17/03
*********************************************/
    bool Ball::getEtatVol() const {return m_enVol;}
    bool Ball::getEtatSaut() const {return m_enSaut;}

/********************************************
    Setters
*********************************************
    Florian : 17/03
*********************************************/
    void Ball::setEtatVol(bool etat) {m_enVol = etat;}
    void Ball::setEtatSaut(bool etat) {m_enSaut = etat;}



/********************************************
    Ball Moving
*********************************************
    Arthur : 10/02
*********************************************/
void Ball::move(clock_t temps_DebutSaut)
{
    if (m_enSaut || m_enVol)
    {
    calculVector();
    RealPosition(temps_DebutSaut);
    Trajectory();
    }
}

void Ball::calculVector()
{
    m_Vx = cos(1.0*m_angle)*m_moveX;
    m_Vy = sin(1.0*m_angle)*m_moveY;
}

void Ball::RealPosition(clock_t temps_DebutSaut)
{
   double tempsCourant = (clock() - temps_DebutSaut)-(double)CLOCKS_PER_SEC;
   m_realposX=(double)(m_Vx*tempsCourant);
   m_realposY=(double)((m_Vy*tempsCourant)-((m_gravitation*tempsCourant*tempsCourant)/2000));
}

void Ball::Trajectory()
{
    m_posX += m_realposX;
    m_posY += m_realposY;
}



