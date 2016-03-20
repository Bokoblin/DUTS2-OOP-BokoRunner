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
#include <ctime>

const double m_pi = 3.14159265358979;
const double m_gravitation = 9.81;
const double m_angle=m_pi/3;;


/********************************************
    Ball Class
*********************************************
    Arthur : 22/02 - 13/03
    Florian: 22/02 - 02/03
*********************************************/
class Ball : public MovableElement
{
public:
    //=== CTORs / DTORs
   Ball(int posX, int posY, int w, int h, int mvX, int mvY);
    ~Ball();

    //=== GETTERS
    bool getEtatVol() const;
    bool getEtatSaut() const;

    //===SETTERS
    void setEtatVol(bool etat);
    void setEtatSaut(bool etat);

    //=== METHODS
    void move(clock_t temps_DebutSaut);
    void calculVector();
    void RealPosition(clock_t temps_DebutSaut);
    void Trajectory();


private:
    bool m_enSaut;
    bool m_enVol;
    double m_Vx;
    double m_Vy;
    int m_realposX;
    int m_realposY;
};

#endif // BALL_H
