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
#include <iostream>

/********************************************
    Parameterized Constructor
*********************************************
    Arthur : 21/02 - 14/03
    Florian: 21/02 - 2/03
*********************************************/
GraphicElement::GraphicElement(sf::Texture &image, int x, int y, int w, int h) : m_w{w}, m_h{h}
{
    this->setTexture(image);
    this->setPosition( (float)x, (float)y);
}


/********************************************
    Copy Constructor
*********************************************
    Arthur : 25/02 - 20/03
    Florian:  2/03 - 2/03
*********************************************/
GraphicElement::GraphicElement(GraphicElement const& elementACopier) :
    Sprite(), m_w(elementACopier.m_w), m_h(elementACopier.m_h)
{
    this->setPosition( elementACopier.getPosition() );
    this->setTexture( *elementACopier.getTexture(), true );
    this->setOrigin( elementACopier.getOrigin() );
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
    Arthur : 22/03
*********************************************/
void GraphicElement::draw(sf::RenderWindow *window) {}


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

/********************************************
    Containing point function
*********************************************
    Arthur : 25/03
*********************************************/
bool GraphicElement::contains(sf::Vector2f point)
{
    int  maxX = this->getPosition().x + this->getLocalBounds().width;
    int  maxY = this->getPosition().y + this->getLocalBounds().height;

    return (point.x >= this->getPosition().x) && (point.x < maxX) && (point.y >= this->getPosition().y) && (point.y < maxY);
}
