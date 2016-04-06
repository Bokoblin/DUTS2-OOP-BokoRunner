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

#ifndef ANIMATEDGRAPHICELEMENT_H
#define ANIMATEDGRAPHICELEMENT_H

#include "GraphicElement.h"
#include <iostream>
#include <chrono>

/********************************************
    AnimatedGraphicElement - Class
*********************************************
    Arthur : 3/03 - 06/04
*********************************************/
class AnimatedGraphicElement : public GraphicElement
{
public:
    //=== CTORs / DTORs
    AnimatedGraphicElement(sf::Texture &image, unsigned int x, unsigned int y, unsigned int w, unsigned int h,
            const std::vector<sf::IntRect> & clipRects, unsigned int separator);
    AnimatedGraphicElement(AnimatedGraphicElement const& other);
    virtual ~AnimatedGraphicElement();

    //=== METHODS
    virtual void sync() override;

private:
    //=== ATTRIBUTES
    std::vector<sf::IntRect> m_clipRectsArray;
    unsigned int m_currentClipRect;
    std::chrono::system_clock::time_point m_lastAnimationTime;
    unsigned int m_arraySeparator;
};

#endif // ANIMATEDGRAPHICELEMENT_H
