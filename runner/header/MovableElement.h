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

/********************************************
    MovableElement Abstract Class
*********************************************
    Arthur : 23/02 - 05/04
    Florian: 02/03 - 02/03
*********************************************/
class MovableElement
{
public:
    //=== CTORs / DTORs
    MovableElement(unsigned int x, unsigned int y,
                    unsigned int w, unsigned int h, int mvX, int mvY);
    virtual ~MovableElement();

    //=== METHODS
    virtual void move()=0;
    bool contains( const unsigned int posX, const  unsigned int posY) const ;
    bool collision( const MovableElement & other) const ;
    std::string to_string()const ;

    //=== GETTERS
    unsigned int getPosX() const;
    unsigned int getPosY() const;
    unsigned int getWidth() const;
    unsigned int getHeight() const;
    int getMoveX() const;
    int getMoveY() const;
    bool getCollisionState() const;
    virtual int getType() const;
    virtual unsigned int getLife() const;


    //=== SETTERS
    void setPosX(unsigned int x);
    void setPosY(unsigned int y);
    void setCollisionState(bool collisionState);
    virtual void setLife(unsigned int newLife);

protected:
    //=== ATTRIBUTES
    unsigned int m_posX;
    unsigned int m_posY;
    unsigned int m_width;
    unsigned int m_height;
    int m_moveX;
    int m_moveY;
    bool m_collisionState;
    unsigned int m_life;
    int m_elementType;
    /** Element Type :
    0 : Player
    1 : Standard Enemy
    2 : Totem Enemy
    3 : Block Enemy
    4 :  Coins
    */

};

#endif // MOVABLEELEMENT_H
