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


/********************************************
    Parameterized Constructor
*********************************************
    Arthur : 21/02 - 2/03
    Florian: 21/02 - 2/03
*********************************************/
GraphicElement::GraphicElement(sf::Texture &image, int x, int y, int w, int h) : m_w(w), m_h(h)
{
    this->setTexture(image);
    this->setPosition( (float)x, (float)y);
}


/********************************************
    Copy Constructor
*********************************************
    Arthur : 25/02 - 2/03
    Florian: 2/03 - 2/03
*********************************************/
GraphicElement::GraphicElement(GraphicElement const& elementACopier) :
    m_w(elementACopier.m_w), m_h(elementACopier.m_h)
{
       this->setPosition( 1.0*(rand()%800),450.f);
       this->setTexture( *elementACopier.getTexture(), true );
}


/********************************************
    Destructor
*********************************************
    Arthur : 21/02 - 21/02
    Florian: 21/02 - 21/02
*********************************************/
GraphicElement::~GraphicElement()
{
    //Dtor
}


/********************************************
    Drawing function
*********************************************
    Arthur : 22/02 - 22/02
    Florian: 22/02 - 22/02
*********************************************/
void GraphicElement::draw(sf::RenderWindow * current_window)
{
    current_window->draw(*this);
    current_window->display();
}


/********************************************
    Resizing function
*********************************************
    Arthur : 22/02 - 25/02
    Florian: 22/02 - 22/02
*********************************************/
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
