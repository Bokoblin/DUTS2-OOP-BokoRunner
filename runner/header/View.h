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

#include "Model.h"
#include "../header/GraphicElement.h"
#include "../header/SlidingBackground.h"
#include "../header/AnimatedGraphicElement.h"
#include <SFML/Graphics.hpp>

#include <sstream>
#include <iostream>
#include <string>

#define POS_X_BALL m_model->getBallElement()->getPosX()
#define POS_Y_BALL m_model->getBallElement()->getPosY()
#define WIDTH_BALL m_model->getBallElement()->getWidth()

const std::string BACKGROUND_IMAGE_1 = "Images/city_1.png";
const std::string BACKGROUND_IMAGE_2 = "Images/city_2.png";
const std::string BALL_IMAGE = "Images/balls.png";
const std::string ENNEMIES_IMAGE = "Images/ennemies.png";
const std::string FONT = "Fonts/Antique_Olive.ttf";

class Model;

/********************************************
    View Class
*********************************************
    Arthur : 21/02 - 5/03
    Florian: 21/02 - 3/03
*********************************************/
class View
{
public:
    //=== CTORs / DTORs
    View(int w, int h);
    ~View();

    //=== SETTERS
    void setModel(Model *model);

    //=== METHODS
    void loadImages();
    void synchronize();
    void draw();
    bool treatEvents();

private:
    //=== ATTRIBUTES
    int m_viewWidth, m_viewHeight;

    sf::RenderWindow *m_window;
    Model *m_model;

    sf::Font *m_font;
    sf::Text m_textPositionBall;

    //=== GraphicElements Textures
    sf::Texture m_farBackgroundTexture;
    sf::Texture m_nearBackgroundTexture;
    sf::Texture m_playerTexture;
    sf::Texture m_ennemiesTexture;

    SlidingBackground *m_farBackground;
    SlidingBackground *m_nearBackground;
    AnimatedGraphicElement *m_playerGraphic;
    GraphicElement *m_ennemiesGraphic;

    //=== Associative arrays
    std::map<const MovableElement *, GraphicElement *> m_elementToGraphicElement;
};
#endif
