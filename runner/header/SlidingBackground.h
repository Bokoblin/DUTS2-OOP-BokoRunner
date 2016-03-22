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

#ifndef SLIDINGBACKGROUND_H
#define SLIDINGBACKGROUND_H

#include "GraphicElement.h"


/********************************************
    SlidingBackground Class
*********************************************
    Arthur : 3/03 - 5/03
    Florian: 3/03 - 3/03
*********************************************/
class SlidingBackground
{
public:
    //=== CTORs / DTORs
    SlidingBackground(sf::Texture &image, int w, int h, unsigned int speed);
    virtual ~SlidingBackground();

    //=== METHODS
    void syncAndDraw(sf::RenderWindow &window);

    //=== SETTERS
    void setSpeed(unsigned int speed);


private:
    //=== ATTRIBUTES
    GraphicElement *m_left, *m_right;
    int m_width, m_height;
    unsigned int m_speed;

};

#endif // SLIDINGBACKGROUND_H