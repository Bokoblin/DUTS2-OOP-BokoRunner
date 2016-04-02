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

#ifndef MENU_H
#define MENU_H

#include "View.h"
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <string>
#include <cassert>
#include <ctime>
#include "SFML/Graphics.hpp"
#include "SlidingBackground.h"

/********************************************
    Constant Variables
********************************************/
const std::string TITLE_IMAGE = "Images/title.png";
const std::string BUTTONS_IMAGE = "Images/buttons.png";


/********************************************
    Menu Class
*********************************************
    Arthur : 26/03 - 02/04
*********************************************/
class Menu : public View
{
public:
    //=== CTORs / DTORs
    Menu(unsigned int w, unsigned int h, sf::RenderWindow *window);
    virtual ~Menu();

    //=== METHODS
    virtual void synchronize() override;
    virtual void draw() override;
    virtual void loadImages() override;
    virtual bool treatEvents() override;

private:
    //=== ATTRIBUTES

    //Textures
    sf::Texture m_farBackgroundTexture;
    sf::Texture m_nearBackgroundTexture;
    sf::Texture m_titleTexture;
    sf::Texture m_playButtonTexture;
    sf::Texture m_quitButtonTexture;

    //Graphic Elements
    SlidingBackground *m_farBackground;
    SlidingBackground *m_nearBackground;
    GraphicElement *m_titleGraphic;
    GraphicElement *m_playButtonGraphic;
    GraphicElement *m_quitButtonGraphic;
};

#endif // MENU_H
