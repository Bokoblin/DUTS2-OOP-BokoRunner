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

#include "Model.h"
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <cassert>
#include <ctime>
#include "SFML/Graphics.hpp"
#include "SlidingBackground.h"

/********************************************
    Constant Variables
********************************************/
const std::string FONT = "Fonts/Antique_Olive.ttf";
const std::string BACKGROUND_IMAGE_1 = "Images/city_1.png";
const std::string BACKGROUND_IMAGE_2 = "Images/city_2.png";
const std::string TITLE_IMAGE = "Images/title.png";
const std::string BUTTONS_IMAGE = "Images/buttons.png";


/********************************************
    Menu Class
*********************************************
    Arthur : 26/03
*********************************************/
class Menu
{
public:
    //=== CTORs / DTORs
    Menu(int width, int height, Model *model, sf::RenderWindow *mywindow);
    virtual ~Menu();


    //=== GETTERS
    //=== SETTERS

    //=== METHODS
    void sync();
    void draw();
    void loadImages();
    void loadText();
    bool treatEvents(sf::Event event);

private:
    //=== ATTRIBUTES
    int m_menuWidth;
    int m_menuHeight;

    //Text
    sf::Font *m_font;
    Model *m_model;
    sf::RenderWindow *m_window;
    sf::Text m_playButtonText;
    sf::Text m_quitButtonText;

    //Textures
    sf::Texture m_farBackgroundTexture;
    sf::Texture m_nearBackgroundTexture;
    sf::Texture m_titleTexture;
    sf::Texture m_playButtonTexture;
    sf::Texture m_quitButtonTexture;

    //Overall Graphic Elements
    SlidingBackground *m_farBackground;
    SlidingBackground *m_nearBackground;
    //Menu Graphic Elements
    GraphicElement *m_titleGraphic;
    GraphicElement *m_playButtonGraphic;
    GraphicElement *m_quitButtonGraphic;
};

#endif // MENU_H
