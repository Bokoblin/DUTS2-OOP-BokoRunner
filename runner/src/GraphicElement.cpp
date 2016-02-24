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

#include "../header/GraphicElement.h"

//=======================================
// Constructeur
//=======================================
GraphicElement::GraphicElement()
{

}

GraphicElement::GraphicElement(sf::Texture &image, int x, int y, int w, int h) : m_w(w), m_h(h)
{
    this->setTexture(image);
    this->setPosition( (float)x, (float)y);
}

//=======================================
// Destructeur
//=======================================
GraphicElement::~GraphicElement()
{
    //dtor
}


//=======================================
// Fonction de dessin
//=======================================
void GraphicElement::draw(sf::RenderWindow * current_window)
{
    current_window->draw(*this);
    current_window->display();
}


//=======================================
// Fonction de redimentionnement
//=======================================
void GraphicElement::resize(int width, int height)
{
    sf::FloatRect bb = this->getLocalBounds();
    float width_factor = width / bb.width;     // facteur de mise à l'échelle
    float height_factor = height / bb.height;
    this->setScale(width_factor, height_factor);
    //modification largeur et hauteur
    this->m_w = width;
    this->m_h = height;
}
