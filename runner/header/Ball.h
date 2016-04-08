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
#include <iostream>

const double PI = 3.14159265358979;
const float GRAVITATION = 20;
const double ANGLE=PI/3;
const float ACCELERATION = 10.0;
const float MOVE_SPEED = 2.0; //force accordée à l'objet pour le déplacement horizontal
const float JUMP_SPEED = 12.0; //force accordée à l'objet pour le saut
const int FRAMERATE = 30;
const int GAME_FLOOR = 480;
const float PRECISION = 1E-1;

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
   Ball(float posX,float posY, int w, int h, int mvX, int mvY);
    ~Ball();

    //=== GETTERS
    virtual bool getFlyingState() const override;
    virtual bool getJumpState() const override;
    virtual bool getDecelerationState() const override;
    virtual clock_t getStartTimeJump() const override;
    virtual std::pair<float,float> getVector() const;
    virtual float getVectorY() const;
    virtual float getVectorX() const;


    //===SETTERS
    virtual void setFlyingState(bool etat) override;
    virtual void setJumpState(bool etat) override;
    virtual void setDecelerationState(bool etat) override;
    virtual void setStartTimeJump(clock_t time) override;
    virtual void setVector(float x,float y);
    virtual void setVectorY(float y);
    virtual void setVectorX(float x);


    //=== METHODS
    virtual void move() override;
    void calculVector();
    void RealPosition();
    void Trajectory();
    void MoveRight() override;
    void MoveLeft() override;
    void Deceleration();
    void Jump();



private:
    bool m_jumping;
    bool m_flying;
    bool m_deceleration;
    double m_Vx;
    double m_Vy;
    float m_realposX;
    float m_realposY;
    clock_t m_time_start_jump;
    std::pair<float,float> m_vectorBall;
};

#endif // BALL_H
