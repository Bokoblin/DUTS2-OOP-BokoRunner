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

#ifndef MOVABLEELEMENT_H
#define MOVABLEELEMENT_H

#include <string>
#include <ctime>

/********************************************
    MovableElement Class
*********************************************
    Arthur : 23/02 - 13/03
    Florian: 02/03 - 02/03
*********************************************/
class MovableElement
{
public:
    //=== CTORs / DTORs
    MovableElement(int posX, int posY, int w, int h, int mvX, int mvY, int type);
    //~MovableElement();
    virtual ~MovableElement() {}

    //=== METHODS
    virtual void move() {} //defining it as virtual allows to override it
    bool contains( const int posX, const int posY) const ;
    std::string to_string()const ;

    //=== GETTERS
    int getMoveX() const;
    int getMoveY() const;
    int getPosX() const;
    int getPosY() const;
    int getWidth() const;
    int getHeight() const;
    int getType() const;
    virtual bool getJumpState() const{return false;}
    virtual bool getFlyingState() const{return false;}
    virtual bool getDecelerationState() const {return false;}
    virtual clock_t getStartTimeJump() const{return -1;}
    virtual std::pair<float,float> getVector() const {}
    float getVectorY() const {}


    //=== SETTERS
    void setPositionX(int x);
    void setPositionY(int y);
    virtual void setJumpState(bool newState){}
    virtual void setFlyingState(bool newState){}
    virtual void setDecelerationState(bool newState) {};
    virtual void setStartTimeJump (clock_t time) {}
    virtual void setVector(float x, float y){}
    virtual void setVectorY(float y){}
    virtual void MoveRight(){}
    virtual void MoveLeft(){}
    virtual void Deceleration(){}


protected:
    //=== ATTRIBUTES
    int m_posX;
    int m_posY;
    int m_width;
    int m_height;
    int m_moveX;
    int m_moveY;
    int m_typeElement; //0 for Ball, 1 for obstacles, 2 for bonuses
};

#endif // MOVABLEELEMENT_H
