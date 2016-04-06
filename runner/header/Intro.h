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

#ifndef INTRO_H
#define INTRO_H

#include "View.h"
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <string>
#include <cassert>
#include <ctime>
#include "SFML/Graphics.hpp"

/********************************************
    Constant Variables
********************************************/
const std::string INTRO_IMAGE = "Images/intro.png";


/********************************************
    Intro Class
*********************************************
    Arthur : 27/03
*********************************************/
class Intro : public View
{
    public:
    //=== CTORs / DTORs
    Intro(unsigned int w, unsigned int h, sf::RenderWindow *window);
    virtual ~Intro();

    //=== METHODS
    virtual void synchronize() override;
    virtual void draw() const override;
    virtual void loadImages() override;
    virtual bool treatEvents() override;

private:
    //=== ATTRIBUTES
    sf::Texture m_introTexture;
    GraphicElement *m_introGraphic;
};

#endif // INTRO_H
