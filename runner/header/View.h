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
#include "GraphicElement.h"
#include <SFML/Graphics.hpp>

#define POSITION_X_BALL m_model->getBall().getPosX()
#define POSITION_Y_BALL m_model->getBall().getPosY()
#define WIDTH_BALL m_model->getBall().getWidth()

const std::string BACKGROUND_IMAGE = "Images/city.png";
const std::string BALL_IMAGE = "Images/ball_25.png";

class Model;

class View
{
public:
    View(int w, int h);
    ~View();

    void setModel(Model * model);

    void synchronize();
    void draw();
    bool treatEvents();

private:
    int m_viewWidth, m_viewHeight;

    sf::RenderWindow *m_window;
    Model *m_model;

    sf::Texture m_background;
    sf::Sprite m_backgroundSprite; //a suppr quand graphicElement marchera

    sf::Texture m_ball;
    sf::Sprite m_ballSprite;//a suppr quand graphicElement marchera

    std::map<const MovableElement *, GraphicElement *> m_elementToGraphicElement;

};
#endif
