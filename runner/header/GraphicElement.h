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

#ifndef GRAPHICELEMENT_H
#define GRAPHICELEMENT_H

#include <SFML/Graphics.hpp>
#include <chrono>

/********************************************
    GraphicElement Class
*********************************************
    Arthur : 21/02 - 31/03
    Florian: 21/02 - 2/03
*********************************************/
class GraphicElement : public sf::Sprite
{
public:
    //=== CTORs / DTORs
    GraphicElement(GraphicElement const& elementACopier);
    GraphicElement(sf::Texture &image, unsigned int x, unsigned int y, unsigned int w, unsigned int h);
    ~GraphicElement();

    //=== METHODS
    virtual void sync() {}
    virtual void draw(sf::RenderWindow *window);
    void resize(unsigned int w, unsigned int h);

private:
    //=== ATTRIBUTES
    unsigned int m_w;
    unsigned int m_h;
};

#endif // GRAPHICELEMENT_H
