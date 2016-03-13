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

/********************************************
    AnimatedGraphicElement - Class
*********************************************
    Arthur : 3/03 - 5/03
*********************************************/
class AnimatedGraphicElement : public GraphicElement
{
public:
    //=== CTORs / DTORs
    AnimatedGraphicElement(const std::vector<sf::IntRect> & clipRects,
                           sf::Texture &image, int x, int y, int w, int h);
    AnimatedGraphicElement(AnimatedGraphicElement const& elementACopier);
    ~AnimatedGraphicElement();

    //=== METHODS
    void draw( sf::RenderWindow *window);

private:
    //=== ATTRIBUTES
    std::vector<sf::IntRect> m_clip_rects;
    unsigned int m_current_clip_rect;
    int m_nb_steps;

};

#endif // ANIMATEDGRAPHICELEMENT_H
