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
    Arthur : 23/02 - 08/04
    Florian: 02/03 - 06/04
*********************************************/
class MovableElement
{
public:
    //=== CTORs / DTORs
    MovableElement(float posX, float posY, int w, int h, float mvX, float mvY);
    virtual ~MovableElement() {}

    //=== METHODS
    virtual void move() {} //defining it as virtual allows to override it
    bool contains( const int posX, const int posY) const ;
    std::string to_string()const ;

    //=== GETTERS
    float getPosX() const;
    float getPosY() const;
    float getMoveX() const;
    float getMoveY() const;
    int getWidth() const;
    int getHeight() const;
    bool getCollisionState() const;
    virtual int getType() const {return -1;}
    virtual int getEnemyType() const {return -1;}
    virtual int getLife() const {return -1;}
    virtual bool getJumpState() const{return false;}
    virtual bool getFlyingState() const{return false;}
    virtual bool getDecelerationState() const {return false;}
    virtual std::pair<float,float> getVector() const {}


    //=== SETTERS
    void setPosX(float x);
    void setPosY(float y);
    virtual void setJumpState(bool newState){}
    virtual void setFlyingState(bool newState){}
    virtual void setDecelerationState(bool newState) {};
    virtual void setStartTimeJump (clock_t time) {}
    virtual void setVector(float x, float y){}
    virtual void controlPlayerMovements(bool left) {}
    void setCollisionState(bool collisionState);
    virtual void setLife(int newLife);


protected:
    //=== ATTRIBUTES
    float m_posX;
    float m_posY;
    int m_width;
    int m_height;
    float m_moveX;
    float m_moveY;
    int m_typeElement; //0 for Ball, 1 for obstacles, 2 for bonuses
    bool m_collisionState;
};

#endif // MOVABLEELEMENT_H
