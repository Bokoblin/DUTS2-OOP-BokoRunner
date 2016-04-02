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

#ifndef _VIEW_H
#define _VIEW_H

#include "Text.h"
#include "Model.h"
#include "GraphicElement.h"
#include <SFML/Graphics.hpp>

#include <cstdlib>
#include <sstream>
#include <iostream>
#include <string>


/********************************************
    Constant Variables
********************************************/
const std::string BACKGROUND_IMAGE_1 = "Images/city_1.png";
const std::string BACKGROUND_IMAGE_2 = "Images/city_2.png";

class Model;

/********************************************
    View Class
*********************************************
    Arthur : 21/02 - 27/03
    Florian: 21/02 - 3/03
*********************************************/
class View
{
public:
    //=== CTORs / DTORs
    View(unsigned int w, unsigned int h, sf::RenderWindow *window);
    ~View();

    //=== GETTERS
    sf::RenderWindow* getWindow();

    //=== SETTERS
    void setModel(Model *model);

    //=== METHODS
    virtual void loadImages();
    virtual void synchronize();
    virtual void draw();
    virtual bool treatEvents();

protected:
    //=== ATTRIBUTES
    unsigned int m_width, m_height;
    sf::RenderWindow *m_window;
    Model *m_model;
    Text m_text;
};

#endif
