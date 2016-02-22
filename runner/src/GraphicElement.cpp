/*
Copyright (C) 2015 Jolivet Arthur & Laronze Florian

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

#include "../header/GraphicElement.h"

GraphicElement::GraphicElement()
{
    //ctor
}


GraphicElement::GraphicElement(sf::Texture &image, int x, int y, int w, int h) : m_w(w), m_h(h)
{
    this->setTexture(image);
    this->setPosition( (float)x, (float)y);
}

GraphicElement::~GraphicElement()
{
    //dtor
}

void GraphicElement::draw(sf::RenderWindow * current_window)
{
   // current_window->draw(?????);
    current_window->display();
}

void GraphicElement::resize(int width, int height)
{
    sf::FloatRect bb = this->getLocalBounds();
    int width_factor = width / bb.width;     // facteur de mise à l'échelle pour la largeur
    int height_factor = height / bb.height;  // facteur de mise à l'échelle pour la largeur
    this->setScale(width_factor, height_factor);
}
