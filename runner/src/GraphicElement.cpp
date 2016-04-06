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

using namespace std::chrono;

/********************************************
    Parameterized Constructors
*********************************************
    Arthur : 21/02 - 03/04
    Florian: 21/02 - 2/03
*********************************************/
GraphicElement::GraphicElement(sf::Texture &image, unsigned int x, unsigned int y,
        unsigned int w, unsigned int h) : m_width{w}, m_height{h}
{
    this->setTexture(image);
    this->setPosition(x, y);
}

GraphicElement::GraphicElement( unsigned int w, unsigned int h) : m_width{w}, m_height{h}
{}


/********************************************
    Copy Constructor
*********************************************
    Arthur : 25/02 - 20/03
    Florian:  2/03 - 2/03
*********************************************/
GraphicElement::GraphicElement(GraphicElement const& elementACopier) :
    Sprite(), m_width(elementACopier.m_width), m_height(elementACopier.m_height)
{
    this->setPosition( elementACopier.getPosition() );
    this->setTexture( *elementACopier.getTexture(), true );
    this->setOrigin( elementACopier.getOrigin() );
}


/********************************************
    Destructor
*********************************************
    Arthur : 21/02
    Florian: 21/02
*********************************************/
GraphicElement::~GraphicElement()
{}


/********************************************
    Synchronization function
*********************************************
    Arthur : 03/04
*********************************************/
void GraphicElement::sync()
{}


/********************************************
    Drawing function
*********************************************
    Arthur : 30/03
*********************************************/
void GraphicElement::draw(sf::RenderWindow *window) const
{
    window->draw(*this);
}


/********************************************
    Resizing function
*********************************************
    Arthur : 22/02 - 25/02
    Florian: 22/02
*********************************************/
void GraphicElement::resize(unsigned int width, unsigned int height)
{
    sf::FloatRect bb = this->getLocalBounds();
    float width_factor = width / bb.width;
    float height_factor = height / bb.height;
    this->setScale(width_factor, height_factor);
    //modification largeur et hauteur
    this->m_width = width;
    this->m_height = height;
}

